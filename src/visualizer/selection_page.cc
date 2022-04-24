#include "visualizer/selection_page.h"

namespace wordle {

namespace visualizer {

SelectionPage::SelectionPage(double margin, double window_width, double window_height,
                             size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;

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

std::string SelectionPage::GetType() const {
  return "selection";
}

void SelectionPage::Draw() const {
  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 5; j++) {
      DrawTile(selection_[i][j]);
    }
  }
}

bool SelectionPage::HasMouseEvent(const ci::vec2& position) const {
  for (size_t i = 0; i < selection_.size(); i++) {
    for (size_t j = 0; j < selection_[i].size(); j++) {
      if (IsInBounds(position, selection_[i][j].GetBounds()) && selection_[i][j].GetColor() != "black") {
        return true;
      }
    }
  }
  return false;
}

size_t SelectionPage::GetMouseEvent(const ci::vec2& position) const {
  for (size_t i = 0; i < selection_.size(); i++) {
    for (size_t j = 0; j < selection_[i].size(); j++) {
      if (IsInBounds(position, selection_[i][j].GetBounds()) && selection_[i][j].GetColor() != "black") {
        return i*selection_[i].size() + j;
      }
    }
  }
  
  // never executes
  return 0;
}

void SelectionPage::AddGame(size_t game_index) {
  selection_[game_index / 5][game_index % 5].SetLabel(std::to_string(game_index + 1));
  selection_[game_index / 5][game_index % 5].SetColor("gray");
}

const std::vector<std::vector<Tile>> &SelectionPage::GetSelection() const {
  return selection_;
}

void SelectionPage::SetSelectionColor(size_t idx, const std::string &color) {
  selection_[idx / 5][idx % 5].SetColor(color);
}

} // namespace visualizer

} // namespace wordle
