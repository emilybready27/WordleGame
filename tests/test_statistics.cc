#include <catch2/catch.hpp>
#include "core/statistics.h"

using wordle::Statistics;
using wordle::Game;

TEST_CASE("Test Update with game won") {
  Statistics statistics = Statistics(6);

  Game game = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  game.Evaluate("catch"); // won
  statistics.Update(game);
  
  SECTION("Correct games played") {
    REQUIRE(statistics.GetGamesPlayed() == 1);
  }
  SECTION("Correct win percentage") {
    REQUIRE(statistics.GetWinPercentage() == 1.0);
  }
  SECTION("Correct current streak") {
    REQUIRE(statistics.GetCurrentStreak() == 1);
  }
  SECTION("Correct max streak") {
    REQUIRE(statistics.GetMaxStreak() == 1);
  }
  SECTION("Correct guess distribution") {
    REQUIRE(statistics.GetGuessDistribution() == std::vector<size_t>{1,0,0,0,0,0});
  }
}

TEST_CASE("Test Update with game lost") {
  Statistics statistics = Statistics(6);

  Game game = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  for (size_t i = 0; i < 6; i++) {
    game.Evaluate("guess");
  } // lost
  statistics.Update(game);

  SECTION("Correct games played") {
    REQUIRE(statistics.GetGamesPlayed() == 1);
  }
  SECTION("Correct win percentage") {
    REQUIRE(statistics.GetWinPercentage() == 0.0);
  }
  SECTION("Correct current streak") {
    REQUIRE(statistics.GetCurrentStreak() == 0);
  }
  SECTION("Correct max streak") {
    REQUIRE(statistics.GetMaxStreak() == 0);
  }
  SECTION("Correct guess distribution") {
    REQUIRE(statistics.GetGuessDistribution() == std::vector<size_t>{0,0,0,0,0,0});
  }
}

TEST_CASE("Test Update with game won then game lost") {
  Statistics statistics = Statistics(6);

  Game game_1 = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  game_1.Evaluate("catch"); // won
  statistics.Update(game_1);
  
  Game game_2 = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  for (size_t i = 0; i < 6; i++) {
    game_2.Evaluate("guess");
  } // lost
  statistics.Update(game_2);

  SECTION("Correct games played") {
    REQUIRE(statistics.GetGamesPlayed() == 2);
  }
  SECTION("Correct win percentage") {
    REQUIRE(statistics.GetWinPercentage() == 0.5);
  }
  SECTION("Correct current streak") {
    REQUIRE(statistics.GetCurrentStreak() == 0);
  }
  SECTION("Correct max streak") {
    REQUIRE(statistics.GetMaxStreak() == 1);
  }
  SECTION("Correct guess distribution") {
    REQUIRE(statistics.GetGuessDistribution() == std::vector<size_t>{1,0,0,0,0,0});
  }
}

TEST_CASE("Test Update with game lost then game won") {
  Statistics statistics = Statistics(6);

  Game game_1 = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  for (size_t i = 0; i < 6; i++) {
    game_1.Evaluate("guess");
  } // lost
  statistics.Update(game_1);

  Game game_2 = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  game_2.Evaluate("catch"); // won
  statistics.Update(game_2);

  SECTION("Correct games played") {
    REQUIRE(statistics.GetGamesPlayed() == 2);
  }
  SECTION("Correct win percentage") {
    REQUIRE(statistics.GetWinPercentage() == 0.5);
  }
  SECTION("Correct current streak") {
    REQUIRE(statistics.GetCurrentStreak() == 1);
  }
  SECTION("Correct max streak") {
    REQUIRE(statistics.GetMaxStreak() == 1);
  }
  SECTION("Correct guess distribution") {
    REQUIRE(statistics.GetGuessDistribution() == std::vector<size_t>{1,0,0,0,0,0});
  }
}

TEST_CASE("Test Update with two games won") {
  Statistics statistics = Statistics(6);

  Game game_1 = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  game_1.Evaluate("catch"); // won
  statistics.Update(game_1);

  Game game_2 = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  game_2.Evaluate("catch"); // won
  statistics.Update(game_2);

  SECTION("Correct games played") {
    REQUIRE(statistics.GetGamesPlayed() == 2);
  }
  SECTION("Correct win percentage") {
    REQUIRE(statistics.GetWinPercentage() == 1.0);
  }
  SECTION("Correct current streak") {
    REQUIRE(statistics.GetCurrentStreak() == 2);
  }
  SECTION("Correct max streak") {
    REQUIRE(statistics.GetMaxStreak() == 2);
  }
  SECTION("Correct guess distribution") {
    REQUIRE(statistics.GetGuessDistribution() == std::vector<size_t>{2,0,0,0,0,0});
  }
}

TEST_CASE("Test Update with two games lost") {
  Statistics statistics = Statistics(6);

  Game game_1 = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  for (size_t i = 0; i < 6; i++) {
    game_1.Evaluate("guess");
  } // lost
  statistics.Update(game_1);

  Game game_2 = Game("catch", 6, 5, "gray", "yellow", "green", "red");
  for (size_t i = 0; i < 6; i++) {
    game_2.Evaluate("guess");
  } // lost
  statistics.Update(game_2);

  SECTION("Correct games played") {
    REQUIRE(statistics.GetGamesPlayed() == 2);
  }
  SECTION("Correct win percentage") {
    REQUIRE(statistics.GetWinPercentage() == 0.0);
  }
  SECTION("Correct current streak") {
    REQUIRE(statistics.GetCurrentStreak() == 0);
  }
  SECTION("Correct max streak") {
    REQUIRE(statistics.GetMaxStreak() == 0);
  }
  SECTION("Correct guess distribution") {
    REQUIRE(statistics.GetGuessDistribution() == std::vector<size_t>{0,0,0,0,0,0});
  }
}