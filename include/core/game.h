#pragma once

#include <string>
#include "board.h"

namespace wordle {

class Game {
 public:
  Game(const std::string& answer);
  
  const std::string& GetAnswer() const;
  size_t GetGuessCount() const;
  void IncrementGuessCount();
  bool IsComplete() const;
  bool IsWon() const;
  const std::string& ProcessInput(const std::string& input);
  
 private:
  Board board_;
  std::string answer_;
  size_t guess_count_;
};

} // namespace wordle