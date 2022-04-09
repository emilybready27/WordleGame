#include "core/wordle.h"

namespace wordle {

Wordle::Wordle() {
  games_ = std::vector<Game>();
  user_interface_ = UserInterface();
  game_count_ = 0;
  message_ = "";
  has_quit_ = false;
}

// TODO: build strings in here, not in UI
void Wordle::Play() {
  user_interface_.Print("Welcome to Wordle!");
  
  while (!has_quit_) {
    message_ = "Please enter a number:\n "
               "1 to start a new game\n "
               "2 to view the instructions\n "
               "3 to view a previous game\n "
               "4 to quit";
    user_interface_.Print(message_);
    
    const std::string& response = user_interface_.GetResponse();
    if (response == "1") {
      // fixed answer "start"
      games_.emplace_back("start");
      game_count_++;
      PlayGame(games_[game_count_ - 1]);
    } else if (response == "2") {
      
    } else if (response == "3") {
      
    } else if (response == "4") {
      has_quit_ = true;
    }
  }
}

// TODO: currently have to keep playing until the end of the game
// TODO: change parameter
void Wordle::PlayGame(Game &game) {
  while (!game.IsComplete()) {
    user_interface_.Print(game.GetBoardString());
    user_interface_.Print("Please enter a guess for the word:");
    
    std::string response = user_interface_.GetResponse();
  
    // if (dictionary_.Contains(response)
    if (true) {
      game.ProcessWord(response);
    } else {
      user_interface_.Print("Invalid word.");
    }
  }

  user_interface_.Print(game.GetBoardString());
  if (game.HasWon()) {
    message_ = "Hooray, you guessed \"" + game.GetAnswer() + "\" correctly!";
  } else {
    message_ = "Sorry, the correct answer is \"" + game.GetAnswer() + "\".";
  }
  user_interface_.Print(message_);
}

} // namespace wordle