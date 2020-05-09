#include <libunittest/unittest.hxx>

#include <libcos/objects/real.hxx>

DEFINE_TEST("constructor")
{
  carousel::real real{ 1.2 };

  TEST_EQUAL(real.value(), 1.2);
}
