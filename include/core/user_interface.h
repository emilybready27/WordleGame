#pragma once

#include <vector>
#include "game.h"

namespace wordle {

class UserInterface {
 public:
  UserInterface();
  
  void Print(const std::string& message);
  void PrintInColor(const Board& board);
  void Prompt(const std::vector<Game>& games);
  const std::string& GetResponse();
  
 private:
  std::string response_;
  
};

} // namespace wordle