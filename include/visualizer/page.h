#pragma once

#include "cinder/gl/gl.h"
#include "tile.h"

namespace wordle {

namespace visualizer {

class Page {
 public:
  virtual void Draw() const = 0;
  virtual void DrawTile(const Tile& tile) const;
  virtual bool IsInBounds(const ci::vec2& position, const ci::Rectf& bounds) const;
  
  virtual std::string GetType() const = 0;
  // TODO: add these methods
//  virtual bool HasMouseEvent(const ci::vec2& position) const = 0;
//  virtual size_t GetMouseEvent(const ci::vec2& position) const = 0;
};

} // namespace visualizer

} // namespace wordle
