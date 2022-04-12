#pragma once

#include <string>
#include "board.h"

namespace wordle {

/** Game state of a single instance of Wordle. */
class Game {
 public:
  /**
   * Constructs a Game with the given attributes.
   * @param answer std::string
   * @param num_guesses size_t
   * @param num_letters size_t
   * @param default_color std::string
   * @param semi_correct_color std::string
   * @param correct_color std::string
   * @param incorrect_color std::string
   */
  Game(const std::string& answer,
       size_t num_guesses,
       size_t num_letters,
       const std::string& default_color,
       const std::string& semi_correct_color,
       const std::string& correct_color,
       const std::string& incorrect_color);

  /**
   * Updates the Game state to reflect the given guess.
   * @param guess std::string
   */
  void Evaluate(const std::string& guess);
  
  /**
   * Determines if the current Game is complete: has already won
   * or has no more guesses left.
   * @return bool
   */
  bool IsComplete() const;
  
  /**
   * Determines if the Game was a win or a loss.
   * @return bool
   */
  bool HasWon() const;
  
  /**
   * Retrieves the current Board.
   * @return Board
   */
  const Board& GetBoard() const;

  /**
   * Retrieves the Game's answer Word.
   * @return Word
   */
  const Word& GetAnswer() const;
  
  /**
   * Retrieves the Game's color.
   * @return 
   */
  const std::string& GetColor() const;
  
 private:
  /**
   * Board consisting of all the Words played.
   */
  Board board_;
  
  /**
   * Correct answer for the Game.
   */
  Word answer_;
  
  /**
   * Current number of guesses taken.
   */
  size_t guess_count_;
  
  /**
   * Total number of guesses allowed.
   */
  size_t num_guesses_;
  
  /**
   * Total number of letters in a guess.
   */
  size_t num_letters_;
  
  /**
   * False if Game lost or not completed.
   * True if Game completed and won.
   */
  bool has_won_;

  /**
   * Color indicating Game is won.
   */
  std::string correct_color_;
  
  /**
   * Color indicating Game is started.
   */
  std::string semi_correct_color_;
  
  /**
   * Color indicating Game is lost.
   */
  std::string incorrect_color_;
};

} // namespace wordle