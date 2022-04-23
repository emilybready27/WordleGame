#pragma once

#include <vector>
#include "tile.h"

namespace wordle {

namespace visualizer {

class BoardPage {
 public:
  BoardPage() = default;
  BoardPage(double margin, double window_width, double window_height,
            size_t num_guesses, size_t num_letters);

  void SetBoardTileLabel(size_t i, size_t j, const std::string& label);
  void SetBoardTileColor(size_t i, size_t j, const std::string& color);
  void SetBoardTile(size_t i, size_t j, const std::string& label, const std::string& color);
  void SetAnswerBox(const std::string& label, const std::string& color);
  
  const Tile &GetAnswerBox() const;
  const Tile &GetHomeBox() const;
  const std::vector<std::vector<Tile>> &GetBoard() const;

 private:
  std::vector<std::vector<Tile>> board_;
  Tile answer_box_;
  Tile home_box_;
  // TODO: std::vector<std::vector<Tile>> keyboard_;
};

} // namespace visualizer

} // namespace wordle
