#include <map>
#include "core/board.h"

using wordle::Letter;

namespace wordle {

Board::Board(size_t num_rows, size_t num_columns, const std::string& default_color,
             const std::string& semi_correct_color, const std::string& correct_color) {
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

  // find correct letters and correct position first
  for (size_t i = 0; i < num_columns_; i++) {
    if (guess_word.GetLetter(i) == answer_word.GetLetter(i)) {
      guess_word.SetColor(i, correct_color_);
    }
  }

  std::map<char, std::vector<size_t>> guess_letters;
  std::map<char, std::vector<size_t>> answer_letters;
  std::vector<char> keys;

  for (size_t i = 0; i < num_columns_; i++) {
    const char guess_letter = guess_word.GetLetter(i).ToChar();

    // if not already in map, find all indices of occurrences of guess_letter in guess
    if (guess_letters.count(guess_letter) == 0) {
      guess_letters[guess_letter] = guess_word.FindLetter(guess_word.GetLetter(i));
      keys.push_back(guess_letter);
    }

    // if not already in map, find all indices of occurrences of guess_letter in answer
    if (answer_letters.count(guess_letter) == 0) {
      answer_letters[guess_letter] = answer_word.FindLetter(guess_word.GetLetter(i));
    }
  }

  for (const char key: keys) {
    size_t color_count = GetCorrectLetterCount(guess_word, key);
    size_t answer_count = GetLetterCount(answer_word, key);

    for (const size_t guess_idx: guess_letters[key]) {
      for (const size_t answer_idx: answer_letters[key]) {
        // found correct letter
        if (guess_idx == answer_idx) {
          break;
        }

        // mark letter as semi-correct, else leave default color
        if (guess_idx != answer_idx && color_count < answer_count
            && guess_word.GetColor(guess_idx) != correct_color_) {
          guess_word.SetColor(guess_idx, semi_correct_color_);
          color_count++;
        }
      }
    }
  }

  words_[word_count_++] = guess_word;
}

size_t Board::GetLetterCount(const Word& word, char target) const {
  size_t count = 0;
  for (const Letter& letter : word.GetLetters()) {
    if (letter.ToChar() == target) {
      count++;
    }
  }
  return count;
}

size_t Board::GetCorrectLetterCount(const Word &word, char target) const {
  size_t count = 0;
  for (const Letter& letter : word.GetLetters()) {
    if (letter.ToChar() == target && letter.GetColor() == correct_color_) {
      count++;
    }
  }
  return count;
}

void Board::SetWords(const std::vector<Word> &words) {
  words_ = words;
}

const std::vector<Word>& Board::GetWords() const {
  return words_;
}

const std::string& Board::GetLastWord() const {
  return words_[word_count_ - 1].ToString();
}

} // namespace wordle