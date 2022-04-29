#include <visualizer/wordle_app.h>

namespace wordle {
    
namespace visualizer {

WordleApp::WordleApp() : wordle_() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  
  home_page_ = HomePage(kMargin, kWindowWidth, kWindowHeight);
  board_page_ = BoardPage(kMargin, kWindowWidth, kWindowHeight,
                          wordle_.GetNumGuesses(), wordle_.GetNumLetters());
  selection_page_ = SelectionPage(kMargin, kWindowWidth, kWindowHeight,
                                  wordle_.GetNumGuesses(), wordle_.GetNumLetters());
  statistics_page_ = StatisticsPage(kMargin, kWindowWidth, kWindowHeight);
  
  current_page_ = "home";
  action_ = 0;
  guess_ = "";
  guess_size_ = 0;
  guess_count_ = 0;
  game_index_ = 0;
}

void WordleApp::draw() {
  ci::gl::clear(ci::Color::black());
  
  switch (action_) {
    case 0:
      home_page_.Draw();
      break;
    case 1:
      board_page_.Draw();
      break;
    case 2:
      selection_page_.Draw();
      break;
//    case 3:
//      instructions_page_.Draw();
//      break;
    case 4:
      statistics_page_.Draw();
      break;
  }
}

void WordleApp::mouseDown(ci::app::MouseEvent event) {
  if (current_page_ == "home" && home_page_.HasMouseEvent(event.getPos())) {
    action_ = home_page_.GetMouseEvent(event.getPos());
    
  } else if (current_page_ == "board" && board_page_.HasMouseEvent(event.getPos())) {
    action_ = board_page_.GetMouseEvent(event.getPos());
    
  } else if (current_page_ == "selection" && selection_page_.HasMouseEvent(event.getPos())) {
    game_index_ = selection_page_.GetMouseEvent(event.getPos());
    action_ = 1;
    
//  } else if (current_page_ == "instructions" && instructions_page_.HasMouseEvent(event.getPos())) {
//    action_ = instructions_page_.GetMouseEvent(event.getPos());

  } else if (current_page_ == "statistics" && statistics_page_.HasMouseEvent(event.getPos())) {
    action_ = statistics_page_.GetMouseEvent(event.getPos());
  }
  
  ProcessAction();
}

void WordleApp::keyDown(ci::app::KeyEvent event) {
  // only accept keyboard inputs for board guesses
  if (current_page_ != "board" || wordle_.GetGames()[game_index_].IsComplete()) {
    return;
  }
  
  // entered a letter, haven't finished guess
  if (isalpha(event.getCharUtf32()) && guess_size_ < wordle_.GetNumLetters()) {
    guess_ += tolower(event.getChar());
    board_page_.SetBoardTileLabel(guess_count_, guess_size_++, std::string(1, event.getChar()));
    
  // entered a return, have finished guess
  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_RETURN && guess_size_ == wordle_.GetNumLetters()) {
    Game &game = wordle_.GetGames()[game_index_];

    if (!wordle_.GetDictionary().Contains(guess_)) { // invalid word
      board_page_.ResetBoardRow(guess_count_);
    } else { // valid word
      game.Evaluate(guess_);
      guess_count_++;

      // update tile colors
      board_page_.Update(game);
      selection_page_.SetSelectionColor(game_index_, game.GetColor());

      // game over
      if (game.IsComplete()) {
        wordle_.GetStatistics().Update(game);
        statistics_page_.Update(wordle_.GetStatistics());
      }
    }

    guess_ = "";
    guess_size_ = 0;

  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_BACKSPACE && guess_size_ > 0) {
    guess_.pop_back();
    board_page_.SetBoardTileLabel(guess_count_, --guess_size_, " ");
  }
}

void WordleApp::ProcessAction() {
  if (action_ == 0) {
    current_page_ = "home";
    guess_size_ = 0;
    guess_ = "";
    
  } else if (action_ == 1 && current_page_ == "home") {
    current_page_ = "board";
    
    // start a new game
    wordle_.AddGame();
    game_index_ = wordle_.GetGameCount() - 1;
    guess_count_ = 0;
    board_page_.Reset();
    selection_page_.AddGame(game_index_);

  } else if (action_ == 1 && current_page_ != "home") {
    current_page_  = "board";
    
    // go to existing game
    guess_count_ = wordle_.GetGames()[game_index_].GetGuessCount();
    board_page_.Update(wordle_.GetGames()[game_index_]);
    
  } else if (action_ == 2) {
    current_page_ = "selection";
    
  } else if (action_ == 3) {
    current_page_ = "instructions";
    
  } else if (action_ == 4) {
    current_page_ = "statistics";
  }
}

} // namespace visualizer

} // namespace wordle