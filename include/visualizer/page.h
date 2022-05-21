#pragma once

#include "cinder/gl/gl.h"
#include "tile.h"

namespace wordle {

namespace visualizer {

/** Abstract Page consisting of Tiles that correspond to mouse events. */
class Page {
 public:
  /**
   * Displays the specific Tiles of the Page.
   */
  virtual void Draw() const = 0;
  
  /**
   * Checks if the given position is within the bounds of any Tiles of the Page.
   * @param position ci::vec2
   * @return bool
   */
  virtual bool HasMouseEvent(const ci::vec2& position) const = 0;
  
  /**
   * Processes the Tile clicked on according to the Page layout.
   * @param position ci::vec2
   * @return size_t
   */
  virtual size_t GetMouseEvent(const ci::vec2& position) const = 0;
  
  /**
   * Displays the Tile according to Cinder methodology.
   * @param tile Tile
   */
  static void DrawTile(const Tile& tile);

  /**
   * Displays the Tile with the given rgb values according to Cinder methodology.
   * @param tile Tile
   * @param float r
   * @param float g
   * @param float b
   */
  static void DrawTile(const Tile& tile, float r, float g, float b);
  
  /**
   * Checks if the given position is in the given bounds.
   * @param position ci::vec2
   * @param bounds ci::Rectf
   * @return bool
   */
  static bool IsInBounds(const ci::vec2& position, const ci::Rectf& bounds);
};

} // namespace visualizer

} // namespace wordle
