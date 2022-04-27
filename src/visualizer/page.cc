#include "visualizer/page.h"

namespace wordle {

namespace visualizer {
    
void Page::DrawTile(const Tile& tile) {
  ci::gl::color(ci::Color(&(tile.GetColor()[0])));
  ci::gl::drawSolidRect(tile.GetBounds());
  ci::gl::drawStringCentered(tile.GetLabel(),
                             tile.GetBounds().getCenter() - ci::vec2(0, tile.GetBounds().getHeight() / 4),
                             ci::Color("black"),
                             ci::Font("Arial", 50.0));
}

bool Page::IsInBounds(const ci::vec2& position, const ci::Rectf& bounds) {
  return position.x >= bounds.x1
         && position.x <= bounds.x2
         && position.y >= bounds.y1
         && position.y <= bounds.y2;
}
    
} // namespace visualizer

} // namespace wordle