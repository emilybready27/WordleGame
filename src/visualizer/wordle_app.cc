#include <visualizer/wordle_app.h>

wordle::visualizer::WordleApp::WordleApp() : wordle_() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  
  // currently, starting with a game instantiated
  wordle_.AddGame();
  
  double tile_size = (kWindowWidth - 4*kMargin) / wordle_.GetNumLetters();
  for (size_t i = 0; i < wordle_.GetNumGuesses(); i++) {
    tiles_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < wordle_.GetNumLetters(); j++) {
      ci::vec2 coords = ci::vec2(kMargin + (tile_size + kMargin/2)*j,
                                 kMargin + (tile_size + kMargin/2)*i);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));
      
      tiles_[i].emplace_back(' ', wordle_.GetDefaultColor(), square);
    }
  }

  guess_ = "";
  guess_size_ = 0;
  guess_count_ = 0;
}

void wordle::visualizer::WordleApp::draw() {
  ci::gl::clear(ci::Color::black());

  for (size_t i = 0; i < tiles_.size(); i++) {
    for (size_t j = 0; j < tiles_[i].size(); j++) {
      const Tile& tile = tiles_[i][j];
      ci::gl::color(ci::Color(&(tile.GetColor()[0])));
      ci::gl::drawSolidRect(tile.GetSquare());
      ci::gl::drawStringCentered(std::string(1, tile.GetLabel()), tile.GetSquare().getCenter(), ci::Color("black"));
    }
  }
}

void wordle::visualizer::WordleApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
}

void wordle::visualizer::WordleApp::mouseDrag(ci::app::MouseEvent event) {
  AppBase::mouseDrag(event);
}

void wordle::visualizer::WordleApp::keyDown(ci::app::KeyEvent event) {
  // is a letter and haven't finished guess
  if (isalpha(event.getCode()) && guess_size_ < wordle_.GetNumLetters()) {
    guess_ += event.getChar(); // TODO: sanitize
    tiles_[guess_count_][guess_size_++].SetLabel(event.getChar());
    
  // is a return and have finished guess
  } else if (event.getCode() == ci::app::KeyEvent::KEY_RETURN && guess_size_ == wordle_.GetNumLetters()) {
    Game& game = wordle_.GetGames()[0];

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
        // TODO: end game
      }
      
    } else { // invalid word
      for (size_t i = 0; i < guess_size_; i++) {
        tiles_[guess_count_][i].SetLabel(' ');
      }
    }

    guess_ = "";
    guess_size_ = 0;
  }   
      
      
    //case ci::app::KeyEvent::KEY_DELETE:
  
}
