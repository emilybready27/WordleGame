#include <iostream>
#include "core/user_interface.h"

namespace wordle {
    
UserInterface::UserInterface() {
}

void UserInterface::Prompt(const std::vector<Game> &games) {
}

const std::string &UserInterface::GetResponse() {
  std::cout << "> ";
  std::cin >> response_;
  return response_;
}

void UserInterface::Print(const std::string& message) {
  std::cout << message << std::endl;
}

} // namespace wordle