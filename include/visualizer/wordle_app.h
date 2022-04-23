#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/wordle.h"
#include "layout.h"
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
  Layout layout_;
  std::string guess_;
  size_t guess_size_;
  size_t guess_count_;
  size_t action_;
  size_t game_index_;
  bool game_chosen_;

  void DrawAnswerBox(const std::string& answer, const std::string& color) const;
  void DisplayHomePage();
  void DisplayStatistics();
  void ClearScreen();
  
};

} // namespace visualizer

} // namespace wordle