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
  
  void Draw() const override;
  void Update(const Statistics& statistics);

  bool HasMouseEvent(const ci::vec2& position) const override;
  size_t GetMouseEvent(const ci::vec2& position) const override;
    
 private:
  Tile title_box_;
  Tile statistics_box_;
  Tile games_played_box_;
  Tile win_percentage_box_;
  Tile current_streak_box_;
  Tile max_streak_box_;
  Tile home_box_;
  
  Tile guess_distribution_box_;
  std::vector<Tile> counts_;
  std::vector<Tile> shaded_bars_;
  std::vector<Tile> labels_;
  Tile label_box_;
};

} // namespace visualizer

} // namespace wordle
