#include "core/word.h"

namespace wordle {

Word::Word(size_t length, const std::string& default_color) {
  letters_ = std::vector<Letter>(length, Letter('_', default_color));
  word_ = "";
  length_ = length;
}

Word::Word(const std::string& word, const std::string& default_color) {
  word_ = word;
  length_ = word_.size();
  letters_ = std::vector<Letter>(length_);
  
  for (size_t i = 0; i < length_; i++) {
    letters_[i] = Letter(word[i], default_color);
  }
}

Word::Word(const std::vector<Letter> &letters) {
  letters_ = letters;
  length_ = letters_.size();
  word_ = "";
  
  for (const Letter& letter : letters_) {
    word_ += letter.ToChar();
  }
}

const std::vector<Letter> &Word::GetWord() const {
  return letters_;
}

const std::string& Word::ToString() const {
  return word_;
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
  for (size_t i = 0; i < length_; i++) {
    if (letters_[i] == target) {
      letters.push_back(i);
    }
  }
  return letters;
}

} // namespace wordle