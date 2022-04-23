#include "visualizer/layout.h"

namespace wordle {

namespace visualizer {

Layout::Layout(double window_width,
               double window_height,
               double margin,
               size_t num_guesses,
               size_t num_letters,
               const std::string& default_color,
               const std::string& semi_correct_color,
               const std::string& correct_color,
               const std::string& incorrect_color) {

  window_width_ = window_width;
  window_height_ = window_height;
  margin_ = margin;
  num_guesses_= num_guesses;
  num_letters_ = num_letters;
  default_color_ = default_color;
  semi_correct_color_ = semi_correct_color;
  correct_color_ = correct_color;
  incorrect_color_ = incorrect_color;

  home_page_ = HomePage(margin_, window_width_, window_height_);
  board_page_ = BoardPage(margin_, window_width_, window_height_,
                          num_guesses_, num_letters_);
  selection_page_ = SelectionPage(margin_, window_width_, window_height_,
                                  num_guesses_, num_letters_);
}

// TODO: magic numbers
// TODO: handle > 30 games
void Layout::AddGame(size_t game_index) {
  selection_page_.AddGame(game_index);
}

void Layout::DrawHomePage() const {
  DrawTile(home_page_.GetWelcomeBox());
  DrawTile(home_page_.GetNewGameBox());
  DrawTile(home_page_.GetOldGameBox());
  DrawTile(home_page_.GetInstructionsBox());
  DrawTile(home_page_.GetStatisticsBox());
}

void Layout::DrawBoardPage() const {
  DrawTile(board_page_.GetHomeBox());

  for (size_t i = 0; i < num_guesses_; i++) {
    for (size_t j = 0; j < num_letters_; j++) {
      DrawTile(board_page_.GetBoard()[i][j]);
    }
  }
}

void Layout::DrawBoardPage(const Game& game) {
  ResetBoardTiles();
  
  for (size_t i = 0; i < game.GetGuessCount(); i++) {
    for (size_t j = 0; j < 5; j++) {
      const Letter &letter = game.GetBoard().GetWords()[i].GetLetter(j);
      board_page_.SetBoardTile(i, j, std::string(1, letter.ToChar()), letter.GetColor());
    }
  }
  
  DrawBoardPage();
}

void Layout::DrawSelectionPage() const {
  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 5; j++) {
      DrawTile(selection_page_.GetSelection()[i][j]);
    }
  }
}

void Layout::DrawBoardAnswer(const std::string& answer, const std::string& color) {
  board_page_.SetAnswerBox(answer, color);
  DrawTile(board_page_.GetAnswerBox());
}

void Layout::DrawTile(const Tile& tile) const {
  ci::gl::color(ci::Color(&(tile.GetColor()[0])));
  ci::gl::drawSolidRect(tile.GetBounds());
  ci::gl::drawStringCentered(tile.GetLabel(),
                             tile.GetBounds().getCenter() - ci::vec2(0, tile.GetBounds().getHeight() / 4),
                             ci::Color("black"),
                             ci::Font("Arial", 50.0));
}

void Layout::SetBoardTileLabel(size_t row, size_t col, const std::string& label) {
  board_page_.SetBoardTileLabel(row, col, label);
}

void Layout::SetBoardTileColor(size_t row, size_t col, const std::string &color) {
  board_page_.SetBoardTileColor(row, col, color);
}

void Layout::ResetBoardTiles() {
  for (size_t i = 0; i < 6; i++) {
    ResetBoardTiles(i);
  }
}

void Layout::ResetBoardTiles(size_t row) {
  for (size_t col = 0; col < 5; col++) {
    SetBoardTileColor(row, col, default_color_);
    SetBoardTileLabel(row, col, " ");
  }
}

void Layout::SetSelectionTileColor(size_t idx, const std::string &color) {
  selection_page_.SetSelectionTileColor(idx, color);
}

} // namespace visualizer

} // namespace wordle
