#pragma once

#include <string>

namespace wordle {

class Tile {
public:
  Tile(const std::string& label, const std::string& color);
  
  const std::string& GetLabel() const;
  const std::string& GetColor() const;
  
private:
  std::string label_;
  std::string color_;

};

} // namespace wordle