#include <libunittest/unittest.hxx>

#include <libcos/objects/boolean.hxx>

DEFINE_TEST("constructor")
{
  carousel::boolean boolean{ true };

  TEST_EQUAL(boolean.value(), true);
}
