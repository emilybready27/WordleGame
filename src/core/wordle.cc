#include "core/wordle.h"

namespace wordle {

Wordle::Wordle() {
  games_ = std::vector<Game>();
  user_interface_ = UserInterface();
  game_count_ = 0;
}

// TODO: build strings in here, not in UI
void Wordle::Play() {
  message_ = "Welcome to Wordle!\n "
             "To start a new game, input 1\n "
             "To view the instructions, input 2\n "
             "To view a previous game, input 3";
  user_interface_.Print(message_);
  
  // TODO: handle all possible responses
  if (user_interface_.GetResponse() == "1") {
    // fixed answer "start"
    games_.emplace_back("start");
    game_count_++;
    PlayGame(games_[game_count_ - 1]);
  }
}

// TODO: change parameter
void Wordle::PlayGame(Game &game) {
//  while (!game.IsComplete()) { // TODO: magic number 6
//    user_interface_.PrintState(game.GetBoard());
//    user_interface_.GamePrompt(game);
//    game.IncrementGuessCount();
//  }
  //user_interface_.PrintState(game.GetBoardString());
  message_ = "Please enter a guess for the word:";
  user_interface_.Print(message_);
  game.IncrementGuessCount();
  std::string response = user_interface_.GetResponse();
  std::string result = game.ProcessInput(response);
  
  message_ = "Hooray, you guessed \"" + result + "\" correctly!";
  user_interface_.Print(message_);
  
//  if (game.IsWon()) {
//    user_interface_.PrintResult();
//  } else {
//    
//  }
}

} // namespace wordle