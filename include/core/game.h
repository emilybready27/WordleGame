#pragma once

#include <string>
#include "board.h"

namespace wordle {

class Game {
 public:
  Game(const std::string& answer);
  
  const std::string& GetAnswerString() const;
  const Word& GetAnswer() const;
  size_t GetGuessCount() const;
  bool IsComplete() const;
  bool HasWon() const;
  void Evaluate(const std::string& guess);
  const Board& GetBoard() const;
  
 private:
  Board board_;
  Word answer_;
  size_t guess_count_;
  bool has_won_;
};

} // namespace wordle