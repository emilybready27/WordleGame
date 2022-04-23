#include <visualizer/wordle_app.h>

namespace wordle {
    
namespace visualizer {

WordleApp::WordleApp() : wordle_() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);

  layout_ = Layout(kWindowWidth, kWindowHeight, kMargin,
                   wordle_.GetNumGuesses(), wordle_.GetNumLetters(),
                   wordle_.GetDefaultColor(), wordle_.GetSemiCorrectColor(),
                   wordle_.GetCorrectColor(), wordle_.GetIncorrectColor());
  
  guess_ = "";
  guess_size_ = 0;
  guess_count_ = 0;
  action_ = 0;
  game_index_ = 0;
  game_chosen_ = false;
}

void WordleApp::draw() {
  ClearScreen();
  
  switch (action_) {
    case 0:
      layout_.DrawHomePage();
      break;
      
    case 1:
      layout_.DrawBoardPage();
      break;
      
    case 2: {
      if (!game_chosen_) {
        layout_.DrawSelectionPage();
        break;
      }

      const Game &game = wordle_.GetGames()[game_index_];
      layout_.DrawBoardPage(game);

      if (game.IsComplete()) { // display answer
        layout_.DrawBoardAnswer(game.GetAnswer().ToString(), game.GetColor());
      } else { // continue playing game
        action_ = 1;
      }
      break;
    }

    case 4:
      DisplayStatistics();
      break;
  }
}

void WordleApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
}

void WordleApp::keyDown(ci::app::KeyEvent event) {
  // entered a letter and haven't finished guess
  if (isalpha(event.getCharUtf32()) && guess_size_ < wordle_.GetNumLetters()) {
    if (wordle_.GetGames()[game_index_].IsComplete()) {
      return;
    }
    guess_ += tolower(event.getChar());
    layout_.SetBoardTileLabel(guess_count_, guess_size_++, std::string(1, event.getChar()));
    
  // entered a return and have finished guess
  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_RETURN && guess_size_ == wordle_.GetNumLetters()) {
    Game &game = wordle_.GetGames()[game_index_];

    if (!wordle_.GetDictionary().Contains(guess_)) { // invalid word
      layout_.ResetBoardTiles(guess_count_);
    } else { // valid word
      game.Evaluate(guess_);

      // update tile colors
      for (size_t i = 0; i < guess_size_; i++) {
        std::string color = game.GetBoard().GetLastWord().GetLetter(i).GetColor();
        layout_.SetBoardTileColor(guess_count_, i, color);
      }
      layout_.SetSelectionTileColor(game_index_, game.GetColor());
      guess_count_++;

      // game over
      if (game.IsComplete()) {
        wordle_.GetStatistics().Update(game);
        guess_count_ = 0;
        action_ = 2; // display answer
        game_chosen_ = true;
      }
    }

    guess_ = "";
    guess_size_ = 0;
  
  // entered a number
  // TODO: handle inputs > 10
  } else if (isdigit(event.getCharUtf32())) {
    size_t input = std::stoi(std::string(1, event.getChar()));
    
    // input is a game index
    if (action_ == 2) {
      if (input >= 1 && input <= wordle_.GetGameCount()) {
        game_chosen_ = true;
        game_index_ = input - 1;
        guess_count_ = wordle_.GetGames()[game_index_].GetGuessCount();
      }
      return;
    }

    // TODO: replace user action inputs with buttons
    // input is an action
    action_ = input;
    if (action_ == 1) {
      wordle_.AddGame();
      guess_count_ = 0;
      game_index_ = wordle_.GetGameCount() - 1;
      layout_.ResetBoardTiles();
      layout_.AddGame(game_index_);
    } else if (action_ == 2) {
      game_chosen_ = false;
    } else if (action_ == 5) {
      exit(0);
    }

  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_ESCAPE) {
    action_ = 0;
  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_BACKSPACE && guess_size_ > 0) {
    guess_.pop_back();
    layout_.SetBoardTileLabel(guess_count_, --guess_size_, " ");
  }
  
}

void WordleApp::DisplayStatistics() {
  std::string message = "Statistics:\n \n"
                        "Games Played: " + std::to_string(wordle_.GetStatistics().GetGamesPlayed()) + "\n"
                        "Win Percentage: " + std::to_string(wordle_.GetStatistics().GetWinPercentage()) + "\n"
                        "Current Streak: " + std::to_string(wordle_.GetStatistics().GetCurrentStreak()) + "\n"
                        "Max Streak: " + std::to_string(wordle_.GetStatistics().GetMaxStreak()) + "\n \n"
                        "Guess Distribution:\n";
  
  for (size_t i = 0; i < wordle_.GetNumGuesses(); i++) {
    message += std::to_string(i + 1) + ": " + std::to_string(wordle_.GetStatistics().GetGuessDistribution(i)) + "\n";
  }

  ci::gl::drawStringCentered(message, ci::vec2(kWindowWidth/2, kMargin),
                             ci::Color("white"), ci::Font("Arial", 50.0));
}

void WordleApp::ClearScreen() {
  ci::gl::clear(ci::Color::black());
}

} // namespace visualizer

} // namespace wordle