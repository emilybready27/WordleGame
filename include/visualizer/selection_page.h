#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "tile.h"
#include "page.h"

namespace wordle {

namespace visualizer {

class SelectionPage : public Page {
 public:
  SelectionPage() = default;
  SelectionPage(double margin, double window_width, double window_height,
            size_t num_guesses, size_t num_letters);
  
  std::string GetType() const override;
  void Draw() const override;

  bool HasMouseEvent(const ci::vec2& position) const;
  size_t GetMouseEvent(const ci::vec2& position) const;
  
  void AddGame(size_t game_index);

  void SetSelectionColor(size_t idx, const std::string& color);
  const std::vector<std::vector<Tile>> &GetSelection() const;

 private:
  std::vector<std::vector<Tile>> selection_;
};

} // namespace visualizer

} // namespace wordle
