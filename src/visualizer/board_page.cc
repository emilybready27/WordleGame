#include "visualizer/board_page.h"

namespace wordle {

namespace visualizer {

BoardPage::BoardPage(double margin, double window_width, double window_height,
                     size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;
  
  answer_box_ = Tile(" ", "black",
                     ci::Rectf(ci::vec2(margin + tile_size + margin/2, 900),
                               ci::vec2(window_width - margin, 1000)));
  home_box_ = Tile("home", "orange",
                   ci::Rectf(ci::vec2(margin, 900),
                             ci::vec2(margin + tile_size, 1000)));

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
  
  ConstructKeyboard(margin, window_width, window_height);
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
  
  for (size_t i = 0; i < keyboard_.size(); i++) {
    for (size_t j = 0; j < keyboard_[i].size(); j++) {
      DrawTile(keyboard_[i][j]);
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

void BoardPage::ConstructKeyboard(double margin, double window_width, double window_height) {
  double tile_width = (window_width - margin - 2.5*margin) / 10;
  double tile_height = (window_height - home_box_.GetBounds().y2 - (2.5)*margin) / 3;
  ConstructRow1(margin, tile_width, tile_height);
  ConstructRow2(margin, tile_width, tile_height);
  ConstructRow3(margin, tile_width, tile_height);
}

void BoardPage::ConstructRow1(double margin, double tile_width, double tile_height) {
  keyboard_.emplace_back(std::vector<Tile>());
  for (size_t i = 0; i < 10; i++) {
    ci::vec2 coords = ci::vec2((0.6)*margin + (tile_width + margin/4)*i,
                               home_box_.GetBounds().y2 + (0.75)*margin);
    ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(tile_width, tile_height));
    keyboard_[0].emplace_back(" ", "gray", key);
  }
  
  keyboard_[0][0].SetLabel("q");
  keyboard_[0][1].SetLabel("w");
  keyboard_[0][2].SetLabel("e");
  keyboard_[0][3].SetLabel("r");
  keyboard_[0][4].SetLabel("t");
  keyboard_[0][5].SetLabel("y");
  keyboard_[0][6].SetLabel("u");
  keyboard_[0][7].SetLabel("i");
  keyboard_[0][8].SetLabel("o");
  keyboard_[0][9].SetLabel("p");
}

void BoardPage::ConstructRow2(double margin, double tile_width, double tile_height) {
  keyboard_.emplace_back(std::vector<Tile>());
  for (size_t i = 0; i < 9; i++) {
    ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*i,
                               home_box_.GetBounds().y2 + (1.1)*margin + tile_height);
    ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(tile_width, tile_height));
    keyboard_[1].emplace_back(" ", "gray", key);
  }

  keyboard_[1][0].SetLabel("a");
  keyboard_[1][1].SetLabel("s");
  keyboard_[1][2].SetLabel("d");
  keyboard_[1][3].SetLabel("f");
  keyboard_[1][4].SetLabel("g");
  keyboard_[1][5].SetLabel("h");
  keyboard_[1][6].SetLabel("j");
  keyboard_[1][7].SetLabel("k");
  keyboard_[1][8].SetLabel("l");
}

void BoardPage::ConstructRow3(double margin, double tile_width, double tile_height) {
  keyboard_.emplace_back(std::vector<Tile>());
  for (size_t i = 0; i < 7; i++) {
    ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*i,
                               home_box_.GetBounds().y2 + (1.45)*margin + 2*tile_height);
    ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(tile_width, tile_height));
    keyboard_[2].emplace_back(" ", "gray", key);
  }

  keyboard_[2][0].SetLabel("z");
  keyboard_[2][1].SetLabel("x");
  keyboard_[2][2].SetLabel("c");
  keyboard_[2][3].SetLabel("v");
  keyboard_[2][4].SetLabel("b");
  keyboard_[2][5].SetLabel("n");
  keyboard_[2][6].SetLabel("m");

  ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*7,
                             home_box_.GetBounds().y2 + (1.45)*margin + 2*tile_height);
  ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(2*tile_width + margin/4, tile_height));
  keyboard_[2].emplace_back("bksp", "red", key);
}

} // namespace visualizer

} // namespace wordle
