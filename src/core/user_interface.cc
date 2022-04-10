#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <cctype>
#include "core/user_interface.h"

namespace wordle {
    
UserInterface::UserInterface() {
  colors_["black"] = 0;
  colors_["blue"] = 1;
  colors_["green"] = 2;
  colors_["aqua"] = 3;
  colors_["red"] = 4;
  colors_["purple"] = 5;
  colors_["yellow"] = 6;
  colors_["white"] = 7;
  colors_["gray"] = 8;
  colors_["light_blue"] = 9;
  colors_["light_green"] = 10;
  colors_["light_aqua"] = 11;
  colors_["light_red"] = 12;
  colors_["light_purple"] = 13;
  colors_["light_yellow"] = 14;
  colors_["bright_white"] = 15;
}

const std::string &UserInterface::GetResponse() {
  std::cout << ">";
  std::getline(std::cin, response_); // newline-delimited
  
  // remove whitespaces
  response_.erase(remove(response_.begin(), response_.end(), ' '), response_.end());
  
  // convert to lowercase
  std::transform(response_.begin(), response_.end(), response_.begin(),
                 [](char c){ return std::tolower(c); });
  
  return response_;
}

void UserInterface::Print(const std::string& message) {
  std::cout << message << std::endl;
}

void UserInterface::PrintInColor(const Board& board, const std::string& default_color,
                                 const std::string& semi_correct_color, const std::string& correct_color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  
  for (const Word& word : board.GetWords()) {
    for (const Letter& letter : word.GetWord()) {

      // set color of text by color of letter
      if (letter.GetColor() == correct_color) {
        SetConsoleTextAttribute(hConsole, colors_[correct_color]);
      } else if (letter.GetColor() == semi_correct_color) {
        SetConsoleTextAttribute(hConsole, colors_[semi_correct_color]);
      } else {
        SetConsoleTextAttribute(hConsole, colors_[default_color]);
      }
      
      std::cout << letter.ToChar();
    }
    std::cout << std::endl;
  }
  
  SetConsoleTextAttribute(hConsole, colors_["white"]);
}

} // namespace wordle