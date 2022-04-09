#pragma once

#include <string>
#include "board.h"

namespace wordle {

class Game {
 public:
  Game(const std::string& answer);
  
  const std::string& GetAnswer() const;
  size_t GetGuessCount() const;
  bool IsComplete() const;
  
 private:
  Board board_;
  std::string answer_;
  size_t guess_count_;
};

} // namespace wordle