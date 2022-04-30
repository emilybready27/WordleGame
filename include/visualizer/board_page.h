#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "tile.h"
#include "core/game.h"
#include "page.h"

namespace wordle {

namespace visualizer {

/** The WordleApp Page used to display the board and play the game. */
class BoardPage : public Page {
 public:
  BoardPage() = default;
  BoardPage(double margin, double window_width, double window_height,
            size_t num_guesses, size_t num_letters, const std::vector<char>& letters);
  
  void Draw() const override;
  bool HasMouseEvent(const ci::vec2& position) const override;
  size_t GetMouseEvent(const ci::vec2& position) const override;

  void Update(const Game& game);
  void Reset();
  void ResetBoardRow(size_t row);
  void SetBoardTileLabel(size_t i, size_t j, const std::string& label);
  void SetSubmitTileColor(const std::string& color);

 private:
  Tile answer_box_;
  Tile home_box_;
  std::vector<std::vector<Tile>> board_;
  std::vector<std::vector<Tile>> keyboard_;
  Tile backspace_;

  size_t num_guesses_;
  std::vector<char> letters_;
  std::map<char, std::string> color_map_;
  
  void ConstructBoard(double margin, double window_width, double window_height,
                      size_t num_guesses, size_t num_letters);
  void ConstructKeyboard(double margin, double window_width, double window_height);
  void ConstructRow1(double margin, double tile_width, double tile_height);
  void ConstructRow2(double margin, double tile_width, double tile_height);
  void ConstructRow3(double margin, double tile_width, double tile_height);
  
};

} // namespace visualizer

} // namespace wordle
