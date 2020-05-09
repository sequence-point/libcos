#ifndef libcos__objects__string_hxx_
#define libcos__objects__string_hxx_

namespace carousel {

class string {
public:
  explicit string(std::string value) : value_{ std::move(value) }
  {}

  std::string const&
  value() const
  {
    return value_;
  }

private:
  std::string value_;
};

} // namespace carousel

#endif
