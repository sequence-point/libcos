#include <libunittest/unittest.hxx>

#include <libcos/value.hxx>

#include <libcos/objects/boolean.hxx>
#include <libcos/objects/integer.hxx>
#include <libcos/objects/real.hxx>
#include <libcos/objects/undefined.hxx>

DEFINE_TEST("value{ boolean }")
{
  carousel::value v1{ carousel::boolean{ true } };
  carousel::value v2{ carousel::boolean{ false } };
  carousel::value v3{ carousel::boolean{ true } };

  TEST_TRUE(v1.is< carousel::boolean >());
  TEST_TRUE(v2.is< carousel::boolean >());
  TEST_TRUE(v3.is< carousel::boolean >());
  TEST_TRUE(value_cast< carousel::boolean >(v1).value());
  TEST_FALSE(value_cast< carousel::boolean >(v2).value());
  TEST_EQUAL(v1, v3);
}

DEFINE_TEST("value{ integer }")
{
  carousel::value v1{ carousel::integer{ 1337 } };

  TEST_TRUE(v1.is< carousel::integer >());
  TEST_EQUAL(value_cast< carousel::integer >(v1).value(), 1337);
}

DEFINE_TEST("value{ real }")
{
  carousel::value v1{ carousel::real{ 1.0 } };

  TEST_TRUE(v1.is< carousel::real >());
  TEST_EQUAL(value_cast< carousel::real >(v1).value(), 1.0);
}

DEFINE_TEST("value{ string }")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("value{ name }")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("value{ array }")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("value{ dictionary }")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("value{ undefined }")
{
  carousel::value v1{ carousel::undefined{} };
  carousel::value v2{ carousel::undefined{} };

  TEST_TRUE(v1.is< carousel::undefined >());
  TEST_TRUE(v2.is< carousel::undefined >());

  TEST_FALSE(v1 == v2);
  TEST_TRUE(v1 != v2);
}

DEFINE_TEST("value{ value{ ... } }")
{
  carousel::value v1{ carousel::value{ carousel::undefined{} } };
  carousel::value v2{ carousel::value{ carousel::integer{ 1337 } } };

  TEST_TRUE(v1.is< carousel::undefined >());
  TEST_TRUE(v2.is< carousel::integer >());
}

DEFINE_TEST("value = value")
{
  carousel::value v1{ carousel::undefined{} };
  carousel::value v2{ carousel::integer{ 1337 } };

  TEST_TRUE(v1.is< carousel::undefined >());
  TEST_TRUE(v2.is< carousel::integer >());

  TEST_THROWS(std::bad_cast, { v1 = v2; });
  TEST_THROWS(std::bad_cast, { v1 = carousel::integer{ 8765 }; });
}
