#include <iostream>
#include <sstream>

#include <libcos/database.hxx>

#include <libcos/objects/dictionary.hxx>
#include <libcos/objects/name.hxx>

int
main(int argc, char* argv[])
try {

  std::stringstream str;

  carousel::database db;
  db.create(str, "EXAMPLE");

  {
    auto dict_obj = db.allocate< carousel::dictionary >();
    auto& dict = carousel::object_cast< carousel::dictionary >(dict_obj);
    dict.set("Key", carousel::object{ carousel::name{ "Covfefe" } });
    dict.set("Key2", carousel::object{ carousel::name{ "Coverage" } });
  }

  {
    auto dict_obj = db.allocate< carousel::dictionary >();
    auto& dict = carousel::object_cast< carousel::dictionary >(dict_obj);
  }

  {
    auto dict_obj = db.allocate< carousel::dictionary >();
    auto& dict = carousel::object_cast< carousel::dictionary >(dict_obj);
    dict.set("Key", carousel::object{ carousel::name{ "Covfefe" } });
    dict.set("Key2", db.allocate< carousel::name >("Indirect Name"));
  }

  {
    auto dict_obj = db.allocate< carousel::dictionary >();
    auto& dict = carousel::object_cast< carousel::dictionary >(dict_obj);
    dict.set("Key", carousel::object{ carousel::name{ "Covfefe" } });
    dict.set("Key2", carousel::object{ carousel::dictionary{} });
  }

  {
    auto stream_obj = db.allocate< carousel::stream >();
    auto& stream = carousel::object_cast< carousel::stream >(stream_obj);
  }

  db.flush();
  db.close();

  std::cout << str.str() << '\n';

  return 0;
}
catch (char const* what) {
  std::cout << "error: " << what << '\n';
}
catch (std::exception const& ex) {
  std::cout << "error: " << ex.what() << '\n';
}
