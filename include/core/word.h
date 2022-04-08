#pragma once

#include <vector>
#include "letter.h"

namespace wordle {
    
class Word {
 public:
  Word();
  Word(const std::vector<Letter>& letters);
  
  void SetWordLetters(const std::vector<Letter>& letters);
  const std::vector<Letter>& GetWordLetters() const;
  void SetIsEmpty(bool is_empty);
  bool GetIsEmpty() const;
  
 private:
  std::vector<Letter> letters_;
  bool is_empty_;
  // TODO: add string representation
};

} // namespace wordle