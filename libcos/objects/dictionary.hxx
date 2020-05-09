#ifndef libcos__objects__dictionary_hxx_
#define libcos__objects__dictionary_hxx_

#include <libcos/object.hxx>

#include <map>

namespace carousel {

class dictionary {
public:
  using container_type = std::map< std::string, object >;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;

  iterator
  begin()
  {
    return container_.begin();
  }

  const_iterator
  begin() const
  {
    return container_.begin();
  }

  const_iterator
  cbegin() const
  {
    return container_.cbegin();
  }

  iterator
  end()
  {
    return container_.end();
  }

  const_iterator
  end() const
  {
    return container_.end();
  }

  const_iterator
  cend() const
  {
    return container_.cend();
  }

  void
  set(std::string const& key, object obj)
  {
    container_.insert_or_assign(key, std::move(obj));
  }

  object&
  get(std::string const& key)
  {
    return container_.at(key);
  }

  object const&
  get(std::string const& key) const
  {
    return container_.at(key);
  }

  void
  erase(std::string const& key)
  {
    container_.erase(key);
  }

private:
  container_type container_;
};

} // namespace carousel

#endif
