#ifndef libcos__value_cache_hxx_
#define libcos__value_cache_hxx_

#include <libcos/value-source.hxx>
#include <libcos/value.hxx>

#include <libcos/objects/undefined.hxx>

#include <cassert>
#include <cstdint>
#include <map>

namespace carousel {

class value_cache {
public:
  explicit value_cache(value_source& s) : source_{ s }
  {}

  value_source&
  source()
  {
    return source_;
  }

  void
  put(std::uint32_t index, std::uint16_t generation, value v)
  {
    key k{ index, generation };
    cache_.insert_or_assign(k, entry{ std::move(v), true });
  }

  value&
  lookup(std::uint32_t index, std::uint16_t generation)
  {
    key k{ index, generation };
    auto it = cache_.find(k);

    if (it != cache_.end())
      return it->second.v;

    // Load from source and insert into cache.
    cache_.insert_or_assign(k, entry{ source().load(index, generation), true });

    it = cache_.find(k);

    assert(it != cache_.end());

    return it->second.v;
  }

  void
  flush()
  {
    for (auto const& j : cache_) {
      auto const entry_dirty = j.second.dirty;
      auto const value_dirty = true; // j.second.v.is_dirty();

      if (entry_dirty || value_dirty)
        source().store(j.first.index, j.first.generation, j.second.v);
    }
  }

  //! Purge the cache removing all entries loosing any unflushed changes.
  void
  purge()
  {
    cache_.clear();
  }

private:
  struct key {
    std::uint32_t index;
    std::uint32_t generation;

    bool
    operator<(key const& other) const
    {
      if (index < other.index)
        return true;

      return generation < other.generation;
    }
  };

  struct entry {
    value v;
    bool dirty{ false };
  };

  value_source& source_;
  std::map< key, entry > cache_;
};

} // namespace carousel

#endif
