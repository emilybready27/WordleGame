#include "core/game.h"

namespace wordle {

Game::Game(const std::string &answer,
           size_t num_guesses,
           size_t num_letters,
           const std::string& default_color,
           const std::string& semi_correct_color,
           const std::string& correct_color) {
  
  guess_count_ = 0;
  num_guesses_ = num_guesses;
  num_letters_ = num_letters;
  has_won_ = false;
  
  board_ = Board(num_guesses_, num_letters_, default_color, semi_correct_color, correct_color);
  answer_ = Word(answer, default_color);
}

void Game::Evaluate(const std::string &guess) {
  guess_count_++;
  board_.UpdateBoard(guess, answer_.ToString());
  has_won_ = (board_.GetLastWord().ToString() == answer_.ToString());
}

bool Game::IsComplete() const {
  return guess_count_ == num_guesses_ || has_won_;
}

bool Game::HasWon() const {
  return has_won_;
}

const Board& Game::GetBoard() const {
  return board_;
}

const Word &Game::GetAnswer() const {
  return answer_;
}

} // namespace wordle