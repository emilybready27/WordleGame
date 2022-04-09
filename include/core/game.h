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
  bool HasWon() const;
  void ProcessWord(const std::string& input);
  std::string GetBoardString() const;
  
 private:
  Board board_;
  std::string answer_;
  size_t guess_count_;
  bool has_won_;
};

} // namespace wordle