#include "visualizer/home_page.h"

namespace wordle {

namespace visualizer {
 
HomePage::HomePage(double margin, double window_width, double window_height) {
  title_box_ = Tile("Welcome to Wordle!", "teal",
                    ci::Rectf(ci::vec2(margin, margin),
                                ci::vec2(window_width - margin, margin + 100)));
  
  new_game_box_ = Tile("New Game", "teal",
                       ci::Rectf(ci::vec2(margin, 2*margin + 100),
                                 ci::vec2(window_width/2 - margin/2, 2*margin + 200)));
  
  old_game_box_ = Tile("Old Game", "teal",
                       ci::Rectf(ci::vec2(window_width/2 + margin/2, 2*margin + 100),
                                 ci::vec2(window_width - margin, 2*margin + 200)));
  
  instructions_box_ = Tile("Instructions", "teal",
                           ci::Rectf(ci::vec2(margin, 2*margin + 200 + margin),
                                     ci::vec2(window_width/2 - margin/2, 2*margin + 300 + margin)));
  
  statistics_box_ = Tile("Statistics", "teal",
                         ci::Rectf(ci::vec2(window_width/2 + margin/2, 2*margin + 200 + margin),
                                   ci::vec2(window_width - margin, 2*margin + 300 + margin)));
}

std::string HomePage::GetType() const {
  return "home";
}

void HomePage::Draw() const {
  DrawTile(title_box_);
  DrawTile(new_game_box_);
  DrawTile(old_game_box_);
  DrawTile(instructions_box_);
  DrawTile(statistics_box_);
}

bool HomePage::HasMouseEvent(const ci::vec2& position) const {
  return IsInBounds(position, new_game_box_.GetBounds())
         || IsInBounds(position, old_game_box_.GetBounds())
         || IsInBounds(position, instructions_box_.GetBounds())
         || IsInBounds(position, statistics_box_.GetBounds());
}

size_t HomePage::GetMouseEvent(const ci::vec2& position) const {
  if (IsInBounds(position, new_game_box_.GetBounds())) {
    return 1;
  } else if (IsInBounds(position, old_game_box_.GetBounds())) {
    return 2;
  } else if (IsInBounds(position, instructions_box_.GetBounds())) {
    return 3;
  } else if (IsInBounds(position, statistics_box_.GetBounds())) {
    return 4;
  } else {
    return 0;
  }
}

const Tile &HomePage::GetWelcomeBox() const {
  return title_box_;
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
