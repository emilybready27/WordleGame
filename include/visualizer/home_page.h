#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "tile.h"
#include "page.h"

namespace wordle {

namespace visualizer {

class HomePage : public Page {
 public:
  HomePage() = default;
  HomePage(double margin, double window_width, double window_height);
  
  void Draw() const override;

  bool HasMouseEvent(const ci::vec2& position) const override;
  size_t GetMouseEvent(const ci::vec2& position) const override;
  
  const Tile &GetWelcomeBox() const;
  const Tile &GetNewGameBox() const;
  const Tile &GetOldGameBox() const;
  const Tile &GetInstructionsBox() const;
  const Tile &GetStatisticsBox() const;
  
 private:
  Tile title_box_;
  Tile new_game_box_;
  Tile old_game_box_;
  Tile instructions_box_;
  Tile statistics_box_;
};

} // namespace visualizer

} // namespace wordle
