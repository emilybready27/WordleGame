#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "tile.h"

namespace wordle {

namespace visualizer {

class HomePage {
 public:
  HomePage() = default;
  HomePage(double margin, double window_width, double window_height);
  
  void Draw() const;
  void DrawTile(const Tile& tile) const;
  
  const Tile &GetWelcomeBox() const;
  const Tile &GetNewGameBox() const;
  const Tile &GetOldGameBox() const;
  const Tile &GetInstructionsBox() const;
  const Tile &GetStatisticsBox() const;
  
 private:
  Tile welcome_box_;
  Tile new_game_box_;
  Tile old_game_box_;
  Tile instructions_box_;
  Tile statistics_box_;
};

} // namespace visualizer

} // namespace wordle
