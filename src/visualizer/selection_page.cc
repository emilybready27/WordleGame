#include "visualizer/selection_page.h"

namespace wordle {

namespace visualizer {

SelectionPage::SelectionPage(double margin, double window_width, double window_height,
                             size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;

  for (size_t i = 0; i < num_guesses; i++) {
    game_indices_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_letters; j++) {
      ci::vec2 coords = ci::vec2(margin + (tile_size + margin/2)*j,
                                 margin + (tile_size + margin/2)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      game_indices_[i].emplace_back(" ", "black", square); // initially invisible
    }
  }
}

void SelectionPage::Draw() const {
  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 5; j++) {
      DrawTile(game_indices_[i][j]);
    }
  }
}

bool SelectionPage::HasMouseEvent(const ci::vec2& position) const {
  for (size_t i = 0; i < game_indices_.size(); i++) {
    for (size_t j = 0; j < game_indices_[i].size(); j++) {
      if (IsInBounds(position, game_indices_[i][j].GetBounds()) && game_indices_[i][j].GetColor() != "black") {
        return true;
      }
    }
  }
  return false;
}

size_t SelectionPage::GetMouseEvent(const ci::vec2& position) const {
  // returns the index of the game the user selected
  for (size_t i = 0; i < game_indices_.size(); i++) {
    for (size_t j = 0; j < game_indices_[i].size(); j++) {
      if (IsInBounds(position, game_indices_[i][j].GetBounds()) && game_indices_[i][j].GetColor() != "black") {
        return i*game_indices_[i].size() + j;
      }
    }
  }
  
  return 0; // never executes
}

void SelectionPage::AddGame(size_t game_index) {
  game_indices_[game_index / 5][game_index % 5].SetLabel(std::to_string(game_index + 1));
  game_indices_[game_index / 5][game_index % 5].SetColor("gray");
}

void SelectionPage::SetSelectionColor(size_t index, const std::string &color) {
  game_indices_[index / 5][index % 5].SetColor(color);
}

} // namespace visualizer

} // namespace wordle
