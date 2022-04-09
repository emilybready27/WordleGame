#include "core/game.h"

namespace wordle {

Game::Game(const std::string &answer) {
  board_ = Board();
  answer_ = answer;
  guess_count_ = 0;
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
  return guess_count_ == 6 || has_won_; // TODO: magic number 6
}

bool Game::HasWon() const {
  return has_won_;
}

// Note: at this point, we know the input is in the dictionary
void Game::Evaluate(const std::string &guess) {
  guess_count_++;
  board_.UpdateBoard(guess, answer_.ToString());
  has_won_ = (board_.GetLastWord() == answer_.ToString());
}

const Board& Game::GetBoard() const {
  return board_;
}


} // namespace wordle