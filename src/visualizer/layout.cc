#include "visualizer/layout.h"

namespace wordle {

namespace visualizer {
    
Layout::Layout(double window_width,
               double window_height,
               double margin,
               size_t num_guesses,
               size_t num_letters,
               const std::string& default_color,
               const std::string& semi_correct_color,
               const std::string& correct_color,
               const std::string& incorrect_color) {

  window_width_ = window_width;
  window_height_ = window_height;
  margin_ = margin;
  num_guesses_= num_guesses;
  num_letters_ = num_letters;
  default_color_ = default_color;
  semi_correct_color_ = semi_correct_color;
  correct_color_ = correct_color;
  incorrect_color_ = incorrect_color;
  
  ConstructBoard();
  ConstructGames();
}

void Layout::ConstructBoard() {
  double tile_size = (window_width_ - 4*margin_) / num_letters_;
  for (size_t i = 0; i < num_guesses_; i++) {
    board_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_letters_; j++) {
      ci::vec2 coords = ci::vec2(margin_ + (tile_size + margin_/2)*j,
                                 margin_ + (tile_size + margin_/2)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      board_[i].emplace_back(" ", default_color_, square);
    }
  }
}

void Layout::ConstructGames() {
  games_ = std::vector<Tile>();
}

void Layout::AddGameTile(size_t game_index) {
  Tile tile = Tile(std::to_string(game_index + 1),
                   default_color_,
                   board_[game_index / 5][game_index % 5].GetSquare()); // TODO: magic number, handle > 30 games
  games_.push_back(tile);
}

void Layout::DrawBoard() const {
  for (size_t i = 0; i < num_guesses_; i++) {
    for (size_t j = 0; j < num_letters_; j++) {
      DrawTile(board_[i][j]);
    }
  }
}

void Layout::DrawBoard(const Game& game) {
  ResetBoardTiles();
  
  for (size_t i = 0; i < game.GetGuessCount(); i++) {
    for (size_t j = 0; j < board_[i].size(); j++) {
      const Letter &letter = game.GetBoard().GetWords()[i].GetLetter(j);
      board_[i][j].SetLabelAndColor(std::string(1, letter.ToChar()), letter.GetColor());
    }
  }
  
  DrawBoard();
}

void Layout::DrawGameSelection() const {
  for (size_t i = 0; i < games_.size(); i++) {
    DrawTile(games_[i]);
  }
}

void Layout::DrawTile(const Tile& tile) const {
  ci::gl::color(ci::Color(&(tile.GetColor()[0])));
  ci::gl::drawSolidRect(tile.GetSquare());
  ci::gl::drawString(tile.GetLabel(), tile.GetSquare().getCenter() - ci::vec2(15.0, 15.0),
                     ci::Color("black"), ci::Font("Arial", 50.0));
}

void Layout::SetBoardTileLabel(size_t row, size_t col, const std::string& label) {
  board_[row][col].SetLabel(label);
}

void Layout::SetBoardTileColor(size_t row, size_t col, const std::string &color) {
  board_[row][col].SetColor(color);
}

void Layout::ResetBoardTiles() {
  for (size_t i = 0; i < board_.size(); i++) {
    ResetBoardTiles(i);
  }
}

void Layout::ResetBoardTiles(size_t row) {
  for (size_t col = 0; col < board_[row].size(); col++) {
    SetBoardTileColor(row, col, default_color_);
    SetBoardTileLabel(row, col, " ");
  }
}

void Layout::SetGameTileColor(size_t idx, const std::string &color) {
  games_[idx].SetColor(color);
}

} // namespace visualizer

} // namespace wordle
