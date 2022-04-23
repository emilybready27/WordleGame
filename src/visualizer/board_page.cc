#include "visualizer/board_page.h"

namespace wordle {

namespace visualizer {

BoardPage::BoardPage(double margin, double window_width, double window_height,
                     size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;
  
  answer_box_ = Tile(" ", "gray",
                     ci::Rectf(ci::vec2(margin + tile_size + margin/2, 1025),
                               ci::vec2(window_width - margin, 1125)));
  home_box_ = Tile("Home", "gray",
                   ci::Rectf(ci::vec2(margin, 1025),
                             ci::vec2(margin + tile_size, 1125)));

  for (size_t i = 0; i < num_guesses; i++) {
    board_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_letters; j++) {
      ci::vec2 coords = ci::vec2(margin + (tile_size + margin/2)*j,
                                 margin + (tile_size + margin/2)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      board_[i].emplace_back(" ", "gray", square);
    }
  }
}

void BoardPage::Draw() const {
  DrawTile(home_box_);

  for (size_t i = 0; i < board_.size(); i++) {
    for (size_t j = 0; j < board_[i].size(); j++) {
      DrawTile(board_[i][j]);
    }
  }
}

void BoardPage::Draw(const Game& game) {
  ResetBoardTiles();

  for (size_t i = 0; i < game.GetGuessCount(); i++) {
    for (size_t j = 0; j < 5; j++) {
      const Letter &letter = game.GetBoard().GetWords()[i].GetLetter(j);
      board_[i][j].SetLabelAndColor(std::string(1, letter.ToChar()), letter.GetColor());
    }
  }

  Draw();
}

void BoardPage::DrawTile(const Tile& tile) const {
  ci::gl::color(ci::Color(&(tile.GetColor()[0])));
  ci::gl::drawSolidRect(tile.GetBounds());
  ci::gl::drawStringCentered(tile.GetLabel(),
                             tile.GetBounds().getCenter() - ci::vec2(0, tile.GetBounds().getHeight() / 4),
                             ci::Color("black"),
                             ci::Font("Arial", 50.0));
}

void BoardPage::ResetBoardTiles() {
  for (size_t i = 0; i < 6; i++) {
    ResetBoardTiles(i);
  }
}

void BoardPage::ResetBoardTiles(size_t row) {
  for (size_t col = 0; col < 5; col++) {
    board_[row][col].SetLabel(" ");
    board_[row][col].SetColor("gray");
  }
}

void BoardPage::DrawAnswer(const std::string& answer, const std::string& color) {
  answer_box_.SetLabelAndColor(answer, color);
  DrawTile(answer_box_);
}

void BoardPage::SetBoardTileLabel(size_t i, size_t j, const std::string &label) {
  board_[i][j].SetLabel(label);
}

void BoardPage::SetBoardTileColor(size_t i, size_t j, const std::string &color) {
  board_[i][j].SetColor(color);
}

const Tile &BoardPage::GetAnswerBox() const {
  return answer_box_;
}

const Tile &BoardPage::GetHomeBox() const {
  return home_box_;
}

const std::vector<std::vector<Tile>> &BoardPage::GetBoard() const {
  return board_;
}

} // namespace visualizer

} // namespace wordle
