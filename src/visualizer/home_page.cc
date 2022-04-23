#include "visualizer/home_page.h"

namespace wordle {

namespace visualizer {
 
HomePage::HomePage(double margin, double window_width, double window_height) {
  welcome_box_ = Tile("Welcome to Wordle!", "gray",
                      ci::Rectf(ci::vec2(margin, margin),
                                ci::vec2(window_width - margin, margin + 100)));
  
  new_game_box_ = Tile("1: New Game", "gray",
                       ci::Rectf(ci::vec2(margin, 2*margin + 100),
                                 ci::vec2(window_width/2 - margin/2, 2*margin + 200)));
  
  old_game_box_ = Tile("2: Old Game", "gray",
                       ci::Rectf(ci::vec2(window_width/2 + margin/2, 2*margin + 100),
                                 ci::vec2(window_width - margin, 2*margin + 200)));
  
  instructions_box_ = Tile("3: Instructions", "gray",
                           ci::Rectf(ci::vec2(margin, 2*margin + 200 + margin),
                                     ci::vec2(window_width/2 - margin/2, 2*margin + 300 + margin)));
  
  statistics_box_ = Tile("4: Statistics", "gray",
                         ci::Rectf(ci::vec2(window_width/2 + margin/2, 2*margin + 200 + margin),
                                   ci::vec2(window_width - margin, 2*margin + 300 + margin)));
}

void HomePage::Draw() const {
  DrawTile(welcome_box_);
  DrawTile(new_game_box_);
  DrawTile(old_game_box_);
  DrawTile(instructions_box_);
  DrawTile(statistics_box_);
}

const Tile &HomePage::GetWelcomeBox() const {
  return welcome_box_;
}

const Tile &HomePage::GetNewGameBox() const {
  return new_game_box_;
}

const Tile &HomePage::GetOldGameBox() const {
  return old_game_box_;
}

const Tile &HomePage::GetInstructionsBox() const {
  return instructions_box_;
}

const Tile &HomePage::GetStatisticsBox() const {
  return statistics_box_;
}

} // namespace visualizer

} // namespace wordle
