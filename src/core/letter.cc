#include "core/letter.h"

namespace wordle {

wordle::Letter::Letter() {
  letter_ = '_';
  color_ = "gray";
}

wordle::Letter::Letter(char letter, const std::string &color) {
  letter_ = letter;
  color_ = color;
}

bool Letter::operator==(const Letter &other) const {
  return this->letter_ == other.letter_;
}

void Letter::SetLetter(char letter) {
  letter_ = letter;
}

char Letter::ToString() const {
  return letter_;
}

void Letter::SetColor(const std::string &color) {
  color_ = color;
}

const std::string &Letter::GetColor() const {
  return color_;
}

} // namespace wordle