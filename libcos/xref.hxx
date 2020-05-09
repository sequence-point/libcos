#ifndef libcos__xref_hxx_
#define libcos__xref_hxx_

#include <libcos/writer.hxx>

#include <cstdint>
#include <ios>
#include <map>

namespace carousel {

//! Represents a highly simplified PDF cross-reference table.
class cross_reference {
public:
  void
  load(std::istream& input)
  {
    throw "not implemented";
  }

  void
  write(std::ostream& output)
  {
    writer w{ output };

    w.begin_xref();

    // Hard-coded object 0 for now.
    w.begin_xref_chunk(0, 1);
    w.write_xref_free_entry(0, 0xFFFF);

    for (auto const& j : table_) {
      w.begin_xref_chunk(j.first, 1);
      w.write_xref_used_entry(j.second, 0);
    }
  }

  std::uint32_t
  allocate()
  {
    auto index = 1;

    if (auto it = table_.rbegin(); it != table_.rend())
      index = it->first + 1;

    table_.insert_or_assign(index, 0);

    return index;
  }

  void
  set(std::uint32_t index, std::uint64_t offset)
  {
    table_.insert_or_assign(index, offset);
  }

  std::uint64_t
  get(std::uint32_t index)
  {
    auto it = table_.find(index);

    if (it == table_.end())
      return 0;

    return it->second;
  }

  cross_reference&
  operator=(cross_reference const&) = delete;

  cross_reference&
  operator=(cross_reference&&) = delete;

private:
  std::map< std::uint32_t, std::uint64_t > table_;
};

} // namespace carousel

#endif
