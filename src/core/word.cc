#include "core/word.h"

namespace wordle {

Word::Word() {
  letters_ = std::vector<Letter>(5); // TODO: magic number 5
  is_empty_ = true;
}

Word::Word(const std::vector<Letter> &letters) {
  letters_ = letters;
  is_empty_ = false;
}

void Word::SetWordLetters(const std::vector<Letter> &letters) {
  letters_ = letters;
}

const std::vector<Letter> &Word::GetWordLetters() const {
  return letters_;
}

void Word::SetIsEmpty(bool is_empty) {
  is_empty_ = is_empty;
}

bool Word::GetIsEmpty() const {
  return is_empty_;
}

} // namespace wordle