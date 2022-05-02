#pragma once

#include "tile.h"
#include "page.h"

namespace wordle {

namespace visualizer {

/** The WordleApp page with gameplay instructions. */
class InstructionsPage : public Page {
 public:
  InstructionsPage() = default;
  InstructionsPage(double margin, double window_width, double window_height,
                   size_t num_guesses, size_t num_letters);

  void Draw() const override;
  bool HasMouseEvent(const ci::vec2& position) const override;
  size_t GetMouseEvent(const ci::vec2& position) const override;
  
 private:
  Tile title_box_;
  Tile preface_box_;
  std::vector<std::vector<Tile>> examples_;
  std::vector<Tile> descriptions_;
  Tile home_box_;
  Tile answer_box_;
  
  void ConstructExamples(double margin, double window_width, double window_height,
                         size_t num_guesses, size_t num_letters);
  void ConstructExample1();
  void ConstructExample2();
  void ConstructExample3();
    
};

} // namespace visualizer

} // namespace wordle
