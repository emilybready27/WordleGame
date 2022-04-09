#include <fstream>
#include <algorithm>
#include <random>
#include "core/dictionary.h"

namespace wordle {

Dictionary::Dictionary() {
  words_ = std::vector<std::string>();
  
  // read in each word on a new line
  std::ifstream file(path_to_dictionary_);
  std::string word;
  while (std::getline(file, word)) {
    words_.push_back(word);
  }
  
  // shuffle the order in which words are generated
  std::shuffle(words_.begin(), words_.end(), std::mt19937(std::random_device()()));
  word_counter_ = 0;
}

bool Dictionary::Contains(const std::string &target) const {
  for (const std::string& word : words_) {
    if (word == target) {
      return true;
    }
  }
  
  return false;
}

const std::string& Dictionary::GenerateNewWord() {
  // if all words are already used once, restart from beginning
  if (word_counter_ == words_.size()) {
    word_counter_ = 0;
  }
  return words_[word_counter_++];
}

}