#include "visualizer/tile.h"

namespace wordle {
    
Tile::Tile(const std::string& label, const std::string& color, const ci::Rectf& square) {
  label_ = label;
  color_ = color;
  square_ = square;
}

void Tile::SetLabelAndColor(const std::string &label, const std::string &color) {
  label_ = label;
  color_ = color;
}

void Tile::SetLabel(const std::string& label) {
  label_ = label;
}

const std::string& Tile::GetLabel() const {
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