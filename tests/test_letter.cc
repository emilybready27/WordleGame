#include <catch2/catch.hpp>
#include "core/letter.h"

using wordle::Letter;

TEST_CASE("Test Letter equals override") {
  Letter guess = Letter('a', "green");
  Letter guesss = Letter('a', "green");
  Letter blank = Letter('_', "gray");
  Letter correct = Letter('a', "gray");
  
  SECTION("Test equal") {
    REQUIRE(guess.ToChar() == guesss.ToChar());
  }

  SECTION("Test unequal") {
    REQUIRE(!(guess.ToChar() == blank.ToChar()));
  }
  
  SECTION("Test unequal") {
    REQUIRE(guess.ToChar() == correct.ToChar());
  }
}