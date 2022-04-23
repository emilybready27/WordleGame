#pragma once

#include <string>
#include <cinder/Rect.h>

namespace wordle {

class Tile {
public:
  Tile(const std::string& label, const std::string& color, const ci::Rectf& square);
  
  void SetLabel(const std::string& label);
  const std::string& GetLabel() const;
  void SetColor(const std::string& color);
  const std::string& GetColor() const;
  const ci::Rectf& GetSquare() const;
  
private:
  std::string label_;
  std::string color_;
  ci::Rectf square_;
  
};

} // namespace wordle