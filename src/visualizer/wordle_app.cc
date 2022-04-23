#include <visualizer/wordle_app.h>

namespace wordle {
    
namespace visualizer {

WordleApp::WordleApp() : wordle_() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  
  double tile_size = (kWindowWidth - 4*kMargin) / wordle_.GetNumLetters();
  for (size_t i = 0; i < wordle_.GetNumGuesses(); i++) {
    tiles_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < wordle_.GetNumLetters(); j++) {
      ci::vec2 coords = ci::vec2(kMargin + (tile_size + kMargin/2)*j,
                                 kMargin + (tile_size + kMargin/2)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));
      
      tiles_[i].emplace_back(" ", wordle_.GetDefaultColor(), square);
    }
  }

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
      DisplayHomePage();
      break;
      
    case 1:
      DrawTiles();
      break;
      
    case 2: {
      if (!game_chosen_) {
        DisplayGameSelection();
        break;
      }

      const Game &game = wordle_.GetGames()[game_index_];
      UpdateTiles(game);
      DrawTiles();

      if (game.IsComplete()) {
        DrawAnswerBox(game.GetAnswer().ToString(), game.GetColor()); // display answer
      } else {
        action_ = 1; // continue playing game
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
  // is a letter and haven't finished guess
  if (isalpha(event.getCode()) && guess_size_ < wordle_.GetNumLetters()) {
    guess_ += tolower(event.getChar());
    tiles_[guess_count_][guess_size_++].SetLabel(std::string(1, event.getChar()));
    
  // is a return and have finished guess
  } else if (event.getCode() == ci::app::KeyEvent::KEY_RETURN && guess_size_ == wordle_.GetNumLetters()) {
    Game &game = wordle_.GetGames()[game_index_];

    if (wordle_.GetDictionary().Contains(guess_)) { // valid word
      game.Evaluate(guess_);

      // update tile colors
      for (size_t i = 0; i < guess_size_; i++) {
        std::string color = game.GetBoard().GetLastWord().GetLetter(i).GetColor();
        tiles_[guess_count_][i].SetColor(color);
      }
      guess_count_++;

      // game over
      if (game.IsComplete()) {
        wordle_.GetStatistics().Update(game);
        guess_count_ = 0;
        action_ = 2; // display answer
        game_chosen_ = true;
      }

    } else { // invalid word
      ResetTiles(guess_count_);
    }

    guess_ = "";
    guess_size_ = 0;
  
  // entered a number for an action
  } else if (isdigit(event.getCode())) {
    std::string str = std::string(1, event.getChar());
    size_t input = std::stoi(str);
    
    if (action_ == 2 && input >= 1 && input <= wordle_.GetGameCount()) {
      game_chosen_ = true;
      game_index_ = input - 1;
      guess_count_ = wordle_.GetGames()[game_index_].GetGuessCount();
      return;
    } else if (action_ == 2) {
      return;
    }

    action_ = input;
    if (action_ == 1) {
      wordle_.AddGame();
      ResetTiles();
      guess_count_ = 0;
      game_index_ = wordle_.GetGameCount() - 1;
    } else if (action_ == 2) {
      game_chosen_ = false;
    } else if (action_ == 5) {
      exit(0);
    }

  } else if (event.getCode() == ci::app::KeyEvent::KEY_ESCAPE) {
    action_ = 0;
  }
  // TODO: ci::app::KeyEvent::KEY_DELETE:
  
}

void WordleApp::DrawTiles() const {
  for (size_t i = 0; i < tiles_.size(); i++) {
    for (size_t j = 0; j < tiles_[i].size(); j++) {
      DrawTile(tiles_[i][j]);
    }
  }
}

void WordleApp::DrawTile(const wordle::Tile &tile) const {
  ci::gl::color(ci::Color(&(tile.GetColor()[0])));
  ci::gl::drawSolidRect(tile.GetSquare());
  ci::gl::drawString(tile.GetLabel(), tile.GetSquare().getCenter() - ci::vec2(15.0, 15.0),
                     ci::Color("black"), ci::Font("Arial", 50.0));
}

void WordleApp::DrawAnswerBox(const std::string& answer, const std::string& color) const {
  ci::gl::color(ci::Color(&(color[0])));
  ci::Rectf answer_box = ci::Rectf(ci::vec2(kWindowWidth/2 - 2*kMargin, 1025),
                                   ci::vec2(kWindowWidth/2 + 2*kMargin, 1125));
  ci::gl::drawSolidRect(answer_box);
  ci::gl::drawString(answer, answer_box.getCenter() - ci::vec2(60.0, 25.0),
                     ci::Color("black"), ci::Font("Arial", 50.0));
}

void WordleApp::DisplayHomePage() {
  std::string message = "Welcome to Wordle!\n \n"
                        "Please enter a number:\n "
                        "1 to start a new game\n "
                        "2 to visit a previous game\n "
                        "3 to view the instructions\n "
                        "4 to view the statistics\n "
                        "5 to quit\n \n"
                        "ESC anytime to return";
  ci::gl::drawStringCentered(message, ci::vec2(kWindowWidth/2, kMargin),
                             ci::Color("white"), ci::Font("Arial", 50.0));
}

void WordleApp::DisplayGameSelection() {
  for (size_t i = 0; i < wordle_.GetGameCount(); i++) {
    std::string game_color = wordle_.GetGames()[i].GetColor();
    Tile tile = Tile(std::to_string(i + 1), game_color, tiles_[i / 6][i % 5].GetSquare());
    DrawTile(tile);
  }
}

void WordleApp::DisplayStatistics() {
  std::string message = "Statistics:\n \n"
                        "Games Played: " + std::to_string(wordle_.GetStatistics().GetGamesPlayed()) + "\n"
                        "Win Percentage: " + std::to_string(wordle_.GetStatistics().GetWinPercentage()) + "\n"
                        "Current Streak: " + std::to_string(wordle_.GetStatistics().GetCurrentStreak()) + "\n"
                        "Max Streak: " + std::to_string(wordle_.GetStatistics().GetMaxStreak()) + "\n \n"
                        "Guess Distribution:\n";
  
  for (size_t i = 0; i < tiles_.size(); i++) {
    message += std::to_string(i + 1) + ": " + std::to_string(wordle_.GetStatistics().GetGuessDistribution(i)) + "\n";
  }

  ci::gl::drawStringCentered(message, ci::vec2(kWindowWidth/2, kMargin),
                             ci::Color("white"), ci::Font("Arial", 50.0));
}

void WordleApp::ClearScreen() {
  ci::gl::clear(ci::Color::black());
}

void WordleApp::ResetTiles() {
  for (size_t i = 0; i < tiles_.size(); i++) {
    ResetTiles(i);
  }
}

void WordleApp::ResetTiles(size_t row) {
  for (size_t col = 0; col < tiles_[row].size(); col++) {
    ResetTile(row, col);
  }
}

void WordleApp::ResetTile(size_t row, size_t col) {
  tiles_[row][col].SetLabelAndColor(" ", "gray");
}

void WordleApp::UpdateTiles(const Game& game) {
  ResetTiles();
  
  for (size_t i = 0; i < game.GetGuessCount(); i++) {
    for (size_t j = 0; j < tiles_[i].size(); j++) {
      const Letter &letter = game.GetBoard().GetWords()[i].GetLetter(j);
      tiles_[i][j].SetLabelAndColor(std::string(1, letter.ToChar()), letter.GetColor());
    }
  }
}

} // namespace visualizer

} // namespace wordle