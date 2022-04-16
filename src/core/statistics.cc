#include <algorithm>
#include "core/statistics.h"

namespace wordle {
    
Statistics::Statistics(size_t num_guesses) {
  games_played_ = 0;
  games_won_ = 0;
  win_percentage_ = 0;
  current_streak_ = 0;
  max_streak_ = 0;
  
  guess_distribution_ = std::vector<size_t>(num_guesses, 0);
}

void Statistics::Update(const Game& game) {
  games_played_++;
  games_won_ += game.HasWon();
  win_percentage_= (double) games_won_ / games_played_;
  
  current_streak_ = (game.HasWon()) ? current_streak_ + 1 : 0;
  max_streak_ = std::max(current_streak_, max_streak_);
  
  if (game.HasWon()) {
    guess_distribution_[game.GetGuessCount() - 1]++;
  }
}

size_t Statistics::GetGamesPlayed() const {
  return games_played_;
}

double Statistics::GetWinPercentage() const {
  return win_percentage_;
}

size_t Statistics::GetCurrentStreak() const {
  return current_streak_;
}

size_t Statistics::GetMaxStreak() const {
  return max_streak_;
}

size_t Statistics::GetGuessDistribution(size_t index) const {
  return guess_distribution_[index];
}

const std::vector<size_t>& Statistics::GetGuessDistribution() const {
  return guess_distribution_;
}

} // namespace wordle