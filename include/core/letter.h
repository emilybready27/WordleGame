#pragma once

#include <string>

namespace wordle {
    
/** Alphabetical letter used in construction of Words. */
class Letter {
 public:
  /**
   * Default Letter is empty: '_' with color gray.
   */
  Letter();
  
  /**
   * Constructs Letter with a character representation and color.
   * @param letter char
   * @param color std::string
   */
  Letter(char letter, const std::string& color);

  /**
   * Two Letters are equal if their character representations are equal.
   * @param other Letter
   * @return bool
   */
  bool operator==(const Letter &other) const;
  
  /**
   * Retrieves character representation.
   * @return char
   */
  char ToChar() const;
  
  /**
   * Set the Letter color.
   * @param color std::string
   */
  void SetColor(const std::string& color);
  
  /**
   * Get the Letter color.
   * @return std::string
   */
  const std::string& GetColor() const;
  
 private:
  /**
   * Character representation.
   */
  char letter_;
  
  /**
   * Color used to determine correctness of Letter.
   */
  std::string color_;
};

} // namespace wordle