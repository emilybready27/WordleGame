#include "visualizer/board_page.h"

namespace wordle {

namespace visualizer {

BoardPage::BoardPage(double margin, double window_width, double window_height,
                     size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;
  
  answer_box_ = Tile(" ", "black", ci::Rectf(ci::vec2(margin + tile_size + margin/2, 900),
                                             ci::vec2(window_width - margin, 1000)));
  home_box_ = Tile("home", "orange", ci::Rectf(ci::vec2(margin, 900),
                                               ci::vec2(margin + tile_size, 1000)));
  
  for (size_t i = 0; i < num_guesses; i++) {
    board_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_letters; j++) {
      ci::vec2 coords = ci::vec2((1.3)*margin + (tile_size + margin/3)*j,
                                 margin + (tile_size + margin/3)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      board_[i].emplace_back(" ", "gray", square);
    }
  }

  num_guesses_ = 0;
  letters_ = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
              'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
              'z', 'x', 'c', 'v', 'b', 'n', 'm'};
  for (const char letter : letters_) {
    color_map_[letter] = "gray";
  }
  
  ConstructKeyboard(margin, window_width, window_height);
}

void BoardPage::Draw() const {
  DrawTile(home_box_);

  for (size_t i = 0; i < board_.size(); i++) {
    for (size_t j = 0; j < board_[i].size(); j++) {
      if (board_[i][j].GetColor() == "dark_gray") {
        DrawTile(board_[i][j], (float) 0.3, (float) 0.3, (float) 0.3); // dark gray
      } else {
        DrawTile(board_[i][j]);
      }
    }
  }
  
  for (size_t i = 0; i < keyboard_.size(); i++) {
    for (size_t j = 0; j < keyboard_[i].size(); j++) {
      if (keyboard_[i][j].GetColor() == "dark_gray") {
        DrawTile(keyboard_[i][j], (float) 0.3, (float) 0.3, (float) 0.3); // dark gray
      } else {
        DrawTile(keyboard_[i][j]);
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
      
      if (letter.GetColor() == "green") {
        color_map_[letter.ToChar()] = letter.GetColor();
      } else if (letter.GetColor() == "yellow" && color_map_[letter.ToChar()] != "green") {
        color_map_[letter.ToChar()] = letter.GetColor();
      } else if (letter.GetColor() == "dark_gray") {
        color_map_[letter.ToChar()] = letter.GetColor();
      }
    }
  }

  UpdateKeyboard();

  if (game.IsComplete()) { // display answer
    answer_box_.SetLabelAndColor(game.GetAnswer().ToString(), game.GetColor());
  }
}

void BoardPage::Reset() {
  for (size_t i = 0; i < 6; i++) {
    ResetBoardRow(i);
  }
  
  answer_box_.SetLabelAndColor(" ", "black");
  
  for (size_t i = 0; i < 26; i++) {
    color_map_[letters_[i]] = "gray";
  }
  
  for (size_t i = 0; i < keyboard_.size(); i++) {
    for (size_t j = 0; j < keyboard_[i].size(); j++) {
      if (keyboard_[i][j].GetLabel() != "bksp") {
        keyboard_[i][j].SetColor("gray");
      }
    }
  }
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
    keyboard_[0].emplace_back(std::string(1, letters_[i]), "gray", key);
  }
}

void BoardPage::ConstructRow2(double margin, double tile_width, double tile_height) {
  keyboard_.emplace_back(std::vector<Tile>());
  for (size_t i = 0; i < 9; i++) {
    ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*i,
                               home_box_.GetBounds().y2 + (1.1)*margin + tile_height);
    ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(tile_width, tile_height));
    keyboard_[1].emplace_back(std::string(1, letters_[i+10]), "gray", key);
  }
}

void BoardPage::ConstructRow3(double margin, double tile_width, double tile_height) {
  keyboard_.emplace_back(std::vector<Tile>());
  for (size_t i = 0; i < 7; i++) {
    ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*i,
                               home_box_.GetBounds().y2 + (1.45)*margin + 2*tile_height);
    ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(tile_width, tile_height));
    keyboard_[2].emplace_back(std::string(1, letters_[i+19]), "gray", key);
  }

  ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*7,
                             home_box_.GetBounds().y2 + (1.45)*margin + 2*tile_height);
  ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(2*tile_width + margin/4, tile_height));
  keyboard_[2].emplace_back("bksp", "red", key);
}

void BoardPage::UpdateKeyboard() {
  for (size_t i = 0; i < keyboard_[0].size(); i++) {
    keyboard_[0][i].SetColor(color_map_[letters_[i]]);
  }

  for (size_t i = 0; i < keyboard_[1].size(); i++) {
    keyboard_[1][i].SetColor(color_map_[letters_[i+10]]);
  }

  for (size_t i = 0; i < keyboard_[2].size() - 1; i++) {
    keyboard_[2][i].SetColor(color_map_[letters_[i+19]]);
  }
}

} // namespace visualizer

} // namespace wordle
