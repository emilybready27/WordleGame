#pragma once

#include <string>

namespace wordle {
    
class Letter {
 public:
  Letter();
  Letter(char letter, const std::string& color);

  bool operator==(const Letter &other) const;
  void SetLetter(char letter);
  char ToString() const;
  void SetColor(const std::string& color);
  const std::string& GetColor() const;
  
 private:
  char letter_;
  std::string color_;
};

} // namespace wordle