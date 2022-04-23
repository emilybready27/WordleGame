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

class WordleApp : public ci::app::App {
public:
  WordleApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowWidth = 875;
  const double kWindowHeight = 1225;
  const double kMargin = 100;
  
private:
  Wordle wordle_;
  
  HomePage home_page_;
  BoardPage board_page_;
  SelectionPage selection_page_;
  StatisticsPage statistics_page_;
  //InstructionsPage instructions_page_;
  
  std::string guess_;
  size_t guess_size_;
  size_t guess_count_;
  size_t action_;
  size_t game_index_;
  bool game_chosen_;

  void DisplayStatistics();
  void ClearScreen();
  
};

} // namespace visualizer

} // namespace wordle