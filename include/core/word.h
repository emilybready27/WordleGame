#pragma once

#include <vector>
#include "letter.h"

namespace wordle {
    
/** English word representing a guess in game play. */
class Word {
 public:
  /**
   * Default constructor.
   */
  Word() = default;
  
  /**
   * Constructs an empty word and initializes the vector of Letters.
   * @param length size_t
   * @param default_color std::string
   */
  Word(size_t length, const std::string& default_color);
  
  /**
   * Constructs the vector of Letters with a string representation.
   * @param word std::string
   * @param default_color std::string
   */
  Word(const std::string& word, const std::string& default_color);
  
  /**
   * Constructs a string representation of the Letters.
   * @param letters std::vector<Letter>
   */
  Word(const std::vector<Letter>& letters);

  /**
   * Two Words are equal if their Letter vectors are equal.
   * @param other Word
   * @return bool
   */
  bool operator==(const Word &other) const;
  
  /**
   * Counts the number of occurrences of target in the Word.
   * @param target char
   * @return size_t
   */
  size_t CountOccurrences(char target) const;
  
  /**
   * Counts the number of occurrences of target marked correct in the Word.
   * @param target char
   * @param correct_color std::string
   * @return size_t
   */
  size_t CountCorrectOccurrences(char target, const std::string& correct_color) const;

  /**
   * Finds all indices of occurrences of the given Letter in the Word.
   * @param target Letter
   * @return std::vector<size_t>
   */
  std::vector<size_t> FindOccurrences(const Letter& target) const;

  /**
   * Retrieves string representation of Word.
   * @return std::string
   */
  const std::string& ToString() const;
  
  /**
   * Retrieves Letter representation of Word.
   * @return std::vector<Letter>
   */
  const std::vector<Letter>& GetLetters() const;

  /**
   * Retrieves Letter at the given index.
   * @param index size_t
   * @return Letter
   */
  const Letter& GetLetter(size_t index) const;
  
  /**
   * Sets the color of the Letter at the given index.
   * @param index size_t
   * @param color std::string
   */
  void SetColor(size_t index, const std::string& color);
  
  /**
   * Gets the color of the Letter at the given index.
   * @param index size_t
   * @return std::string
   */
  const std::string& GetColor(size_t index);
  
 private:
  /**
   * Letters and associated colors that constitute the Word.
   */
  std::vector<Letter> letters_;
  
  /**
   * String representation of Word.
   */
  std::string word_;
  
  /**
   * Number of characters in the Word.
   */
  size_t length_;
};

} // namespace wordle