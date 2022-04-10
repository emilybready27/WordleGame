#include <catch2/catch.hpp>
#include "core/letter.h"

using wordle::Letter;

TEST_CASE("Test Letter equals override") {
  Letter blank = Letter('_', "gray");
  Letter correct = Letter('a', "gray");
  Letter guess = Letter('a', "green");
  
  SECTION("Test equals") {
    REQUIRE(guess == correct);
  }
  
  SECTION("Test not equals") {
    REQUIRE(!(guess == blank));
  }
}