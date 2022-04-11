#include "core/wordle.h"

namespace wordle {

Wordle::Wordle() {
  games_ = std::vector<Game>();
  user_interface_ = UserInterface();
  dictionary_ = Dictionary();
  game_count_ = 0;
  message_ = "";
  has_quit_ = false;
}

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
      PlayGame();
    } else if (response == "2") {
      
    } else if (response == "3") {
      
    } else if (response == "4") {
      has_quit_ = true;
    }
  }
}

// TODO: currently have to keep playing until the end of the game
void Wordle::PlayGame() {
  Game game = Game(dictionary_.GenerateNewWord(), kNumGuesses, kNumLetters,
                   kDefaultColor, kSemiCorrectColor, kCorrectColor);
  games_.push_back(game);
  game_count_++;
  
  while (!game.IsComplete()) {
    user_interface_.PrintInColor(game.GetBoard(), kDefaultColor, kSemiCorrectColor, kCorrectColor);
    user_interface_.Print("Guess:");
    
    std::string response = user_interface_.GetResponse();
  
     if (dictionary_.Contains(response)) {
       game.Evaluate(response);
    } else {
      user_interface_.Print("Invalid word.");
    }
  }

  user_interface_.PrintInColor(game.GetBoard(), kDefaultColor, kSemiCorrectColor, kCorrectColor);
  if (game.HasWon()) {
    message_ = "Hooray, you guessed \"" + game.GetAnswer().ToString() + "\" correctly!";
  } else {
    message_ = "Sorry, the correct answer is \"" + game.GetAnswer().ToString() + "\".";
  }
  user_interface_.Print(message_);
}

} // namespace wordle