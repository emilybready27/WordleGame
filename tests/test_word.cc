#include <catch2/catch.hpp>
#include "core/word.h"

using wordle::Word;
using wordle::Letter;

TEST_CASE("Test Word construction") {
  Word word_1 = Word(5, "gray");
  Word word_2 = Word("start", "gray");
  std::vector<Letter> letters = {Letter('s', "gray"),
                                 Letter('t', "gray"),
                                 Letter('a', "gray"),
                                 Letter('r', "gray"),
                                 Letter('t', "gray")};
  Word word_3 = Word(letters);
  
  SECTION("Correct vector of default letters") {
    std::vector<Letter> default_letters(5, Letter('_', "gray"));
    REQUIRE(word_1.GetLetters() == default_letters);
  }
  
  SECTION("Correct vector of letters") {
    REQUIRE(word_2.GetLetters() == letters);
  }
  
  SECTION("Correct string construction") {
    REQUIRE(word_3.ToString() == "start");
  }
}

TEST_CASE("Test CountOccurrences method") {
  Word word = Word("start", "gray");
  
  SECTION("Correct result for 's'") {
    REQUIRE(word.CountOccurrences('s') == 1);
  }

  SECTION("Correct result for 't'") {
    REQUIRE(word.CountOccurrences('t') == 2);
  }

  SECTION("Correct result for 'f'") {
    REQUIRE(word.CountOccurrences('f') == 0);
  }
}

TEST_CASE("Test CountCorrectOccurrences method") {
  Word word = Word("start", "gray");
  word.SetColor(0, "green");
  word.SetColor(1, "green");

  SECTION("Correct result for 's'") {
    REQUIRE(word.CountCorrectOccurrences('s', "green") == 1);
  }

  SECTION("Correct result for 't'") {
    REQUIRE(word.CountCorrectOccurrences('t', "green") == 1);
  }

  SECTION("Correct result for 'f'") {
    REQUIRE(word.CountCorrectOccurrences('f', "green") == 0);
  }
}

TEST_CASE("Test FindOccurrences method") {
  Word word = Word("start", "gray");
  
  SECTION("Correct result for 's'") {
    REQUIRE(word.FindOccurrences(Letter('s', "gray")) == std::vector<size_t>{0});
  }

  SECTION("Correct result for 't'") {
    REQUIRE(word.FindOccurrences(Letter('t', "gray")) == std::vector<size_t>{1, 4});
  }

  SECTION("Correct result for 'a'") {
    REQUIRE(word.FindOccurrences(Letter('a', "gray")) == std::vector<size_t>{2});
  }

  SECTION("Correct result for 'r'") {
    REQUIRE(word.FindOccurrences(Letter('r', "gray")) == std::vector<size_t>{3});
  }
  
  SECTION("Correct result for 'f") {
    REQUIRE(word.FindOccurrences(Letter('f', "gray")).empty());
  }
}