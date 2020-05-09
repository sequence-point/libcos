#ifndef libcos__objects__stream_hxx_
#define libcos__objects__stream_hxx_

#include <libcos/visitor.hxx>

#include <libcos/objects/dictionary.hxx>

#include <cstdint>
#include <sstream>
#include <stdexcept>

namespace carousel {

class stream : public dictionary {
public:
  enum seek_direction { beg, cur, end };

  stream() = default;
  stream(stream const&){};
  stream(stream&&){};

  void
  feed(std::istream& source, std::uint32_t count)
  {
    data_.str(std::string{});
  }

  void
  flush(std::ostream& target)
  {
    target << data_.rdbuf();
  }

  std::uint32_t
  seek(std::uint32_t pos)
  {
    // TODO bounds
  }

  std::uint32_t
  seek(std::int32_t off, seek_direction dir)
  {
    // TODO
    throw "not implemented";
  }

  std::uint32_t
  tell()
  {}

  std::uint32_t
  read(char* s, std::uint32_t count)
  {
    if (s == nullptr)
      throw std::invalid_argument{ "s cannot be null" };

    // offset_ += data_.read(s, count).gcount();
  }

  std::uint32_t
  write(char const* s, std::uint32_t count)
  {
    if (s == nullptr)
      throw std::invalid_argument{ "s cannot be null" };

    // offset_ += data_.write(s, count).pcount
  }

  bool
  operator==(stream const& other)
  {
    return false;
  }
  bool
  operator!=(stream const& other)
  {
    return true;
  }

  stream&
  operator=(stream const& other)
  {
    throw "cannot assign a stream";
  }

  stream&
  operator=(stream&& other)
  {
    throw "cannot assign a stream";
  }

private:
  std::stringstream data_;
};

void
accept(stream& visitee, visitor& v)
{
  accept(static_cast< dictionary& >(visitee), v);
}

template< typename T >
void
accept(stream const& visitee, visitor& v)
{
  accept(static_cast< dictionary const& >(visitee), v);
}

} // namespace carousel

#endif
