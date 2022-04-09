#include <iostream>
#include <Windows.h>
#include "core/user_interface.h"

namespace wordle {
    
UserInterface::UserInterface() {
}

void UserInterface::Prompt(const std::vector<Game> &games) {
}

const std::string &UserInterface::GetResponse() {
  std::cout << ">";
  std::cin >> response_;
  return response_;
}

void UserInterface::Print(const std::string& message) {
  std::cout << message << std::endl;
}

void UserInterface::PrintInColor(const Board& board) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  
  for (const Word& word : board.GetWords()) {
    for (const Letter& letter : word.GetWordLetters()) {

      // set color of text by color of letter
      if (letter.GetColor() == "green") {
        SetConsoleTextAttribute(hConsole, 0x02);
      } else if (letter.GetColor() == "yellow") {
        SetConsoleTextAttribute(hConsole, 0x06);
      } else {
        SetConsoleTextAttribute(hConsole, 0x08);
      }
      
      std::cout << letter.GetLetter();
    }
    std::cout << std::endl;
  }
  SetConsoleTextAttribute(hConsole, 0x07);
}

} // namespace wordle