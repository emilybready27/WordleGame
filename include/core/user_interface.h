#pragma once

#include <vector>
#include <map>
#include "game.h"

namespace wordle {

class UserInterface {
 public:
  UserInterface();
  
  void Print(const std::string& message);
  void PrintInColor(const Board& board, const std::string& default_color,
                    const std::string& semi_correct_color, const std::string& correct_color);
  const std::string& GetResponse();
  
 private:
  std::string response_;
  std::map<std::string, int> colors_;
};

} // namespace wordle