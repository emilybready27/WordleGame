#pragma once

#include "word.h"

namespace wordle {

class Board {
 public:
  Board();
  Board(const std::vector<Word>& words);
  
  void SetWords(const std::vector<Word>& words);
  const std::vector<Word>& GetWords() const;
  
 private:
  std::vector<Word> words_;
};

} // namespace wordle