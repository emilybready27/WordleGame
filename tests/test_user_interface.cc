#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>
#include "core/user_interface.h"

using wordle::UserInterface;
using wordle::Board;

TEST_CASE("Test getting user input") {
  UserInterface user_interface = UserInterface();

  SECTION("Handle simple input") {
    std::stringstream input("start");
    std::string response = user_interface.GetResponse(input);
    REQUIRE(response == "start");
  }
  
  SECTION("Handle mixed case input") {
    std::stringstream input("StArT");
    std::string response = user_interface.GetResponse(input);
    REQUIRE(response == "start");
  }

  SECTION("Handle leading and trailing spaces") {
    std::stringstream input("   start   ");
    std::string response = user_interface.GetResponse(input);
    REQUIRE(response == "start");
  }

  SECTION("Handle spaces between letters") {
    std::stringstream input(" s t a r t ");
    std::string response = user_interface.GetResponse(input);
    REQUIRE(response == "start");
  }
  
  SECTION("Handle non-alphabetical characters") {
    std::stringstream input("?/~8#");
    std::string response = user_interface.GetResponse(input);
    REQUIRE(response == "?/~8#");
  }
  
}

TEST_CASE("Test printing output") {
  UserInterface user_interface = UserInterface();
  
  SECTION("Print method works") {
    std::stringstream output;
    user_interface.Print(output, "guess");
    REQUIRE(output.str() == "guess");
  }

  SECTION("PrintLn method works") {
    std::stringstream output;
    user_interface.PrintLn(output, "guess");
    REQUIRE(output.str() == "guess\n");
  }

  SECTION("PrintBoard method works") {
    Board board = Board(6, 5, "gray", "yellow", "green");
    board.UpdateBoard("guess", "start");
    
    std::stringstream output;
    user_interface.PrintBoard(output, board, "gray", "yellow", "green");
    
    REQUIRE(output.str() == "guess\n"
                            "_____\n"
                            "_____\n"
                            "_____\n"
                            "_____\n"
                            "_____\n");
  }
}