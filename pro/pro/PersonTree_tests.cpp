#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "Person.h"
#include "tree.h"

TEST_SUITE_BEGIN("Person");

TEST_CASE("Default constructor") {
  Person person;

  REQUIRE(person.m_phone == 0);
  REQUIRE(person.m_age == 0);
  REQUIRE(person.m_fio.empty());
  REQUIRE(person.m_address.empty());
}

TEST_CASE("Create and save to CSV") {
  const std::string csv("123	John	33	Neverland");
  Person person{csv};

  REQUIRE(person.m_phone == 123);
  REQUIRE(person.m_fio == "John");
  REQUIRE(person.m_age == 33);
  REQUIRE(person.m_address == "Neverland");

  REQUIRE(person.toCsv() == csv);
}


TEST_CASE("Compare instances") {
  Person personJohn{"123	John	33	Neverland"};
  Person personSmith{"456	Smith	33	Neverland" };

  REQUIRE(personJohn < personSmith);
  REQUIRE(personSmith > personJohn);
}

TEST_SUITE_END();


TEST_SUITE_BEGIN("Tree node");

TEST_CASE("Compare instances") {
  tree_node node{Person{}, nullptr};

  REQUIRE(node.value.m_phone == 0);
  REQUIRE(node.up == nullptr);
}

TEST_SUITE_END();


TEST_SUITE_BEGIN("Tree");

TEST_CASE("Can insert, remove and find") {
  Person p;
  tree t;
  tree_node* n = nullptr;

  // Mixed inserts and removes
  p.m_phone = 3;
  REQUIRE(((n = t.insert(p)) && n->value.m_phone == p.m_phone));
  p.m_phone = 1;
  REQUIRE(((n = t.insert(p)) && n->value.m_phone == p.m_phone));
  p.m_phone = 2;
  REQUIRE(((n = t.insert(p)) && n->value.m_phone == p.m_phone));
  p.m_phone = 4;
  REQUIRE(((n = t.insert(p)) && n->value.m_phone == p.m_phone));
  p.m_phone = 5;
  REQUIRE(((n = t.insert(p)) && n->value.m_phone == p.m_phone));
  p.m_phone = 3;
  REQUIRE(t.remove(p));
  p.m_phone = 5;
  REQUIRE(t.remove(p));
  p.m_phone = 10;
  REQUIRE(((n = t.insert(p)) && n->value.m_phone == p.m_phone));

  // Negative remove cases
  p.m_phone = 5;
  REQUIRE(!t.remove(p));
  p.m_phone = 11;
  REQUIRE(!t.remove(p));

  // Trying to find all remaining items in the tree: {1, 2, 4, 10}
  p.m_phone = 1;
  REQUIRE(((n = t.find(p.m_phone)) && n->value.m_phone == p.m_phone));
  p.m_phone = 2;
  REQUIRE(((n = t.find(p.m_phone)) && n->value.m_phone == p.m_phone));
  p.m_phone = 4;
  REQUIRE(((n = t.find(p.m_phone)) && n->value.m_phone == p.m_phone));
  p.m_phone = 10;
  REQUIRE(((n = t.find(p.m_phone)) && n->value.m_phone == p.m_phone));

  // Attempting to find non-existing items
  p.m_phone = 3;
  REQUIRE(!t.find(p.m_phone));
  p.m_phone = 0;
  REQUIRE(!t.find(p.m_phone));
}

TEST_SUITE_END();
