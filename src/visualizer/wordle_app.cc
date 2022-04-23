#include <visualizer/wordle_app.h>

namespace wordle {
    
namespace visualizer {

WordleApp::WordleApp() : wordle_() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);

  // TODO: magic numbers
  // TODO: handle > 30 games
  home_page_ = HomePage(kMargin, kWindowWidth, kWindowHeight);
  board_page_ = BoardPage(kMargin, kWindowWidth, kWindowHeight,
                          wordle_.GetNumGuesses(), wordle_.GetNumLetters());
  selection_page_ = SelectionPage(kMargin, kWindowWidth, kWindowHeight,
                                  wordle_.GetNumGuesses(), wordle_.GetNumLetters());
  statistics_page_ = StatisticsPage(kMargin, kWindowWidth, kWindowHeight);
  current_page_ = "home";
  
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
      home_page_.Draw();
      break;
      
    case 1:
      board_page_.Draw();
      break;
      
    case 2: {
      if (!game_chosen_) {
        selection_page_.Draw();
        break;
      }

      const Game &game = wordle_.GetGames()[game_index_];
      board_page_.Draw(game);

      if (game.IsComplete()) { // display answer
        board_page_.DrawAnswer(game.GetAnswer().ToString(), game.GetColor());
      } else { // continue playing game
        action_ = 1;
      }
      break;
    }

    case 4:
      statistics_page_.Draw(wordle_.GetStatistics());
      break;
  }
}

//void WordleApp::mouseDown(ci::app::MouseEvent event) {
//  if ()
//}

void WordleApp::keyDown(ci::app::KeyEvent event) {
  // entered a letter and haven't finished guess
  if (isalpha(event.getCharUtf32()) && guess_size_ < wordle_.GetNumLetters()) {
    if (wordle_.GetGames()[game_index_].IsComplete()) {
      return;
    }
    guess_ += tolower(event.getChar());
    board_page_.SetBoardTileLabel(guess_count_, guess_size_++, std::string(1, event.getChar()));
    
  // entered a return and have finished guess
  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_RETURN && guess_size_ == wordle_.GetNumLetters()) {
    Game &game = wordle_.GetGames()[game_index_];

    if (!wordle_.GetDictionary().Contains(guess_)) { // invalid word
      board_page_.ResetBoardTiles(guess_count_);
    } else { // valid word
      game.Evaluate(guess_);

      // update tile colors
      for (size_t i = 0; i < guess_size_; i++) {
        std::string color = game.GetBoard().GetLastWord().GetLetter(i).GetColor();
        board_page_.SetBoardTileColor(guess_count_, i, color);
      }
      selection_page_.SetSelectionColor(game_index_, game.GetColor());
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
      board_page_.ResetBoardTiles();
      selection_page_.AddGame(game_index_);
    } else if (action_ == 2) {
      game_chosen_ = false;
    } else if (action_ == 5) {
      exit(0);
    }

  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_ESCAPE) {
    action_ = 0;
  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_BACKSPACE && guess_size_ > 0) {
    guess_.pop_back();
    board_page_.SetBoardTileLabel(guess_count_, --guess_size_, " ");
  }
  
}

void WordleApp::ClearScreen() {
  ci::gl::clear(ci::Color::black());
}

} // namespace visualizer

} // namespace wordle