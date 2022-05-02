#include "visualizer/instructions_page.h"

namespace wordle {

namespace visualizer {

InstructionsPage::InstructionsPage(double margin, double window_width, double window_height,
                                   size_t num_guesses, size_t num_letters) {
  title_box_ = Tile("Instructions:", "gray", ci::Rectf(ci::vec2(margin, margin),
                                              ci::vec2(window_width - margin, margin + 100)));
  
  preface_box_ = Tile("\nGuess the word in 6 (or less) tries.\n"
                      "After each guess, the color changes\n"
                      "to show what letters are correct.", "gray",
                      ci::Rectf(ci::vec2(margin, margin),
                                ci::vec2(window_width - margin, margin + 250)));
  
  home_box_ = Tile("home", "orange", ci::Rectf(ci::vec2(margin, 1150),
                                               ci::vec2(margin + (window_width - 4*margin) / 5, 1250)));
  
  answer_box_ = Tile("Correct answer: sheep", "green",
                     ci::Rectf(ci::vec2(margin + home_box_.GetBounds().getWidth() + margin/2, 1150),
                               ci::vec2(window_width - margin, 1250)));
  
  ConstructExamples(margin, window_width, window_height, num_guesses, num_letters);
}

void InstructionsPage::Draw() const {
  DrawTile(preface_box_);
  DrawTile(title_box_);
  DrawTile(home_box_);
  DrawTile(answer_box_);
  
  for (size_t i = 0; i < descriptions_.size(); i++) {
    DrawTile(descriptions_[i]);
    for (size_t j = 0; j < examples_[i].size(); j++) {
      if (examples_[i][j].GetColor() == "dark_gray") {
        DrawTile(examples_[i][j], (float) 0.3, (float) 0.3, (float) 0.3); // dark gray
      } else {
        DrawTile(examples_[i][j]);
      }
    }
  }
}

bool InstructionsPage::HasMouseEvent(const glm::vec2 &position) const {
  return IsInBounds(position, home_box_.GetBounds());
}

size_t InstructionsPage::GetMouseEvent(const glm::vec2 &position) const {
  return 0; // only action is to return home
}

void InstructionsPage::ConstructExamples(double margin, double window_width, double window_height,
                                         size_t num_guesses, size_t num_letters) {
  double tile_size = (window_width - (num_letters - 1)*margin) / num_letters;
  
  for (size_t i = 0; i < 3; i++) {
    descriptions_.emplace_back(" ", "gray",
                               ci::Rectf(ci::vec2(margin, margin + 300 + i*250),
                                         ci::vec2(window_width - margin, margin + 380 + i*250)));
    examples_.emplace_back(std::vector<Tile>());
    for (size_t j = 0; j < num_letters; j++) {
      ci::vec2 coords = ci::vec2(margin + (tile_size + margin/2)*j,
                                 descriptions_[i].GetBounds().y1 + margin);
      ci::Rectf square = ci::Rectf(coords, coords + ci::vec2(tile_size, tile_size));

      examples_[i].emplace_back(" ", "gray", square);
    }
  }

  ConstructExample1();
  ConstructExample2();
  ConstructExample3();
}

void InstructionsPage::ConstructExample1() {
  descriptions_[0].SetLabel("The letter s is in the correct spot:");

  examples_[0][0].SetLabelAndColor("s", "green");
  examples_[0][1].SetLabelAndColor("t", "dark_gray");
  examples_[0][2].SetLabelAndColor("a", "dark_gray");
  examples_[0][3].SetLabelAndColor("r", "dark_gray");
  examples_[0][4].SetLabelAndColor("t", "dark_gray");
}

void InstructionsPage::ConstructExample2() {
  descriptions_[1].SetLabel("The letter e is in wrong spot:");

  examples_[1][0].SetLabelAndColor("l", "dark_gray");
  examples_[1][1].SetLabelAndColor("e", "yellow");
  examples_[1][2].SetLabelAndColor("a", "dark_gray");
  examples_[1][3].SetLabelAndColor("r", "dark_gray");
  examples_[1][4].SetLabelAndColor("n", "dark_gray");
}

void InstructionsPage::ConstructExample3() {
  descriptions_[2].SetLabel("None of the letters are in the word:");

  examples_[2][0].SetLabelAndColor("w", "dark_gray");
  examples_[2][1].SetLabelAndColor("o", "dark_gray");
  examples_[2][2].SetLabelAndColor("r", "dark_gray");
  examples_[2][3].SetLabelAndColor("d", "dark_gray");
  examples_[2][4].SetLabelAndColor("y", "dark_gray");
}

} // namespace visualizer

} // namespace wordle
