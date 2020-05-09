#include <libunittest/unittest.hxx>

#include <sstream>
#include <string>

#include <libcos/xref.hxx>

std::string expected{
  "xref\r\n"
  "0 1\r\n"
  "0000000000 65535 f\r\n"
  "1 1\r\n"
  "0000001024 00000 n\r\n"
  "2 1\r\n"
  "0000000512 00000 n\r\n"
};

DEFINE_TEST("allocate and write")
{
  carousel::cross_reference xref;

  xref.set(xref.allocate(), 1024); // should allocate index 1
  xref.set(xref.allocate(), 512); // should allocate index 2

  std::stringstream str;

  xref.write(str);

  TEST_EQUAL(str.str(), expected);
}
