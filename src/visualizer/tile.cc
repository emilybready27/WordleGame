#include "visualizer/tile.h"

namespace wordle {
    
Tile::Tile(const std::string& label, const std::string& color) {
  label_ = label;
  color_ = color;
}

const std::string& Tile::GetLabel() const {
  return label_;
}

const std::string& Tile::GetColor() const {
  return color_;
} 
    
}