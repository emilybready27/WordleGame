#include "core/board.h"

namespace wordle {

Board::Board() {
  words_ = std::vector<Word>(6); // TODO: magic number 6
}

Board::Board(const std::vector<Word> &words) {
  words_ = words;
}

void Board::SetWords(const std::vector<Word> &words) {
  words_ = words;
}

const std::vector<Word>& Board::GetWords() const {
  return words_;
}

} // namespace wordle