#pragma once

#include "word.h"

namespace wordle {

/** Board of Words from the game play. */
class Board {
 public:
  /**
   * Default constructor.
   */
  Board() = default;
  
  /**
   * Constructs a game Board with the given attributes.
   * @param num_rows size_t
   * @param num_columns size_t
   * @param default_color std::string
   * @param semi_correct_color std::string
   * @param correct_color std::string
   */
  Board(size_t num_rows, size_t num_columns,
        const std::string& default_color,
        const std::string& semi_correct_color,
        const std::string& correct_color);
  
  /**
   * Adds the new guess to the Board and colors the appropriate Letters.
   * @param guess std::string
   * @param answer std::string
   */
  void UpdateBoard(const std::string& guess, const std::string& answer);
  
  /**
   * Retrieves the vector of Words on the Board.
   * @return std::vector<Word>
   */
  const std::vector<Word>& GetWords() const;
  
  /**
   * Retrieves the final, most recently played Word on the Board.
   * @return Word
   */
  const Word& GetLastWord() const;
  
 private:
  /**
   * Vector of Words on the Board.
   */
  std::vector<Word> words_;
  
  /**
   * Number of words on the Board.
   */
  size_t word_count_{};
  
  /**
   * Number of rows in the Board.
   */
  size_t num_rows_{};
  
  /**
   * Number of columns in the Board.
   */
  size_t num_columns_{};
  
  /**
   * Default coloring of Letters.
   */
  std::string default_color_;
  
  /**
   * Coloring of correct Letters in incorrect positions.
   */
  std::string semi_correct_color_;
  
  /**
   * Coloring of correct Letters in correct positions.
   */
  std::string correct_color_;
};

} // namespace wordle