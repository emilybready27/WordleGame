#include "visualizer/selection_page.h"

namespace wordle {

namespace visualizer {

SelectionPage::SelectionPage(double margin, double window_width, double window_height,
                             size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;

  home_box_ = Tile("Home", "gray",
                   ci::Rectf(ci::vec2(margin, 1025),
                             ci::vec2(margin + tile_size, 1125)));

  for (size_t i = 0; i < num_guesses; i++) {
    selection_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_letters; j++) {
      ci::vec2 coords = ci::vec2(margin + (tile_size + margin/2)*j,
                                 margin + (tile_size + margin/2)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      selection_[i].emplace_back(" ", "black", square);
    }
  }
}

void SelectionPage::Draw() const {
  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 5; j++) {
      DrawTile(selection_[i][j]);
    }
  }
}

void SelectionPage::DrawTile(const Tile& tile) const {
  ci::gl::color(ci::Color(&(tile.GetColor()[0])));
  ci::gl::drawSolidRect(tile.GetBounds());
  ci::gl::drawStringCentered(tile.GetLabel(),
                             tile.GetBounds().getCenter() - ci::vec2(0, tile.GetBounds().getHeight() / 4),
                             ci::Color("black"),
                             ci::Font("Arial", 50.0));
}

void SelectionPage::AddGame(size_t game_index) {
  selection_[game_index / 5][game_index % 5].SetLabel(std::to_string(game_index + 1));
  selection_[game_index / 5][game_index % 5].SetColor("gray");
}

const Tile &SelectionPage::GetHomeBox() const {
  return home_box_;
}

const std::vector<std::vector<Tile>> &SelectionPage::GetSelection() const {
  return selection_;
}

void SelectionPage::SetSelectionColor(size_t idx, const std::string &color) {
  selection_[idx / 5][idx % 5].SetColor(color);
}

} // namespace visualizer

} // namespace wordle
