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

TEST_CASE("Test FindLetter method") {
  Word word = Word("start", "gray");
  
  SECTION("Correct result for 's'") {
    REQUIRE(word.FindLetter(Letter('s', "gray")) == std::vector<size_t>{0});
  }

  SECTION("Correct result for 't'") {
    REQUIRE(word.FindLetter(Letter('t', "gray")) == std::vector<size_t>{1,4});
  }

  SECTION("Correct result for 'a'") {
    REQUIRE(word.FindLetter(Letter('a', "gray")) == std::vector<size_t>{2});
  }

  SECTION("Correct result for 'r'") {
    REQUIRE(word.FindLetter(Letter('r', "gray")) == std::vector<size_t>{3});
  }
  
  SECTION("Correct result for 'f") {
    REQUIRE(word.FindLetter(Letter('f', "gray")).empty());
  }
}