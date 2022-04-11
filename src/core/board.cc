#include <map>
#include "core/board.h"

using wordle::Letter;

namespace wordle {

Board::Board(size_t num_rows, size_t num_columns,
             const std::string& default_color,
             const std::string& semi_correct_color,
             const std::string& correct_color) {
  
  word_count_ = 0;
  num_rows_ = num_rows;
  num_columns_ = num_columns;
  words_ = std::vector<Word>(num_rows_, Word(num_columns, default_color));
  
  default_color_ = default_color;
  semi_correct_color_ = semi_correct_color;
  correct_color_ = correct_color;
}

void Board::UpdateBoard(const std::string& guess, const std::string& answer) {
  Word guess_word = Word(guess, default_color_);
  Word answer_word = Word(answer, default_color_);

  // map each distinct letter in guess to indices of occurrences of that letter in guess
  std::map<char, std::vector<size_t>> guess_indices;
  std::vector<char> distinct_letters;

  for (const Letter& letter : guess_word.GetLetters()) {
    // if not already in map, find occurrences of letter in guess
    if (guess_indices.count(letter.ToChar()) == 0) {
      guess_indices[letter.ToChar()] = guess_word.FindOccurrences(letter);
      distinct_letters.push_back(letter.ToChar());
    }
  }

  // find any correct letters in correct position, mark as correct
  for (size_t i = 0; i < num_columns_; i++) {
    if (guess_word.GetLetter(i).ToChar() == answer_word.GetLetter(i).ToChar()) {
      guess_word.SetColor(i, correct_color_);
    }
  }
  
  // find any correct letters in incorrect position, mark as semi-correct
  for (const char letter: distinct_letters) {
    size_t num_colored = guess_word.CountCorrectOccurrences(letter, correct_color_);
    size_t num_total = answer_word.CountOccurrences(letter);

    // mark at most (num_total - num_colored) other occurrences as semi-correct,
    // starting from left to right
    for (const size_t guess_idx: guess_indices[letter]) {
      if (guess_word.GetColor(guess_idx) != correct_color_ && num_colored < num_total) {
        guess_word.SetColor(guess_idx, semi_correct_color_);
        num_colored++;
      }
    }
  }

  words_[word_count_++] = guess_word;
}

const std::vector<Word>& Board::GetWords() const {
  return words_;
}

const Word& Board::GetLastWord() const {
  return words_[word_count_ - 1];
}

} // namespace wordle