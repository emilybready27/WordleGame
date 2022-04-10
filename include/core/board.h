#pragma once

#include "word.h"

namespace wordle {

class Board {
 public:
  Board() = default;
  Board(size_t num_rows, size_t num_columns, const std::string& default_color,
        const std::string& semi_correct_color, const std::string& correct_color);
  
  void UpdateBoard(const std::string& word, const std::string& answer);
  void SetWords(const std::vector<Word>& words);
  const std::vector<Word>& GetWords() const;
  const std::string& GetLastWord() const;
  
 private:
  std::vector<Word> words_;
  size_t word_count_{};
  size_t num_rows_{};
  size_t num_columns_{};
  std::string default_color_;
  std::string semi_correct_color_;
  std::string correct_color_;

  size_t GetLetterCount(const Word &word, char target) const;
  size_t GetCorrectLetterCount(const Word &word, char target) const;
};

} // namespace wordle