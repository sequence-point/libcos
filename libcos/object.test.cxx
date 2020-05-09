#include <libunittest/unittest.hxx>

#include <libcos/object.hxx>
#include <libcos/value-source.hxx>

#include <libcos/objects/boolean.hxx>
#include <libcos/objects/integer.hxx>
#include <libcos/objects/undefined.hxx>

#include <cstdint>
#include <map>

class dummy_value_source : public carousel::value_source {
public:
  void
  store(std::uint32_t index,
        std::uint16_t generation,
        carousel::value const& v) override
  {}

  carousel::value
  load(std::uint32_t index, std::uint16_t generation) override
  {
    return carousel::undefined{};
  }
};

DEFINE_TEST("object{ boolean{ ... } }")
{
  carousel::object obj{ carousel::boolean{ true } };

  TEST_TRUE(obj.is< carousel::boolean >());
  TEST_TRUE(object_cast< carousel::boolean >(obj).value());
}

DEFINE_TEST("object{ integer{ ... } }")
{
  carousel::object obj{ carousel::integer{ 1337 } };

  TEST_TRUE(obj.is< carousel::integer >());
  TEST_EQUAL(object_cast< carousel::integer >(obj).value(), 1337);
}

DEFINE_TEST("object{ undefined }")
{
  carousel::object obj{ carousel::undefined{} };

  TEST_TRUE(obj.is< carousel::undefined >());
}

DEFINE_TEST("object{ ... } = object{ ... } (unique = unique)")
{
  carousel::object obj{ carousel::undefined{} };

  TEST_TRUE(obj.is< carousel::undefined >());

  obj = carousel::integer{ 1337 };

  TEST_TRUE(obj.is< carousel::integer >());
  TEST_EQUAL(object_cast< carousel::integer >(obj).value(), 1337);
}

DEFINE_TEST("object{ ... } = object{ ... } (shared = unique)")
{
  dummy_value_source dvs;
  carousel::value_cache vc{ dvs };

  carousel::object obj{ vc, 32, 0 };

  TEST_TRUE(obj.is< carousel::undefined >());

  obj = carousel::integer{ 1337 };

  TEST_TRUE(obj.is< carousel::integer >());
  TEST_EQUAL(object_cast< carousel::integer >(obj).value(), 1337);

  // Create a new indirect reference to the same object.
  carousel::object obj2{ vc, 32, 0 };

  TEST_TRUE(obj2.is< carousel::integer >());
  TEST_EQUAL(object_cast< carousel::integer >(obj2).value(), 1337);

  // Change the value of obj2 and obj should change.
  obj2 = carousel::integer{ 2000 };

  TEST_TRUE(obj.is< carousel::integer >());
  TEST_EQUAL(object_cast< carousel::integer >(obj).value(), 2000);

  // Change the type of the obj and obj2 should change.
  obj = carousel::undefined{};

  TEST_TRUE(obj2.is< carousel::undefined >());

  // Finally, check the cache directly.
  TEST_TRUE(vc.lookup(32, 0).is< carousel::undefined >());
}

// DEFINE_TEST("shared")
//{
//  cos::object obj{ 32, 16, cos::undefined{} };
//
//  TEST_TRUE(obj.is_shared());
//  TEST_EQUAL(obj.index(), 32);
//  TEST_EQUAL(obj.generation(), 16);
//}

// DEFINE_TEST("create dictionary")
//{
//  // Create the dictionary.
//  cos::object my_dict{ cos::dictionary };
//
//  // Access the dictionary.
//  object_cast< cos::dictionary >(my_dict).add("hello", cos::integer{ 0 });
//
//}
