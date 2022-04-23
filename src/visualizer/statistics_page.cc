#include "visualizer/statistics_page.h"


namespace wordle {

namespace visualizer {

StatisticsPage::StatisticsPage(double margin, double window_width, double window_height) {
  title_box_ = Tile("Statistics", "gray", ci::Rectf(ci::vec2(margin, margin),
                                                    ci::vec2(window_width - margin, margin + 100)));
  
  statistics_box_ = Tile(" ", "gray", ci::Rectf(ci::vec2(margin, 2*margin + 100),
                                                ci::vec2(window_width - margin, margin + 450)));

  double width = statistics_box_.GetBounds().getWidth();
  games_played_box_ = Tile("Games\nPlayed:\n0", "gray",
                           ci::Rectf(ci::vec2(margin, 2*margin + 100),
                                     ci::vec2(margin + width/4, 2*margin + 300)));
  win_percentage_box_ = Tile("Win\n%:\n0.00", "gray",
                             ci::Rectf(ci::vec2(margin + width/4, 2*margin + 100),
                                       ci::vec2(margin + width/2, 2*margin + 300)));
  current_streak_box_ = Tile("Current\nStreak:\n0", "gray",
                             ci::Rectf(ci::vec2(margin + width/2, 2*margin + 100),
                                       ci::vec2(margin + 3*width/4, 2*margin + 300)));
  max_streak_box_ = Tile("Max\nStreak:\n0", "gray",
                         ci::Rectf(ci::vec2(margin + 3*width/4, 2*margin + 100),
                                   ci::vec2(margin + width, 2*margin + 300)));
  //guess_distribution_box_;
}
    
void StatisticsPage::Draw(const Statistics& statistics) {
  games_played_box_.SetLabel("Games\nPlayed:\n" + std::to_string(statistics.GetGamesPlayed()));
  win_percentage_box_.SetLabel("Win\n%:\n" + std::to_string(statistics.GetWinPercentage()));
  current_streak_box_.SetLabel("Current\nStreak:\n" + std::to_string(statistics.GetCurrentStreak()));
  max_streak_box_.SetLabel("Max\nStreak:\n" + std::to_string(statistics.GetMaxStreak()));

//  for (size_t i = 0; i < wordle_.GetNumGuesses(); i++) {
//    message += std::to_string(i + 1) + ": " + std::to_string(wordle_.GetStatistics().GetGuessDistribution(i)) + "\n";
//  }

  DrawTile(title_box_);
  DrawTile(statistics_box_);
  DrawTile(games_played_box_);
  DrawTile(win_percentage_box_);
  DrawTile(current_streak_box_);
  DrawTile(max_streak_box_);
}

void StatisticsPage::DrawTile(const Tile& tile) const {
  ci::gl::color(ci::Color(&(tile.GetColor()[0])));
  ci::gl::drawSolidRect(tile.GetBounds());
  ci::gl::drawStringCentered(tile.GetLabel(),
                             tile.GetBounds().getCenter() - ci::vec2(0, tile.GetBounds().getHeight() / 4),
                             ci::Color("black"),
                             ci::Font("Arial", 50.0));
}


} // namespace visualizer

} // namespace wordle