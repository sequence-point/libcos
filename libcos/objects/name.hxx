#ifndef libcos__objects__name_hxx_
#define libcos__objects__name_hxx_

#include <string>

namespace carousel {

class name {
public:
  explicit name(std::string value) : value_{ std::move(value) }
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
