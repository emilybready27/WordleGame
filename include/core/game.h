#pragma once

#include <string>
#include "board.h"

namespace wordle {

class Game {
 public:
  Game(const std::string& answer, size_t num_guesses, size_t num_letters, const std::string& default_color,
       const std::string& semi_correct_color, const std::string& correct_color);
  
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
  size_t num_guesses_;
  size_t num_letters_;
  bool has_won_;
};

} // namespace wordle