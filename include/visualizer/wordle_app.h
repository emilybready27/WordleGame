#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/wordle.h"
#include "tile.h"

namespace wordle {

namespace visualizer {

class WordleApp : public ci::app::App {
public:
  WordleApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowWidth = 875;
  const double kWindowHeight = 1025;
  const double kMargin = 100;
  
private:
  Wordle wordle_;
  std::vector<std::vector<Tile>> tiles_;
  std::string guess_;
  size_t guess_size_;
  size_t guess_count_;
  
};

} // namespace visualizer

} // namespace wordle