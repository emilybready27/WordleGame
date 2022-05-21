#include <catch2/catch.hpp>
#include "core/dictionary.h"

using wordle::Dictionary;

TEST_CASE("Test Dictionary construction") {
  std::string path = R"(C:\Users\Mary\Desktop\Cinder\my-projects\final-project-ebready2\resources\small_dictionary.txt)";
  Dictionary dictionary = Dictionary(path);
  
  SECTION("Has correct number of words") {
    REQUIRE(dictionary.GetNumWords() == 6);
  }
  
  SECTION("Contains 'laces'") {
    REQUIRE(dictionary.Contains("laces"));
  }

  SECTION("Contains 'candy'") {
    REQUIRE(dictionary.Contains("candy"));
  }

  SECTION("Contains 'catty'") {
    REQUIRE(dictionary.Contains("catty"));
  }

  SECTION("Contains 'cacti'") {
    REQUIRE(dictionary.Contains("cacti"));
  }

  SECTION("Contains 'cache'") {
    REQUIRE(dictionary.Contains("cache"));
  }

  SECTION("Contains 'catch'") {
    REQUIRE(dictionary.Contains("catch"));
  }
}