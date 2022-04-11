#pragma once

#include <vector>
#include "game.h"
#include "user_interface.h"
#include "dictionary.h"

namespace wordle {
    
class Wordle {
 public:
  Wordle();
  
  void Play();
  void PlayGame();
  
private:
  std::vector<Game> games_;
  UserInterface user_interface_;
  Dictionary dictionary_;
  size_t game_count_;
  std::string message_;
  bool has_quit_;
  const size_t kNumGuesses = 6;
  const size_t kNumLetters = 5;
  const std::string kDefaultColor = "gray";
  const std::string kSemiCorrectColor = "light_yellow";
  const std::string kCorrectColor = "light_green";
  const std::string kPathToDictionary =
          R"(C:\Users\Mary\Desktop\Cinder\my-projects\final-project-ebready2\resources\dictionary.txt)";
};

} // namespace wordle