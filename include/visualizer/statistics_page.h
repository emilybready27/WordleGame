#pragma once

#include "cinder/gl/gl.h"
#include "tile.h"
#include "core/statistics.h"
#include "page.h"

namespace wordle {

namespace visualizer {

class StatisticsPage : public Page {
 public:
  StatisticsPage() = default;
  StatisticsPage(double margin, double window_width, double window_height);
  
  std::string GetType() const override;
  void Draw() const override;
  void Draw(const Statistics& statistics);
    
 private:
  Tile title_box_;
  Tile statistics_box_;
  Tile games_played_box_;
  Tile win_percentage_box_;
  Tile current_streak_box_;
  Tile max_streak_box_;
  // TODO: Tile guess_distribution_box_;
  // TODO: Tile home_box_;
  
  // TODO: Histogram histogram_
};

} // namespace visualizer

} // namespace wordle
