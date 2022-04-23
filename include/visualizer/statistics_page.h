#pragma once

#include "cinder/gl/gl.h"
#include "tile.h"
#include "core/statistics.h"

namespace wordle {

namespace visualizer {

class StatisticsPage {
public:
    StatisticsPage() = default;
    StatisticsPage(double margin, double window_width, double window_height);
    
    void Draw(const Statistics& statistics);
    void DrawTile(const Tile& tile) const;
    
private:
    Tile title_box_;
    Tile statistics_box_;
    Tile games_played_box_;
    Tile win_percentage_box_;
    Tile current_streak_box_;
    Tile max_streak_box_;
    Tile guess_distribution_box_;
    
    // TODO: Histogram histogram_
};

} // namespace visualizer

} // namespace wordle
