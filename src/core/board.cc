#include "core/board.h"

namespace wordle {

Board::Board() {
  words_ = std::vector<Word>(6); // TODO: magic number 6
  word_count_ = 0;
}

Board::Board(const std::vector<Word> &words) {
  words_ = words;
  word_count_ = words_.size();
}

void Board::UpdateBoard(const std::string& word, const std::string& answer) {
  word_count_++;
  words_[word_count_ - 1] = Word(word); // by default, mark all letters incorrect

  // find correct letters and/or correct position
  // TODO: magic number 5
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {

      // correct letter in correct position
      if (word[i] == answer[j] && i == j) {
        words_[word_count_ - 1].SetColor(i, "green"); // TODO: hide color literal
        break;

        // correct letter in incorrect position
      } else if (word[i] == answer[j]) {
        words_[word_count_ - 1].SetColor(i, "yellow"); // TODO: hide color literal
      }
    }
  }
}

void Board::SetWords(const std::vector<Word> &words) {
  words_ = words;
}

const std::vector<Word>& Board::GetWords() const {
  return words_;
}

const std::string& Board::GetLastWord() const {
  return words_[word_count_ - 1].GetWord();
}

} // namespace wordle