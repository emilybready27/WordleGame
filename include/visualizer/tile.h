#pragma once

#include <string>
#include <cinder/Rect.h>

namespace wordle {

/** Rectangular text box displayed in a Page. */
class Tile {
public:
  Tile() = default;
  Tile(const std::string& label, const std::string& color, const ci::Rectf& bounds);
  
  void SetLabelAndColor(const std::string& label, const std::string& color);
  void SetLabel(const std::string& label);
  const std::string& GetLabel() const;
  void SetColor(const std::string& color);
  const std::string& GetColor() const;
  void SetBounds(const ci::Rectf& bounds);
  const ci::Rectf& GetBounds() const;
  
private:
  std::string label_;
  std::string color_;
  ci::Rectf bounds_;
  
};

} // namespace wordle