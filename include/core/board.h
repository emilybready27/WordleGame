#pragma once

#include "word.h"

namespace wordle {

class Board {
 public:
  Board();
  Board(const std::vector<Word>& words);
  
  void UpdateBoard(const std::string& word, const std::string& answer);
  void SetWords(const std::vector<Word>& words);
  const std::vector<Word>& GetWords() const;
  const std::string& GetLastWord() const;
  
 private:
  std::vector<Word> words_;
  size_t word_count_;
};

} // namespace wordle