#pragma once

#include <vector>
#include "tile.h"

namespace wordle {

namespace visualizer {

class SelectionPage {
 public:
  SelectionPage() = default;
  SelectionPage(double margin, double window_width, double window_height,
            size_t num_guesses, size_t num_letters);
  
  void AddGame(size_t game_index);

  void SetSelectionTileColor(size_t idx, const std::string& color);
  const Tile &GetHomeBox() const;
  const std::vector<std::vector<Tile>> &GetSelection() const;

 private:
  std::vector<std::vector<Tile>> selection_;
  Tile home_box_;
};

} // namespace visualizer

} // namespace wordle
