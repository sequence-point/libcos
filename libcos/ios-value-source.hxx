#ifndef libcos__ios_value_source_hxx_
#define libcos__ios_value_source_hxx_

#include <libcos/value-source.hxx>
#include <libcos/xref.hxx>

#include <cstdint>
#include <iostream>

namespace carousel {

class ios_value_source : public value_source {
public:
  ios_value_source(std::iostream& ios, cross_reference& xref)
    : ios_{ ios }, xref_{ xref }
  {}

  std::iostream&
  ios()
  {
    return ios_;
  }

  void
  store(std::uint32_t index, std::uint16_t generation, value const& v) override
  {
    // Seek to the end.
    ios().seekp(0, std::ios_base::end);

    // Update the cross reference table to store the new offset of the object.
    auto offset = static_cast< std::uint64_t >(ios().tellp());
    xref_.set(index, offset); // TODO handle generation

    // Write the object.
    writer w{ ios_ };
    w.write_value(index, generation, v);

    // Done.
  }

  value
  load(std::uint32_t index, std::uint16_t generation) override
  {
    // TODO detect mismatch index generation and file.
    return undefined{};
  }

private:
  std::iostream& ios_;
  cross_reference& xref_;
};

} // namespace carousel

#endif
