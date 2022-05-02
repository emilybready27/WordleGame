#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "tile.h"
#include "core/game.h"
#include "page.h"

namespace wordle {

namespace visualizer {

/** The WordleApp Page used to display the board and play the game. */
class BoardPage : public Page {
 public:
  BoardPage() = default;
  BoardPage(double margin, double window_width, double window_height,
            size_t num_guesses, size_t num_letters, const std::vector<char>& letters);
  
  void Draw() const override;
  bool HasMouseEvent(const ci::vec2& position) const override;
  size_t GetMouseEvent(const ci::vec2& position) const override;

  /**
   * Updates the board and keyboard by changing colors as appropriate.
   * If the game is complete, displays the answer.
   * @param game Game
   */
  void Update(const Game& game);
  
  /**
   * Resets the state of the board to empty.
   */
  void Reset();
  
  /**
   * Resets the given row of the board to empty.
   * @param row size_t
   */
  void ResetBoardRow(size_t row);
  
  /**
   * Sets the given index of the board with the given label.
   * @param i size_t
   * @param j size_t
   * @param label std::string
   */
  void SetBoardTileLabel(size_t i, size_t j, const std::string& label);
  
  /**
   * Sets the submit tile / answer box to the given color.
   * @param color 
   */
  void SetSubmitTileColor(const std::string& color);

 private:
  Tile answer_box_;
  Tile home_box_;
  std::vector<std::vector<Tile>> board_;
  std::vector<std::vector<Tile>> keyboard_;
  Tile backspace_;

  /**
   * The alphabetical letters used for the keyboard.
   */
  std::vector<char> letters_;
  
  /**
   * Maps the keyboard letters to their colors for display.
   */
  std::map<char, std::string> color_map_;
  
  void ConstructBoard(double margin, double window_width, double window_height,
                      size_t num_guesses, size_t num_letters);
  void ConstructKeyboard(double margin, double window_width, double window_height);
  void ConstructKeyboardRow1(double margin, double tile_width, double tile_height);
  void ConstructKeyboardRow2(double margin, double tile_width, double tile_height);
  void ConstructKeyboardRow3(double margin, double tile_width, double tile_height);
  
};

} // namespace visualizer

} // namespace wordle
