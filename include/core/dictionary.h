#pragma once

#include <string>
#include <vector>

namespace wordle {

/** Collection of valid words for a Wordle game. */
class Dictionary {
 public:
  /**
   * Default constructor.
   */
  Dictionary() = default;
  
  /**
   * Constructs a shuffled vector of words from the text file at the given path.
   * @param path_to_dictionary std::string
   */
  Dictionary(const std::string& path_to_dictionary);
  
  /**
   * Retrieves a word from the shuffled vector of words.
   * @return std::string
   */
  const std::string& GenerateNewWord();
  
  /**
   * Determines if the given target word is in the Dictionary.
   * @param target std::string
   * @return bool
   */
  bool Contains(const std::string& target) const;
  
  /**
   * Retrieves the number of words in the Dictionary.
   * @return size_t
   */
  size_t GetNumWords() const;
  
 private:
  /**
   * Vector of valid words.
   */
  std::vector<std::string> words_;
  
  /**
   * Iterator through the vector of words.
   */
  size_t word_counter_{};
  
  /**
   * Number of words in Dictionary.
   */
  size_t num_words_{};
};

} // namespace wordle