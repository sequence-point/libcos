#ifndef libcos__exception_hxx_
#define libcos__exception_hxx_

#include <stdexcept>

namespace carousel {

class not_implemented : public std::runtime_error {
public:
  not_implemented() : std::runtime_error{ "feature not implemented" }
  {}
};

} // namespace carousel

#endif
