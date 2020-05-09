#include <libunittest/unittest.hxx>

#include <libcos/database.hxx>

#include <sstream>

DEFINE_TEST("create database")
{
	std::stringstream str;

  carousel::database db;
  //db.create("/example.pdf");
}

DEFINE_TEST("open database")
{
	std::stringstream str;

  carousel::database db;
 	db.open(str);
  //db.open("/example.pdf");
}
