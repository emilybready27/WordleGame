#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/wordle.h"
#include "home_page.h"
#include "board_page.h"
#include "selection_page.h"
#include "statistics_page.h"
#include "tile.h"

namespace wordle {

namespace visualizer {

/** The Cinder visualization for Wordle. */
class WordleApp : public ci::app::App {
 public:
  /**
   * Initializes the Pages and other state of the WordleApp.
   */
  WordleApp();

  /**
   * Draws the current page on the screen.
   */
  void draw() override;
  
  /**
   * Responds to a user input to direct the action of the App.
   * @param event ci::app::MouseEvent
   */
  void mouseDown(ci::app::MouseEvent event) override;
  
  /**
   * Responds to a user input of a board guess.
   * @param event ci::app::KeyEvent
   */
  void keyDown(ci::app::KeyEvent event) override;

  /**
   * Window width in pixels.
   */
  const double kWindowWidth = 875;
  
  /**
   * Window height in pixels.
   */
  const double kWindowHeight = 1225;
  
  /**
   * Window margin in pixels.
   */
  const double kMargin = 100;
  
 private:
  /**
   * Instance of the Wordle which stores the game state.
   */
  Wordle wordle_;
  
  /**
   * The different pages that the screen can show.
   */
  HomePage home_page_;
  BoardPage board_page_;
  SelectionPage selection_page_;
  StatisticsPage statistics_page_;
  // TODO: InstructionsPage instructions_page_;
  
  /**
   * An indication of the current page shown on the screen:
   * "home", "board", "selection", "instructions", or "statistics".
   */
  std::string current_page_;

  /**
  * The current action selected by the user.
  * 0. go to home page
  * 1. play a game
  * 2. visit a previous game
  * 3. view the instructions
  * 4. view the statistics
  */
  size_t action_;
  
  /**
   * The current user guess for a word.
   */
  std::string guess_;
  
  /**
   * The current number of characters input for a user guess.
   */
  size_t guess_size_;
  
  /**
   * The current number of user guesses taken.
   */
  size_t guess_count_;
  
  /**
   * The current index of game being considered.
   */
  size_t game_index_;

  /**
   * Directs the behavior based on the user choice of action.
   */
  void ProcessAction();

  // TODO: magic numbers
  
};

} // namespace visualizer

} // namespace wordle