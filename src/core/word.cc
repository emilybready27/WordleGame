#include "core/word.h"

namespace wordle {

Word::Word() {
  letters_ = std::vector<Letter>(5); // TODO: magic number 5
  word_ = "";
  is_empty_ = true;
}

Word::Word(const std::string& word) {
  letters_ = std::vector<Letter>(5);
  word_ = word;
  is_empty_ = false;
  
  for (size_t i = 0; i < 5; i++) { // TODO: magic number 5
    letters_[i] = Letter(word[i], "gray");
  }
}

Word::Word(const std::vector<Letter> &letters) {
  letters_ = letters;
  word_ = "";
  is_empty_ = false;
  
  for (const Letter& letter : letters_) {
    word_ += letter.ToString();
  }
}

void Word::SetWordLetters(const std::vector<Letter> &letters) {
  letters_ = letters;
}

const std::vector<Letter> &Word::GetWord() const {
  return letters_;
}

const std::string& Word::ToString() const {
  return word_;
}

void Word::SetIsEmpty(bool is_empty) {
  is_empty_ = is_empty;
}

bool Word::GetIsEmpty() const {
  return is_empty_;
}

void Word::SetColor(size_t index, const std::string &color) {
  letters_[index].SetColor(color);
}

const std::string &Word::GetColor(size_t index) {
  return letters_[index].GetColor();
}

const Letter& Word::GetLetter(size_t index) const {
  return letters_[index];
}

std::vector<size_t> Word::FindLetter(const Letter& target) {
  // find indices of occurrences of target in word, empty if none
  std::vector<size_t> letters;
  for (size_t i = 0; i < 5; i++) {
    if (letters_[i] == target) {
      letters.push_back(i);
    }
  }
  return letters;
}

} // namespace wordle