#include "core/word.h"

namespace wordle {

Word::Word(size_t length, const std::string& default_color) {
  // initialize Word as empty
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

size_t Word::CountOccurrences(char target) const {
  size_t count = 0;
  
  for (const Letter& letter : letters_) {
    if (letter.ToChar() == target) {
      count++;
    }
  }
  
  return count;
}

size_t Word::CountCorrectOccurrences(char target, const std::string& correct_color) const {
  size_t count = 0;
  
  for (const Letter& letter : letters_) {
    if (letter.ToChar() == target && letter.GetColor() == correct_color) {
      count++;
    }
  }
  
  return count;
}

std::vector<size_t> Word::FindOccurrences(const Letter& target) const {
  // indices of occurrences of target in word, empty if none
  std::vector<size_t> indices;
  
  for (size_t i = 0; i < length_; i++) {
    if (letters_[i] == target) {
      indices.push_back(i);
    }
  }
  
  return indices;
}

const std::string& Word::ToString() const {
  return word_;
}

const std::vector<Letter> &Word::GetLetters() const {
  return letters_;
}

const Letter& Word::GetLetter(size_t index) const {
  return letters_[index];
}

void Word::SetColor(size_t index, const std::string &color) {
  letters_[index].SetColor(color);
}

const std::string &Word::GetColor(size_t index) {
  return letters_[index].GetColor();
}

} // namespace wordle