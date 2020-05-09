#include <libunittest/unittest.hxx>

#include <libcos/objects/name.hxx>
#include <libcos/objects/undefined.hxx>

#include <libcos/writer.hxx>

#include <sstream>

DEFINE_TEST("write_header(\"PDF-1.0\")")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.write_header("PDF-1.0");

  TEST_EQUAL(str.str(), "%PDF-1.0\r\n%%\x80\xff\x80\xff\r\n");
}

DEFINE_TEST("write_value(boolean{ false })")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.write_value(carousel::boolean{ false });

  TEST_EQUAL(str.str(), "false");
}

DEFINE_TEST("write_value(boolean{ true })")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.write_value(carousel::boolean{ true });

  TEST_EQUAL(str.str(), "true");
}

DEFINE_TEST("write_value(integer{ 0 })")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.write_value(carousel::integer{ 0 });

  TEST_EQUAL(str.str(), "0");
}

DEFINE_TEST("write_value(real{ 1.1 })")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.write_value(carousel::real{ 1.1 });

  TEST_EQUAL(str.str(), "1.100000");
}

DEFINE_TEST("write_value(string{ \"Covfefe\" }) (literal)")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_value(string{ \"Covfefe\" }) (hex)")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_value(name{ \"Covfefe\" })")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.write_value(carousel::name{ "Covfefe" });

  TEST_EQUAL(str.str(), "/Covfefe");
}

DEFINE_TEST("write_value(array{ })")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_value(array{ ... })")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_value(dictionary{ })")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_value(dictionary{ ... })")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_value(undefined{ })")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.write_value(carousel::undefined{});

  TEST_EQUAL(str.str(), "null");
}

DEFINE_TEST("write_object(object{ ... })")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("begin_xref()")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.begin_xref();

  TEST_EQUAL(str.str(), "xref\r\n");
}

DEFINE_TEST("begin_xref_chunk(...)")
{
  std::ostringstream str;
  carousel::writer w{ str };

  w.begin_xref_chunk(0, 6);

  TEST_EQUAL(str.str(), "0 6\r\n");
}

DEFINE_TEST("write_xref_used_entry(...)")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_xref_free_entry(...)")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_trailer(dictionary{ ... })")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("write_eof(1024)")
{
  TEST_NOT_IMPLEMENTED;
}
