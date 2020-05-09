#ifndef libcos__parser_hxx_
#define libcos__parser_hxx_

#include <libcos/objects/boolean.hxx>
#include <libcos/objects/integer.hxx>
#include <libcos/objects/real.hxx>
#include <libcos/objects/string
#include <libcos/objects/array.hxx>
#include <libcos/objects/dictionary.hxx>
#include <libcos/objects/name.hxx>

#include <istream>

namespace carousel {

class parser {
public:
  explicit parser(std::istream& source);

  optional< value >
  try_parse();

private:
  optional< boolean >
  try_parse_boolean();

  optional< number >
  try_parse_number();

  optional< string >
  try_parse_string();

  optional< name >
  try_parse_name();

  optional< array >
  try_parse_array();

  optional< dictionary >
  try_parse_dictionary();

  // TODO streams

  optional< undefined >
  try_parse_undefined();

  std::istream& source_;
};

} // namespace carousel

#endif
