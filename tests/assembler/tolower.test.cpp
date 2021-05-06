#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"
#include "../../src/montador/util.h"

TEST_CASE("should not modify original string") {
  std::string str = "Hello WOrld";

  CHECK_EQ("hello world", toLower(str));
  CHECK_EQ("Hello WOrld", str);

  str = "N&1";
  CHECK_EQ("n&1", toLower(str));
  CHECK_EQ("N&1", str);
}
