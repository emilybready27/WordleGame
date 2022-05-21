#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "tile.h"
#include "page.h"

namespace wordle {

namespace visualizer {

/** The initial WordleApp Page with all user actions. */
class HomePage : public Page {
 public:
  HomePage() = default;
  HomePage(double margin, double window_width, double window_height);

  void Draw() const override;
  bool HasMouseEvent(const ci::vec2& position) const override;
  size_t GetMouseEvent(const ci::vec2& position) const override;
  
 private:
  Tile title_box_;
  Tile new_game_box_;
  Tile old_game_box_;
  Tile instructions_box_;
  Tile statistics_box_;
};

} // namespace visualizer

} // namespace wordle
