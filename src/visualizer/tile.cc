#include "visualizer/tile.h"

namespace wordle {
    
Tile::Tile(const std::string& label, const std::string& color, const ci::Rectf& bounds) {
  label_ = label;
  color_ = color;
  bounds_ = bounds;
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

void Tile::SetBounds(const ci::Rectf& bounds) {
  bounds_ = bounds;
}

const ci::Rectf& Tile::GetBounds() const {
  return bounds_;
}

}