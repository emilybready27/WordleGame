#include <catch2/catch.hpp>
#include "core/board.h"

using wordle::Board;
using wordle::Word;

TEST_CASE("Test Update method simple") {
  Board board = Board(6, 3, "gray", "yellow", "green");
  std::string answer = "cat";

  SECTION("No correct letters") {
    board.UpdateBoard("pin", answer);
    Word word = Word("pin", "gray");
    REQUIRE(board.GetLastWord() == word);
  }
  
  SECTION("One semi-correct letter") {
    board.UpdateBoard("top", answer);
    Word word = Word("top", "gray");
    word.SetColor(0, "yellow");
    REQUIRE(board.GetLastWord() == word);
  }

  SECTION("One correct letter") {
    board.UpdateBoard("met", answer);
    Word word = Word("met", "gray");
    word.SetColor(2, "green");
    REQUIRE(board.GetLastWord() == word);
  }

  SECTION("One correct letter, one semi-correct letter") {
    board.UpdateBoard("art", answer);
    Word word = Word("art", "gray");
    word.SetColor(0, "yellow");
    word.SetColor(2, "green");
    REQUIRE(board.GetLastWord() == word);
  }

  SECTION("Two correct letters") {
    board.UpdateBoard("bat", answer);
    Word word = Word("bat", "gray");
    word.SetColor(1, "green");
    word.SetColor(2, "green");
    REQUIRE(board.GetLastWord() == word);
  }

  SECTION("Three correct letters") {
    board.UpdateBoard("cat", answer);
    Word word = Word("cat", "green");
    REQUIRE(board.GetLastWord() == word);
  }
}

TEST_CASE("Test Update method repeated 'c'") {
  Board board = Board(6, 5, "gray", "yellow", "green");
  std::string answer = "catch";
  
  SECTION("One semi-correct 'c'") {
    board.UpdateBoard("laces", answer);
    Word word = Word("laces", "gray");
    word.SetColor(1, "green");
    word.SetColor(2, "yellow");
    REQUIRE(board.GetLastWord() == word);
  }
  
  SECTION("One correct 'c'") {
    board.UpdateBoard("catty", answer);
    Word word = Word("catty", "gray");
    word.SetColor(0, "green");
    word.SetColor(1, "green");
    word.SetColor(2, "green");
    REQUIRE(board.GetLastWord() == word);
  }
  
  SECTION("One correct 'c', one semi-correct 'c'") {
    board.UpdateBoard("cacti", answer);
    Word word = Word("cacti", "gray");
    word.SetColor(0, "green");
    word.SetColor(1, "green");
    word.SetColor(2, "yellow");
    word.SetColor(3, "yellow");
    REQUIRE(board.GetLastWord() == word);
  }
  
  SECTION("Two correct 'c's") {
    board.UpdateBoard("catch", answer);
    Word word = Word("catch", "green");
    REQUIRE(board.GetLastWord() == word);
  }
}