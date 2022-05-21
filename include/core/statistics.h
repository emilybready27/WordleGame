#pragma once

#include "game.h"

namespace wordle {

/** Relevant statistics for an instance of Wordle. */
class Statistics {
 public:
  /**
   * Default constructor.
   */
  Statistics() = default;
  
  /**
   * Initializes the statistics as empty.
   * @param num_guesses size_t
   */
  Statistics(size_t num_guesses);
    
  /**
   * Updates the statistics based on the completed game.
   */
  void Update(const Game& game);
  
  /**
   * Getters for stats.
   */
  size_t GetGamesPlayed() const;
  double GetWinPercentage() const;
  size_t GetCurrentStreak() const;
  size_t GetMaxStreak() const;
  size_t GetGuessDistribution(size_t index) const;
  const std::vector<size_t>& GetGuessDistribution() const;
  
 private:
  /**
   * Number of games played.
   */
  size_t games_played_{};
  
  /**
   * Number of games won.
   */
  size_t games_won_{};
  
  /**
   * Ratio of games won to games played.
   */
  double win_percentage_{};
  
  /**
   * Current number of games won in a row.
   */
  size_t current_streak_{};
  
  /**
   * Maximum number of games won in a row.
   */
  size_t max_streak_{};
  
  /**
   * Distribution of games based on number of guesses to win.
   */
  std::vector<size_t> guess_distribution_;
};

} // namespace wordle