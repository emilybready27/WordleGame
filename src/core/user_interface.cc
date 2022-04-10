#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <cctype>
#include "core/user_interface.h"

namespace wordle {
    
UserInterface::UserInterface() {
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

void UserInterface::PrintInColor(const Board& board) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  
  for (const Word& word : board.GetWords()) {
    for (const Letter& letter : word.GetWord()) {

      // set color of text by color of letter
      if (letter.GetColor() == "green") {
        SetConsoleTextAttribute(hConsole, 0x02);
      } else if (letter.GetColor() == "yellow") {
        SetConsoleTextAttribute(hConsole, 0x06);
      } else {
        SetConsoleTextAttribute(hConsole, 0x08);
      }
      
      std::cout << letter.ToChar();
    }
    std::cout << std::endl;
  }
  SetConsoleTextAttribute(hConsole, 0x07);
}

} // namespace wordle