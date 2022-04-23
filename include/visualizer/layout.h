#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "tile.h"
#include "core/game.h"

namespace wordle {

namespace visualizer {

class Layout {
 public:
  Layout() = default;
  
  Layout(double window_width,
         double window_height,
         double margin,
         size_t num_guesses,
         size_t num_letters,
         const std::string &default_color,
         const std::string &semi_correct_color,
         const std::string &correct_color,
         const std::string &incorrect_color);
  
  void DrawBoard() const;
  void DrawBoard(const Game& game);
  void DrawGameSelection() const;
  
  void AddGameTile(size_t game_index);
  
  void SetBoardTileLabel(size_t row, size_t col, const std::string& label);
  void SetBoardTileColor(size_t row, size_t col, const std::string& color);
  void ResetBoardTiles();
  void ResetBoardTiles(size_t row);
  
  void SetGameTileColor(size_t idx, const std::string& color);
    
 private:
  double window_width_;
  double window_height_;
  double margin_;
  size_t num_guesses_;
  size_t num_letters_;
  std::string default_color_;
  std::string semi_correct_color_;
  std::string correct_color_;
  std::string incorrect_color_;

  std::vector<std::vector<Tile>> board_;
  std::vector<Tile> games_;
  //std::vector<std::vector<Tile>> keyboard_;
  
  void ConstructBoard();
  void ConstructGames();
  void DrawTile(const Tile& tile) const;
    
};

} // namespace visualizer

} // namespace wordle
