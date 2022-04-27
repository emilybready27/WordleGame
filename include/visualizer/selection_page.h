#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "tile.h"
#include "page.h"

namespace wordle {

namespace visualizer {

/** The WordleApp Page with a display of the games played so far. */
class SelectionPage : public Page {
 public:
  SelectionPage() = default;
  SelectionPage(double margin, double window_width, double window_height,
                size_t num_guesses, size_t num_letters);
  
  void Draw() const override;
  bool HasMouseEvent(const ci::vec2& position) const override;
  size_t GetMouseEvent(const ci::vec2& position) const override;
  
  void AddGame(size_t game_index);
  void SetSelectionColor(size_t idx, const std::string& color);

 private:
  std::vector<std::vector<Tile>> selection_;

  // TODO: handle > 30 games
};

} // namespace visualizer

} // namespace wordle
