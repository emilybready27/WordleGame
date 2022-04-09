#include "core/game.h"

namespace wordle {

Game::Game(const std::string &answer) {
  board_ = Board();
  answer_ = answer;
  guess_count_ = 0;
  has_won_ = false;
}

const std::string &Game::GetAnswer() const {
  return answer_;
}

size_t Game::GetGuessCount() const {
  return guess_count_;
}

void Game::IncrementGuessCount() {
  guess_count_++;
}

bool Game::IsComplete() const {
  return guess_count_ == 6 || has_won_; // TODO: magic number 6
}

bool Game::HasWon() const {
  return has_won_;
}

// Note: at this point, we know the input is in the dictionary
void Game::ProcessWord(const std::string &word) {
  guess_count_++;
  board_.UpdateBoard(word, answer_);
  has_won_ = (board_.GetLastWord() == answer_);
}

std::string Game::GetBoardString() const {
  return board_.GetBoardString();
}


} // namespace wordle