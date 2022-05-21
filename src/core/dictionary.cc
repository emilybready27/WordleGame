#include <fstream>
#include <algorithm>
#include <random>
#include "core/dictionary.h"

namespace wordle {

Dictionary::Dictionary(const std::string& path_to_dictionary) {
  words_ = std::vector<std::string>();
  
  // read in each word on a new line
  std::ifstream file(path_to_dictionary);
  std::string word;
  while (std::getline(file, word)) {
    words_.push_back(word);
  }
  
  // shuffle the order in which words are generated
  std::shuffle(words_.begin(), words_.end(), std::mt19937(std::random_device()()));
  word_counter_ = 0;
  num_words_ = words_.size();
}

bool Dictionary::Contains(const std::string &target) const {
  // return true if any element in words_ equals target
  return std::any_of(words_.begin(),
                     words_.end(),
                     [&target](const std::string& word){return word == target;});
}

const std::string& Dictionary::GenerateNewWord() {
  // if all words are already used once, restart from beginning
  if (word_counter_ == num_words_) {
    word_counter_ = 0;
  }
  return words_[word_counter_++];
}

size_t Dictionary::GetNumWords() const {
  return num_words_;
}

}