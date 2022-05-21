#include "visualizer/board_page.h"

namespace wordle {

namespace visualizer {

BoardPage::BoardPage(double margin, double window_width, double window_height,
                     size_t num_guesses, size_t num_letters, const std::vector<char>& letters) {

  letters_ = letters;
  for (const char letter : letters_) {
    color_map_[letter] = "gray";
  }
  
  ConstructBoard(margin, window_width, window_height, num_guesses, num_letters);
  ConstructKeyboard(margin, window_width, window_height);
}

void BoardPage::Draw() const {
  // draw board
  for (size_t i = 0; i < board_.size(); i++) {
    for (size_t j = 0; j < board_[i].size(); j++) {
      if (board_[i][j].GetColor() == "dark_gray") {
        DrawTile(board_[i][j], (float) 0.3, (float) 0.3, (float) 0.3); // dark gray
      } else {
        DrawTile(board_[i][j]);
      }
    }
  }

  // draw keyboard
  for (size_t i = 0; i < keyboard_.size(); i++) {
    for (size_t j = 0; j < keyboard_[i].size(); j++) {
      if (keyboard_[i][j].GetColor() == "dark_gray") {
        DrawTile(keyboard_[i][j], (float) 0.3, (float) 0.3, (float) 0.3); // dark gray
      } else {
        DrawTile(keyboard_[i][j]);
      }
    }
  }

  DrawTile(home_box_);
  DrawTile(answer_box_);
  DrawTile(backspace_);
}

bool BoardPage::HasMouseEvent(const ci::vec2& position) const {
  for (size_t i = 0; i < keyboard_.size(); i++) {
    for (size_t j = 0; j < keyboard_[i].size(); j++) {
      if (IsInBounds(position, keyboard_[i][j].GetBounds())) {
        return true;
      }
    }
  }

  return IsInBounds(position, answer_box_.GetBounds())
         || IsInBounds(position, backspace_.GetBounds())
         || IsInBounds(position, home_box_.GetBounds());
}

size_t BoardPage::GetMouseEvent(const ci::vec2& position) const {
  // returns the index of the letter clicked on, or an index larger than 25
  // corresponding to one of the other three button options
  if (IsInBounds(position, home_box_.GetBounds())) {
    return 28;
  } else if (IsInBounds(position, backspace_.GetBounds())) {
    return 27;
  } else if (IsInBounds(position, answer_box_.GetBounds())) {
    return 26;
  } else {
    
    size_t counter = 0;
    for (size_t i = 0; i < keyboard_.size(); i++) {
      for (size_t j = 0; j < keyboard_[i].size(); j++) {
        if (IsInBounds(position, keyboard_[i][j].GetBounds())) {
          return counter;
        }
        counter++;
      }
    }
  }

  return 0; // never executes
}

void BoardPage::Update(const Game& game) {
  Reset();

  // update board
  for (size_t i = 0; i < game.GetGuessCount(); i++) {
    for (size_t j = 0; j < 5; j++) {
      const Letter &letter = game.GetBoard().GetWords()[i].GetLetter(j);
      board_[i][j].SetLabelAndColor(std::string(1, letter.ToChar()), letter.GetColor());
      
      // update color map
      if (letter.GetColor() == "green") {
        color_map_[letter.ToChar()] = letter.GetColor();
      } else if (letter.GetColor() == "yellow" && color_map_[letter.ToChar()] != "green") {
        color_map_[letter.ToChar()] = letter.GetColor();
      } else if (letter.GetColor() == "dark_gray") {
        color_map_[letter.ToChar()] = letter.GetColor();
      }
    }
  }

  // update keyboard
  for (size_t i = 0; i < keyboard_[0].size(); i++) {
    keyboard_[0][i].SetColor(color_map_[letters_[i]]);
  }
  for (size_t i = 0; i < keyboard_[1].size(); i++) {
    keyboard_[1][i].SetColor(color_map_[letters_[i+10]]);
  }
  for (size_t i = 0; i < keyboard_[2].size(); i++) {
    keyboard_[2][i].SetColor(color_map_[letters_[i+19]]);
  }

  // display answer if game is over
  if (game.IsComplete()) {
    answer_box_.SetLabelAndColor(game.GetAnswer().ToString(), game.GetColor());
  }
}

void BoardPage::Reset() {
  for (size_t i = 0; i < 6; i++) {
    ResetBoardRow(i);
  }
  
  answer_box_.SetLabelAndColor("submit", "gray");
  
  for (size_t i = 0; i < 26; i++) {
    color_map_[letters_[i]] = "gray";
  }
  
  for (size_t i = 0; i < keyboard_.size(); i++) {
    for (size_t j = 0; j < keyboard_[i].size(); j++) {
      keyboard_[i][j].SetColor("gray");
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

void BoardPage::SetSubmitTileColor(const std::string& color) {
  answer_box_.SetColor(color);
}

void BoardPage::ConstructBoard(double margin, double window_width, double window_height,
                               size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters-1)*margin) / num_letters;

  answer_box_ = Tile("submit", "gray", ci::Rectf(ci::vec2(margin + tile_size + margin/2, 900),
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
}

void BoardPage::ConstructKeyboard(double margin, double window_width, double window_height) {
  double tile_width = (window_width - margin - 2.5*margin) / 10;
  double tile_height = (window_height - home_box_.GetBounds().y2 - (2.5)*margin) / 3;
  
  ConstructKeyboardRow1(margin, tile_width, tile_height);
  ConstructKeyboardRow2(margin, tile_width, tile_height);
  ConstructKeyboardRow3(margin, tile_width, tile_height);

  ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*7,
                             home_box_.GetBounds().y2 + (1.45)*margin + 2*tile_height);
  ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(2*tile_width + margin/4, tile_height));
  backspace_ = Tile("bksp", "red", key);
}

void BoardPage::ConstructKeyboardRow1(double margin, double tile_width, double tile_height) {
  keyboard_.emplace_back(std::vector<Tile>());
  for (size_t i = 0; i < 10; i++) {
    ci::vec2 coords = ci::vec2((0.6)*margin + (tile_width + margin/4)*i,
                               home_box_.GetBounds().y2 + (0.75)*margin);
    ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(tile_width, tile_height));
    
    keyboard_[0].emplace_back(std::string(1, letters_[i]), "gray", key);
  }
}

void BoardPage::ConstructKeyboardRow2(double margin, double tile_width, double tile_height) {
  keyboard_.emplace_back(std::vector<Tile>());
  for (size_t i = 0; i < 9; i++) {
    ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*i,
                               home_box_.GetBounds().y2 + (1.1)*margin + tile_height);
    ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(tile_width, tile_height));
    
    keyboard_[1].emplace_back(std::string(1, letters_[i+10]), "gray", key);
  }
}

void BoardPage::ConstructKeyboardRow3(double margin, double tile_width, double tile_height) {
  keyboard_.emplace_back(std::vector<Tile>());
  for (size_t i = 0; i < 7; i++) {
    ci::vec2 coords = ci::vec2(margin + (tile_width + margin/4)*i,
                               home_box_.GetBounds().y2 + (1.45)*margin + 2*tile_height);
    ci::Rectf key = ci::Rectf(coords, coords + ci::vec2(tile_width, tile_height));
    
    keyboard_[2].emplace_back(std::string(1, letters_[i+19]), "gray", key);
  }
}

} // namespace visualizer

} // namespace wordle
