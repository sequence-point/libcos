#include <libunittest/unittest.hxx>

#include <libcos/objects/integer.hxx>

DEFINE_TEST("constructor")
{
  carousel::integer integer{ 1337 };

  TEST_EQUAL(integer.value(), 1337);
}
