#include "visualizer/tile.h"

namespace wordle {
    
Tile::Tile(char label, const std::string& color, const ci::Rectf& square) {
  label_ = label;
  color_ = color;
  square_ = square;
}

void Tile::SetLabel(char label) {
  label_ = label;
}

char Tile::GetLabel() const {
  return label_;
}

void Tile::SetColor(const std::string& color) {
  color_ = color;
}

const std::string& Tile::GetColor() const {
  return color_;
}

const ci::Rectf& Tile::GetSquare() const {
  return square_;
}
    
}