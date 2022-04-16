#pragma once

#include <vector>
#include "game.h"
#include "user_interface.h"
#include "dictionary.h"
#include "statistics.h"

namespace wordle {

/** Instance of the game Wordle. */
class Wordle {
 public:
  /**
   * Initializes Wordle.
   */
  Wordle();
  
  /**
   * Begins console-based game play with options to:
   * 1. start a new game
   * 2. visit a previous game
   * 3. view the instructions
   * 4. view the statistics
   * 5. quit
   */
  void Play();
  
 private:
  const size_t kNumGuesses = 6;
  const size_t kNumLetters = 5;
  const std::string kDefaultColor = "gray";
  const std::string kSemiCorrectColor = "light_yellow";
  const std::string kCorrectColor = "light_green";
  const std::string kIncorrectColor = "light_red";
  const std::string kPathToDictionary =
          R"(C:\Users\Mary\Desktop\Cinder\my-projects\final-project-ebready2\resources\dictionary.txt)";
  
  /**
   * Vector of Game instances.
   */
  std::vector<Game> games_;
  
  /**
   * Used for inputs and outputs.
   */
  UserInterface user_interface_;
  
  /**
   * Stores the valid words that can be played.
   */
  Dictionary dictionary_;
  
  /**
   * Keeps track of relevant stats.
   */
  Statistics statistics_;
  
  /**
   * Number of games played.
   */
  size_t game_count_;
  
  /**
   * Boolean to continue playing or not.
   */
  bool has_quit_;
  
  /**
   * Begins a new game of Wordle.
   */
  void PlayNewGame();
  
  /**
   * Returns to a previous game to view or complete.
   */
  void PlayPastGame();
  
  /**
   * Plays the game at the given index until termination or interrupt.
   * @param size_t index
   */
  void PlayGame(size_t index);
  
  /**
   * Prints the selection of games played.
   */
  void PrintGameSelection();

  /**
   * Prints the instructions for the user.
   */
  void PrintInstructions();
  
  /**
   * Prints the user statistics.
   */
  void PrintStatistics();
};

} // namespace wordle