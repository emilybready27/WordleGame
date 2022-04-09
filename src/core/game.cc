#include "core/game.h"

namespace wordle {

Game::Game(const std::string &answer) {
  board_ = Board();
  answer_ = answer;
  guess_count_ = 0;
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
  return guess_count_ == 6; // TODO: magic number 6
}

bool Game::IsWon() const {
  return guess_count_ < 6 && board_.GetLastWord() == answer_;
}

const std::string &Game::ProcessInput(const std::string &input) {
  return answer_;
}


} // namespace wordle