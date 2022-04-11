#include "core/game.h"

namespace wordle {

Game::Game(const std::string &answer, size_t num_guesses, size_t num_letters, const std::string& default_color,
           const std::string& semi_correct_color, const std::string& correct_color) {
  guess_count_ = 0;
  num_guesses_ = num_guesses;
  num_letters_ = num_letters;
  board_ = Board(num_guesses_, num_letters_, default_color, semi_correct_color, correct_color);
  answer_ = Word(answer, default_color);
  has_won_ = false;
}

const std::string &Game::GetAnswerString() const {
  return answer_.ToString();
}

const Word& Game::GetAnswer() const {
  return answer_;
}

size_t Game::GetGuessCount() const {
  return guess_count_;
}

bool Game::IsComplete() const {
  return guess_count_ == num_guesses_ || has_won_;
}

bool Game::HasWon() const {
  return has_won_;
}

// Note: at this point, we know the input is in the dictionary
void Game::Evaluate(const std::string &guess) {
  guess_count_++;
  board_.UpdateBoard(guess, answer_.ToString());
  has_won_ = (board_.GetLastWord().ToString() == answer_.ToString());
}

const Board& Game::GetBoard() const {
  return board_;
}


} // namespace wordle