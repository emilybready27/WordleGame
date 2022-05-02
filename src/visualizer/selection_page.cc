#include "visualizer/selection_page.h"

namespace wordle {

namespace visualizer {

SelectionPage::SelectionPage(double margin, double window_width, double window_height,
                             size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;

  num_games_ = 0;
  num_rows_ = num_guesses + 2;
  num_cols_ = num_letters;
  max_num_games_ = num_rows_ * num_cols_;
  
  for (size_t i = 0; i < num_rows_; i++) {
    game_indices_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_cols_; j++) {
      ci::vec2 coords = ci::vec2((1.3)*margin + (tile_size + margin/3)*j,
                                 margin + (tile_size + margin/3)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      game_indices_[i].emplace_back(" ", "black", square); // initially invisible
    }
  }

  home_box_ = Tile("home", "orange",
                   ci::Rectf(ci::vec2(margin, window_height - margin - tile_size),
                             ci::vec2(margin + (window_width - 4*margin) / 5, window_height - margin)));
}

void SelectionPage::Draw() const {
  for (size_t i = 0; i < num_rows_; i++) {
    for (size_t j = 0; j < num_cols_; j++) {
      DrawTile(game_indices_[i][j]);
    }
  }
  
  DrawTile(home_box_);
}

bool SelectionPage::HasMouseEvent(const ci::vec2& position) const {
  for (size_t i = 0; i < game_indices_.size(); i++) {
    for (size_t j = 0; j < game_indices_[i].size(); j++) {
      if (IsInBounds(position, game_indices_[i][j].GetBounds()) && game_indices_[i][j].GetColor() != "black") {
        return true;
      }
    }
  }
  return IsInBounds(position, home_box_.GetBounds());
}

size_t SelectionPage::GetMouseEvent(const ci::vec2& position) const {
  if (IsInBounds(position, home_box_.GetBounds())) {
    return num_rows_ * num_cols_;
  }
  
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
  if (num_games_ == num_rows_ * num_cols_) {
    ReconstructGameIndices();
  }
  
  game_indices_[game_index / num_cols_][game_index % num_cols_].SetLabel(std::to_string(game_index + 1));
  game_indices_[game_index / num_cols_][game_index % num_cols_].SetColor("gray");
  num_games_++;
}

void SelectionPage::SetSelectionColor(size_t index, const std::string &color) {
  game_indices_[index / num_cols_][index % num_cols_].SetColor(color);
}

size_t SelectionPage::GetMaxNumGames() const {
  return max_num_games_;
}

void SelectionPage::ReconstructGameIndices() {
  size_t num_rows = num_rows_ * 2;
  size_t num_cols = num_cols_ * 2;
  std::vector<std::vector<Tile>> game_indices;

  double tile_size = game_indices_[0][0].GetBounds().getWidth() / 2;
  double margin = 100;
  
  for (size_t i = 0; i < num_rows; i++) {
    game_indices.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_cols; j++) {
      ci::vec2 coords = ci::vec2(margin + (tile_size + margin/5)*j,
                                 margin + (tile_size + margin/5)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      game_indices[i].emplace_back(" ", "black", square); // initially invisible

      if (i*num_cols + j < num_rows_ * num_cols_) {
        size_t index = i*num_cols + j;
        const std::string& label = game_indices_[index / num_cols_][index % num_cols_].GetLabel();
        const std::string& color = game_indices_[index / num_cols_][index % num_cols_].GetColor();
        game_indices[i][j].SetLabelAndColor(label, color);
      }
    }
  }

  num_rows_ = num_rows;
  num_cols_ = num_cols;
  max_num_games_ = num_rows_ * num_cols_;
  game_indices_ = game_indices;
}

} // namespace visualizer

} // namespace wordle
