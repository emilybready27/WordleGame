#include <iostream>
#include "core/wordle.h"

namespace wordle {

Wordle::Wordle() {
  games_ = std::vector<Game>();
  user_interface_ = UserInterface();
  dictionary_ = Dictionary(kPathToDictionary);
  statistics_ = Statistics(kNumGuesses);
  game_count_ = 0;
  has_quit_ = false;
}

void Wordle::Play() {
  user_interface_.PrintLn(std::cout, "Welcome to Wordle!");
  
  while (!has_quit_) {
    std::string message = "Please enter a number:\n "
                          "1 to start a new game\n "
                          "2 to visit a previous game\n "
                          "3 to view the instructions\n "
                          "4 to view the statistics\n "
                          "5 to quit\n"
                          ">";
    user_interface_.Print(std::cout, message);
    
    const std::string& response = user_interface_.GetResponse(std::cin);
    if (response == "1") {
      PlayNewGame();
    } else if (response == "2") {
      PlayPastGame();
    } else if (response == "3") {
      PrintInstructions();
    } else if (response == "4") {
      PrintStatistics();
    } else if (response == "5") {
      has_quit_ = true;
    }
  }
}

void Wordle::PlayGame(size_t index) {
  Game& game = games_[index];
  
  while (!game.IsComplete()) {
    user_interface_.PrintBoard(std::cout, game.GetBoard(), kDefaultColor, kSemiCorrectColor, kCorrectColor);
    user_interface_.Print(std::cout, "Enter a guess or 0 to return:\n"
                                     ">");

    std::string response = user_interface_.GetResponse(std::cin);

    if (response == "0") { // return
      return;
    } else if (dictionary_.Contains(response)) { // valid word
      game.Evaluate(response);
      
      if (game.IsComplete()) {
        statistics_.Update(game);
      }
    } else { // invalid word
      user_interface_.PrintLn(std::cout, "Invalid word.");
    }
  }

  user_interface_.PrintBoard(std::cout, game.GetBoard(), kDefaultColor, kSemiCorrectColor, kCorrectColor);
  
  if (game.HasWon()) {
    user_interface_.PrintLn(std::cout, "You guessed \"" + game.GetAnswer().ToString() + "\" correctly!");
  } else {
    user_interface_.PrintLn(std::cout, "The correct answer is \"" + game.GetAnswer().ToString() + "\".");
  }
}

void Wordle::PlayNewGame() {
  Game game = Game(dictionary_.GenerateNewWord(), kNumGuesses, kNumLetters,
                   kDefaultColor, kSemiCorrectColor, kCorrectColor, kIncorrectColor);
  games_.push_back(game);
  
  PlayGame(game_count_++);
}

void Wordle::PlayPastGame() {
  if (game_count_ == 0) {
    user_interface_.PrintLn(std::cout, "No previous games");
    return;
  }
  
  PrintGameSelection();
  
  int index = 0;
  while (index <= 0 || index > (int) game_count_) {
    user_interface_.Print(std::cout, "Select a number:\n"
                                     ">");
    index = stoi(user_interface_.GetResponse(std::cin));
  }
  
  PlayGame(index - 1);
}

void Wordle::PrintGameSelection() {
  // print out display of game indices
  for (size_t i = 0; i < game_count_; i++) {
    std::string game_color = games_[i].GetColor();
    user_interface_.Print(std::cout, std::to_string(i + 1) + " ", game_color);
  }
  user_interface_.PrintLn(std::cout, "");
}

void Wordle::PrintInstructions() {
  user_interface_.PrintLn(std::cout, "");
  user_interface_.PrintLn(std::cout, "Instructions:\n"
                                     "Guess the word in 6 (or less) tries.\n"
                                     "After each guess, the letter color changes to show what letters are correct.");

  user_interface_.PrintLn(std::cout, "The letter s is in the word and in the correct spot.");
  Board correct = Board(1, kNumLetters, kDefaultColor, kSemiCorrectColor, kCorrectColor);
  correct.UpdateBoard("start", "sheep");
  user_interface_.PrintBoard(std::cout, correct, kDefaultColor, kSemiCorrectColor, kCorrectColor);

  user_interface_.PrintLn(std::cout, "The letter e is in the word but in the wrong spot.");
  Board semi_correct = Board(1, kNumLetters, kDefaultColor, kSemiCorrectColor, kCorrectColor);
  semi_correct.UpdateBoard("learn", "sheep");
  user_interface_.PrintBoard(std::cout, semi_correct, kDefaultColor, kSemiCorrectColor, kCorrectColor);

  user_interface_.PrintLn(std::cout, "None of the letters are in the correct spot.");
  Board incorrect = Board(1, kNumLetters, kDefaultColor, kSemiCorrectColor, kCorrectColor);
  incorrect.UpdateBoard("wordy", "sheep");
  user_interface_.PrintBoard(std::cout, incorrect, kDefaultColor, kSemiCorrectColor, kCorrectColor);

  user_interface_.PrintLn(std::cout, "");
}

void Wordle::PrintStatistics() {
  user_interface_.PrintLn(std::cout, "");
  user_interface_.PrintLn(std::cout, "Statistics:");
  user_interface_.PrintLn(std::cout, "Games Played: " + std::to_string(statistics_.GetGamesPlayed()));
  user_interface_.PrintLn(std::cout, "Win Percentage: " + std::to_string(statistics_.GetWinPercentage()));
  user_interface_.PrintLn(std::cout, "Current Streak: " + std::to_string(statistics_.GetCurrentStreak()));
  user_interface_.PrintLn(std::cout, "Max Streak: " + std::to_string(statistics_.GetMaxStreak()));
  
  user_interface_.PrintLn(std::cout, "Guess Distribution:");
  for (size_t i = 0; i < kNumGuesses; i++) {
    std::string message = std::to_string(i + 1) + ": " + std::to_string(statistics_.GetGuessDistribution(i));
    user_interface_.PrintLn(std::cout, message);
  }
  user_interface_.PrintLn(std::cout, "");
}

} // namespace wordle