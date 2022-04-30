#include "visualizer/board_page.h"

namespace wordle {

namespace visualizer {

BoardPage::BoardPage(double margin, double window_width, double window_height,
                     size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;
  
  answer_box_ = Tile(" ", "black",
                     ci::Rectf(ci::vec2(margin + tile_size + margin/2, 925),
                               ci::vec2(window_width - margin, 1025)));
  home_box_ = Tile("home", "orange",
                   ci::Rectf(ci::vec2(margin, 925),
                             ci::vec2(margin + tile_size, 1025)));

  num_guesses_ = 0;
  for (size_t i = 0; i < num_guesses; i++) {
    board_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_letters; j++) {
      ci::vec2 coords = ci::vec2((1.3)*margin + (tile_size + margin/3)*j,
                                 margin + (tile_size + margin/3)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      board_[i].emplace_back(" ", "gray", square);
    }
  }
  
//  ConstructKeyboard(margin, window_width, window_height);
}

void BoardPage::Draw() const {
  DrawTile(home_box_);

  for (size_t i = 0; i < board_.size(); i++) {
    for (size_t j = 0; j < board_[i].size(); j++) {
      if (board_[i][j].GetColor() == "gray" && board_[i][j].GetLabel() == " ") {
        DrawTile(board_[i][j], (float) 0.5, (float) 0.5, (float) 0.5); // medium gray
      } else if (board_[i][j].GetColor() == "gray" && num_guesses_ >= i + 1) {
        DrawTile(board_[i][j], (float) 0.3, (float) 0.3, (float) 0.3); // dark gray
      } else {
        DrawTile(board_[i][j]);
      }
    }
  }

  // only visible when game is complete
  DrawTile(answer_box_);
}

bool BoardPage::HasMouseEvent(const ci::vec2& position) const {
  return IsInBounds(position, home_box_.GetBounds());
}

size_t BoardPage::GetMouseEvent(const ci::vec2& position) const {
  return 0; // only action is to return home
}

void BoardPage::Update(const Game& game) {
  Reset();

  num_guesses_++;
  for (size_t i = 0; i < game.GetGuessCount(); i++) {
    for (size_t j = 0; j < 5; j++) {
      const Letter &letter = game.GetBoard().GetWords()[i].GetLetter(j);
      board_[i][j].SetLabelAndColor(std::string(1, letter.ToChar()), letter.GetColor());
    }
  }

  if (game.IsComplete()) { // display answer
    answer_box_.SetLabelAndColor(game.GetAnswer().ToString(), game.GetColor());
  }
}

void BoardPage::Reset() {
  for (size_t i = 0; i < 6; i++) {
    ResetBoardRow(i);
  }
  
  answer_box_.SetLabelAndColor(" ", "black");
}

void BoardPage::ResetBoardRow(size_t row) {
  for (size_t col = 0; col < 5; col++) {
    board_[row][col].SetLabelAndColor(" ", "gray");
  }
}

void BoardPage::SetBoardTileLabel(size_t i, size_t j, const std::string &label) {
  board_[i][j].SetLabel(label);
}

//void BoardPage::ConstructKeyboard(double margin, double window_width, double window_height) {
//  keyboard_.emplace_back(std::vector<Tile>);
//  for (size_t i = 0; i < 10; i++) {
//    keyboard_[0].emplace_back(" ", "gray", )
//  }
//}

} // namespace visualizer

} // namespace wordle
