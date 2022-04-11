#include <catch2/catch.hpp>
#include "core/game.h"

using wordle::Game;

TEST_CASE("Test win") {
  Game game = Game("catch", 6, 5, "gray", "yellow", "green");
  game.Evaluate("laces");
  
  SECTION("Incorrect guess hasn't won") {
    REQUIRE(game.HasWon() == false);
  }

  game.Evaluate("catch");
  
  SECTION("Correct guess has won") {
    REQUIRE(game.HasWon() == true);
  }

  SECTION("Game is complete after win") {
    REQUIRE(game.IsComplete() == true);
  }
}

TEST_CASE("Test loss") {
  Game game = Game("catch", 6, 5, "gray", "yellow", "green");
  game.Evaluate("laces");
  game.Evaluate("candy");
  game.Evaluate("catty");
  game.Evaluate("cacti");
  game.Evaluate("cache");
  
  SECTION("Game isn't complete") {
    REQUIRE(game.IsComplete() == false);
  }

  game.Evaluate("cache");
  
  SECTION("Game is complete") {
    REQUIRE(game.IsComplete() == true);
  }
  
  SECTION("Game hasn't won") {
    REQUIRE(game.HasWon() == false);
  }
}