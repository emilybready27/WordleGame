#pragma once

#include "cinder/gl/gl.h"
#include "tile.h"

namespace wordle {

namespace visualizer {

class Page {
 public:
  virtual void Draw() const = 0;
  virtual void DrawTile(const Tile& tile) const;
  virtual std::string GetType() const = 0;
  virtual bool IsInBounds(const ci::vec2& position, const ci::Rectf& bounds) const;
};

} // namespace visualizer

} // namespace wordle