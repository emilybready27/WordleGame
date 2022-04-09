#pragma once

#include <vector>
#include "game.h"
#include "user_interface.h"

namespace wordle {
    
class Wordle {
 public:
  Wordle();
  
  void Play();
  void PlayGame(Game& game);
  
private:
  std::vector<Game> games_;
  UserInterface user_interface_;
  size_t game_count_;
  std::string message_;
  bool has_quit_;
};

} // namespace wordle