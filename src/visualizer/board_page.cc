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

void BoardPage::SetBoardTileLabel(size_t i, size_t j, const std::string &label) {
  board_[i][j].SetLabel(label);
}

void BoardPage::SetBoardTileColor(size_t i, size_t j, const std::string &color) {
  board_[i][j].SetColor(color);
}

void BoardPage::SetBoardTile(size_t i, size_t j, const std::string &label, const std::string& color) {
  board_[i][j].SetLabelAndColor(label, color);
}

void BoardPage::SetAnswerBox(const std::string &label, const std::string &color) {
  answer_box_.SetLabelAndColor(label, color);
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
