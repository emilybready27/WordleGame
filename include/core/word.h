#pragma once

#include <vector>
#include "letter.h"

namespace wordle {
    
class Word {
 public:
  Word();
  Word(const std::string& word);
  Word(const std::vector<Letter>& letters);
  
  void SetWordLetters(const std::vector<Letter>& letters);
  const std::vector<Letter>& GetWord() const;
  const std::string& ToString() const;
  void SetIsEmpty(bool is_empty);
  bool GetIsEmpty() const;
  void SetColor(size_t index, const std::string& color);
  const std::string& GetColor(size_t index);
  const Letter& GetLetter(size_t index) const;
  
  // Find all occurrences of target in the word
  std::vector<size_t> FindLetter(const Letter& target);
  
 private:
  std::vector<Letter> letters_;
  std::string word_;
  bool is_empty_;
  // TODO: add string representation
};

} // namespace wordle