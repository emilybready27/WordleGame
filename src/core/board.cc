#include <map>
#include "core/board.h"

using wordle::Letter;

namespace wordle {

Board::Board() {
  words_ = std::vector<Word>(6); // TODO: magic number 6
  word_count_ = 0;
}

Board::Board(const std::vector<Word> &words) {
  words_ = words;
  word_count_ = words_.size();
}

void Board::UpdateBoard(const std::string& guess, const std::string& answer) {
  Word guess_word = Word(guess); // by default, mark all letters as gray
  Word answer_word = Word(answer);

  // find correct letters and correct position first
  for (size_t i = 0; i < 5; i++) { // TODO: magic number 5
    if (guess_word.GetLetter(i) == answer_word.GetLetter(i)) {
      guess_word.SetColor(i, "green"); // TODO: hide color literal
    }
  }

  std::map<char, std::vector<size_t>> guess_letters;
  std::map<char, std::vector<size_t>> answer_letters;
  std::vector<char> keys;

  for (size_t i = 0; i < 5; i++) {
    const char guess_letter = guess_word.GetLetter(i).ToString();

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
        // found green letter
        if (guess_idx == answer_idx) {
          break;
        }

        // color letter yellow, else leave gray
        if (guess_idx != answer_idx && color_count < answer_count
            && guess_word.GetColor(guess_idx) != "green") {
          guess_word.SetColor(guess_idx, "yellow"); // TODO: hide color literal
          color_count++;
        }
      }
    }
  }

  words_[word_count_++] = guess_word;
}

size_t Board::GetLetterCount(const Word& word, char target) const {
  size_t count = 0;
  for (const Letter& letter : word.GetWord()) {
    if (letter.ToString() == target) {
      count++;
    }
  }
  return count;
}

size_t Board::GetCorrectLetterCount(const Word &word, char target) const {
  size_t count = 0;
  for (const Letter& letter : word.GetWord()) {
    if (letter.ToString() == target && letter.GetColor() == "green") {
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