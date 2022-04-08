#pragma once

#include <string>

namespace wordle {
    
class Letter {
 public:
  Letter();
  Letter(char letter, const std::string& color);
  
  void SetLetter(char letter);
  char GetLetter() const;
  void SetColor(const std::string& color);
  const std::string& GetColor() const;
  
 private:
  char letter_;
  std::string color_;
};

} // namespace wordle