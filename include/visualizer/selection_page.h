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
  
  /**
   * Adds a new tile to the selection of games.
   * @param game_index size_t
   */
  void AddGame(size_t game_index);
  
  /**
   * Sets the color of the selection tile with the given index.
   * @param idx size_t
   * @param color std::string
   */
  void SetSelectionColor(size_t index, const std::string& color);
  
  /**
   * Gets the maximum number of games supported.
   * @return size_t
   */
  size_t GetMaxNumGames() const;

 private:
  Tile home_box_;
  std::vector<std::vector<Tile>> game_indices_;
  size_t num_games_;
  size_t max_num_games_;
  size_t num_rows_;
  size_t num_cols_;
  
  void ReconstructGameIndices();
};

} // namespace visualizer

} // namespace wordle
