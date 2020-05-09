#ifndef libcos__value_source_hxx_
#define libcos__value_source_hxx_

#include <libcos/value.hxx>

#include <cstdint>

namespace carousel {

class value_source {
public:
  virtual ~value_source() = default;

  virtual void
  store(std::uint32_t index, std::uint16_t generation, value const& v) = 0;

  virtual value
  load(std::uint32_t index, std::uint16_t generation) = 0;
};

} // namespace carousel

#endif
