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

bool Game::IsComplete() const {
  return guess_count_ == 6; // TODO: magic number 6
}

} // namespace wordle