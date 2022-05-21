#include "core/letter.h"

namespace wordle {

wordle::Letter::Letter(char letter, const std::string &color) {
  letter_ = letter;
  color_ = color;
}

bool Letter::operator==(const Letter &other) const {
  return this->letter_ == other.letter_ && this->color_ == other.color_;
}

char Letter::ToChar() const {
  return letter_;
}

void Letter::SetColor(const std::string &color) {
  color_ = color;
}

const std::string &Letter::GetColor() const {
  return color_;
}

} // namespace wordle