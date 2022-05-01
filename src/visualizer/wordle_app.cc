#include <visualizer/wordle_app.h>

namespace wordle {
    
namespace visualizer {

WordleApp::WordleApp() : wordle_() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  
  home_page_ = HomePage(kMargin, kWindowWidth, kWindowHeight);
  board_page_ = BoardPage(kMargin, kWindowWidth, kWindowHeight,
                          wordle_.GetNumGuesses(), wordle_.GetNumLetters(), kLetters);
  selection_page_ = SelectionPage(kMargin, kWindowWidth, kWindowHeight,
                                  wordle_.GetNumGuesses(), wordle_.GetNumLetters());
  statistics_page_ = StatisticsPage(kMargin, kWindowWidth, kWindowHeight);
  instructions_page_ = InstructionsPage(kMargin, kWindowWidth, kWindowHeight,
                                        wordle_.GetNumGuesses(), wordle_.GetNumLetters());
  
  current_page_ = "home";
  action_ = 0;
  guess_ = "";
  guess_size_ = 0;
  guess_count_ = 0;
  game_index_ = 0;
  letter_index_ = 0;
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
    case 3:
      instructions_page_.Draw();
      break;
    case 4:
      statistics_page_.Draw();
      break;
  }
}

void WordleApp::mouseDown(ci::app::MouseEvent event) {
  if (current_page_ == "home" && home_page_.HasMouseEvent(event.getPos())) {
    action_ = home_page_.GetMouseEvent(event.getPos());
    
  } else if (current_page_ == "board" && board_page_.HasMouseEvent(event.getPos())) {
    letter_index_ = board_page_.GetMouseEvent(event.getPos());
    if (letter_index_ == 28) { // go to home page
      action_ = 0;
    } else if (letter_index_ == 27) { // backspace
      return ProcessInput('\b');
    } else if (letter_index_ == 26) { // submit guess
      return ProcessInput('\n');
    } else { // entered letter for guess
      return ProcessInput(kLetters[letter_index_]);
    }
    
  } else if (current_page_ == "selection" && selection_page_.HasMouseEvent(event.getPos())) {
    game_index_ = selection_page_.GetMouseEvent(event.getPos());
    action_ = 1;
    
  } else if (current_page_ == "instructions" && instructions_page_.HasMouseEvent(event.getPos())) {
    action_ = instructions_page_.GetMouseEvent(event.getPos());

  } else if (current_page_ == "statistics" && statistics_page_.HasMouseEvent(event.getPos())) {
    action_ = statistics_page_.GetMouseEvent(event.getPos());
  } else {
    return;
  }
  
  ProcessAction();
}

void WordleApp::keyDown(ci::app::KeyEvent event) {
  if (isalpha(event.getChar())) {
    ProcessInput(event.getChar());
    
  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_RETURN) {
    ProcessInput('\n');
    
  } else if (event.getCharUtf32() == ci::app::KeyEvent::KEY_BACKSPACE) {
    ProcessInput('\b');
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

void WordleApp::ProcessInput(char input) {
  // only accept keyboard inputs for board guesses
  if (current_page_ != "board" || wordle_.GetGames()[game_index_].IsComplete()) {
    return;
  }

  // entered a letter, haven't finished guess
  if (isalpha(input) && guess_size_ < wordle_.GetNumLetters()) {
    guess_ += tolower(input);
    board_page_.SetBoardTileLabel(guess_count_, guess_size_++, std::string(1, input));
    
  // entered a backspace, have started guess
  } else if (input == '\b' && guess_size_ > 0) {
    guess_.pop_back();
    board_page_.SetBoardTileLabel(guess_count_, --guess_size_, " ");

  // entered a return, have finished guess
  } else if (input == '\n' && guess_size_ == wordle_.GetNumLetters()) {
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
  }

  if (guess_size_ == wordle_.GetNumLetters()) {
    board_page_.SetSubmitTileColor("green");
  } else if (!wordle_.GetGames()[game_index_].IsComplete()){
    board_page_.SetSubmitTileColor("gray");
  }
}

} // namespace visualizer

} // namespace wordle