#include <libunittest/unittest.hxx>

#include <libcos/objects/name.hxx>

DEFINE_TEST("constructor")
{
  carousel::name name{ "Title" };

  TEST_EQUAL(name.value(), "Title");
}
