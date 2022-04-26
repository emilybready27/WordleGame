#include "visualizer/statistics_page.h"

namespace wordle {

namespace visualizer {

StatisticsPage::StatisticsPage(double margin, double window_width, double window_height) {
  title_box_ = Tile("Statistics", "pink", ci::Rectf(ci::vec2(margin, margin),
                                                    ci::vec2(window_width - margin, margin + 100)));
  
  statistics_box_ = Tile(" ", "gray", ci::Rectf(ci::vec2(margin, 1.5*margin + 100),
                                                ci::vec2(window_width - margin, margin + 400)));

  double width = statistics_box_.GetBounds().getWidth();
  games_played_box_ = Tile(" ", "pink", ci::Rectf(ci::vec2(margin, 1.5*margin + 100),
                                                  ci::vec2(margin + width/4, margin + 400)));
  win_percentage_box_ = Tile(" ", "pink", ci::Rectf(ci::vec2(margin + width/4, 1.5*margin + 100),
                                                    ci::vec2(margin + width/2, margin + 400)));
  current_streak_box_ = Tile(" ", "pink", ci::Rectf(ci::vec2(margin + width/2, 1.5*margin + 100),
                                                    ci::vec2(margin + 3*width/4, margin + 400)));
  max_streak_box_ = Tile(" ", "pink", ci::Rectf(ci::vec2(margin + 3*width/4, 1.5*margin + 100),
                                                ci::vec2(margin + width, margin + 400)));
  
  guess_distribution_box_ = Tile(" ", "gray", ci::Rectf(ci::vec2(margin, margin + 500),
                                                        ci::vec2(window_width - margin, margin + 800)));
  
  for (size_t i = 0; i < 6; i++) {
    counts_.emplace_back(std::to_string(0), "gray", ci::Rectf(ci::vec2(margin + i*width/6,
                                                                       margin + 450),
                                                            ci::vec2(margin + (i+1)*width/6,
                                                                     margin + 500)));
    shaded_bars_.emplace_back(" ", "salmon", ci::Rectf(ci::vec2(counts_[i].GetBounds().x1,
                                                               margin + 795),
                                                      ci::vec2(counts_[i].GetBounds().x2,
                                                               margin + 800)));
    labels_.emplace_back(std::to_string(i + 1), "pink", ci::Rectf(ci::vec2(counts_[i].GetBounds().x1,
                                                                           margin + 800),
                                                                  ci::vec2(counts_[i].GetBounds().x2,
                                                                           margin + 850)));
  }
  
  label_box_ = Tile("Guess Distribution", "pink", ci::Rectf(ci::vec2(margin, margin + 850),
                                                              ci::vec2(window_width - margin, margin + 900)));
  home_box_ = Tile("home", "orange", ci::Rectf(ci::vec2(margin, 1025),
                                               ci::vec2(margin + (window_width - 4*margin) / 5, 1125)));
}

std::string StatisticsPage::GetType() const {
  return "statistics";
}

void StatisticsPage::Draw() const {
  DrawTile(title_box_);
  DrawTile(statistics_box_);
  DrawTile(games_played_box_);
  DrawTile(win_percentage_box_);
  DrawTile(current_streak_box_);
  DrawTile(max_streak_box_);
  DrawTile(guess_distribution_box_);
  DrawTile(label_box_);
  DrawTile(home_box_);
  
  for (size_t i = 0; i < counts_.size(); i++) {
    DrawTile(counts_[i]);
    DrawTile(shaded_bars_[i]);
    DrawTile(labels_[i]);
  }
}
    
void StatisticsPage::Draw(const Statistics& statistics) {
  games_played_box_.SetLabel("Games\nPlayed:\n" + std::to_string(statistics.GetGamesPlayed()));
  win_percentage_box_.SetLabel("Win\nPercent:\n" + std::to_string(statistics.GetWinPercentage()));
  current_streak_box_.SetLabel("Current\nStreak:\n" + std::to_string(statistics.GetCurrentStreak()));
  max_streak_box_.SetLabel("Max\nStreak:\n" + std::to_string(statistics.GetMaxStreak()));

  for (size_t i = 0; i < statistics.GetGuessDistribution().size(); i++) {
    size_t win_count = statistics.GetGuessDistribution(i);
    
    // called continuously, only update if there's a change
    if ((int) win_count > std::stoi(counts_[i].GetLabel())) {
      counts_[i].SetLabel(std::to_string(win_count));
      shaded_bars_[i].SetBounds(ci::Rectf(ci::vec2(shaded_bars_[i].GetBounds().x1,
                                                   shaded_bars_[i].GetBounds().y1 - 20),
                                          ci::vec2(shaded_bars_[i].GetBounds().x2,
                                                   shaded_bars_[i].GetBounds().y2)));
    }
  }

  Draw();
}

bool StatisticsPage::HasMouseEvent(const ci::vec2& position) const {
  return IsInBounds(position, home_box_.GetBounds());
}

size_t StatisticsPage::GetMouseEvent(const ci::vec2& position) const {
  return 0;
}

} // namespace visualizer

} // namespace wordle