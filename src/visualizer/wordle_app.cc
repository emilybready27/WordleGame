#include <visualizer/wordle_app.h>

wordle::visualizer::WordleApp::WordleApp() : wordle_() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  
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
  action_ = 0;
}

void wordle::visualizer::WordleApp::draw() {
  // not currently playing a game
  if (action_ == 0) {
    ci::gl::clear(ci::Color::black());
    std::string message = "Welcome to Wordle!\n"
                          "Please enter a number:\n "
                          "1 to start a new game\n "
                          "2 to visit a previous game\n "
                          "3 to view the instructions\n "
                          "4 to view the statistics\n "
                          "5 to quit";
    ci::gl::drawStringCentered(message, ci::vec2(kWindowWidth/2, kMargin),
                               ci::Color("white"), ci::Font("Roboto", 50.0));
    
  // currently playing a game
  } else if (action_ == 1) {
    ci::gl::clear(ci::Color::black());

    // TODO: add another tile color
    for (size_t i = 0; i < tiles_.size(); i++) {
      for (size_t j = 0; j < tiles_[i].size(); j++) {
        const Tile &tile = tiles_[i][j];
        ci::gl::color(ci::Color(&(tile.GetColor()[0])));
        ci::gl::drawSolidRect(tile.GetSquare());
        ci::gl::drawString(std::string(1, tile.GetLabel()), tile.GetSquare().getCenter() - ci::vec2(15.0, 15.0),
                           ci::Color("black"), ci::Font("Roboto", 50.0));
      }
    }

  // visit previous game
  } else if (action_ == 2) {
    // TODO: add selection display for which game to view
    const Game& game = wordle_.GetGames()[wordle_.GetGameCount()-1];
    ci::gl::clear(ci::Color::black());
    
    // display board
    size_t word_count = 0;
    size_t letter_count = 0;
    for (const Word& word : game.GetBoard().GetWords()) {
      for (const Letter& letter : word.GetLetters()) {
        ci::gl::color(ci::Color(&(letter.GetColor()[0])));
        ci::gl::drawSolidRect(tiles_[word_count][letter_count].GetSquare());
        ci::gl::drawString(std::string(1, letter.ToChar()),
                           tiles_[word_count][letter_count].GetSquare().getCenter() - ci::vec2(15.0, 15.0),
                           ci::Color("black"), ci::Font("Roboto", 50.0));
        letter_count++;
      }
      letter_count = 0;
      word_count++;
    }
    
    // display answer if completed
    if (game.IsComplete()) {
      ci::gl::color(ci::Color("green"));
//      ci::Rectf answer_box = ci::Rectf(ci::vec2(2*kMargin, kWindowHeight/2 - kMargin),
//                                       ci::vec2(kWindowWidth - 2*kMargin, kWindowHeight/2 + kMargin));
      ci::Rectf answer_box = ci::Rectf(ci::vec2(kWindowWidth/2 - 2*kMargin, 1025),
                                       ci::vec2(kWindowWidth/2 + 2*kMargin, 1125));
      ci::gl::drawSolidRect(answer_box);
      ci::gl::drawString(game.GetAnswer().ToString(), answer_box.getCenter() - ci::vec2(60.0, 25.0),
                         ci::Color("black"), ci::Font("Roboto", 50.0));
    }
  
  // quit
  } else if (action_ == 5) {
    ci::gl::clear(ci::Color::black());
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
    Game &game = wordle_.GetGames()[wordle_.GetGameCount() - 1];

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
        action_ = 0;
        
        // reset board
        for (size_t i = 0; i < tiles_.size(); i++) {
          for (size_t j = 0; j < tiles_[i].size(); j++) {
            tiles_[i][j].SetColor("gray");
            tiles_[i][j].SetLabel(' ');
          }
        }
        // create popup
      }

    } else { // invalid word
      for (size_t i = 0; i < guess_size_; i++) {
        tiles_[guess_count_][i].SetLabel(' ');
      }
    }

    guess_ = "";
    guess_size_ = 0;
  
  // entered a number for a command
  } else if (isdigit(event.getCode())) {
    std::string str = std::string(1, event.getChar());
    if (std::stoi(str) >= 1 && std::stoi(str) <= 5) {
      action_ = std::stoi(str);
    }

    if (action_ == 1) {
      wordle_.AddGame();
    } else if (action_ == 2) {
      // nothing right now...
    } else if (action_ == 5) {
      exit(0);
    }

  } else if (event.getCode() == ci::app::KeyEvent::KEY_ESCAPE) {
    action_ = 0;
  }
  // TODO: ci::app::KeyEvent::KEY_DELETE:
  
}
