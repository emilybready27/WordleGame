#pragma once

#include <vector>
#include "letter.h"

namespace wordle {
    
class Word {
 public:
  Word() = default;
  Word(size_t length, const std::string& default_color);
  Word(const std::string& word, const std::string& default_color);
  Word(const std::vector<Letter>& letters);
  
  const std::vector<Letter>& GetWord() const;
  const std::string& ToString() const;
  void SetColor(size_t index, const std::string& color);
  const std::string& GetColor(size_t index);
  const Letter& GetLetter(size_t index) const;
  
  // Find all occurrences of target in the word
  std::vector<size_t> FindLetter(const Letter& target);
  
 private:
  std::vector<Letter> letters_;
  std::string word_;
  size_t length_;
};

} // namespace wordle