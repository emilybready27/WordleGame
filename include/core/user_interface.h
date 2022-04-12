#pragma once

#include <vector>
#include <map>
#include "game.h"

namespace wordle {

/** Class that handles the interaction with the user. */
class UserInterface {
 public:
  /**
   * Initializes the map of text colors.
   */
  UserInterface();

  /**
   * Prints the given message to the output stream.
   * @param output std::ostream
   * @param message std::string
   */
  void Print(std::ostream& output, const std::string& message);
  
  /**
   * Prints the given message ending in a newline to the output stream.
   * @param output std::ostream
   * @param message std::string
   */
  void PrintLn(std::ostream& output, const std::string& message);

  /**
   * Prints the given message to the output stream in the given color.
   * @param output std::ostream
   * @param message std::string
   */
  void Print(std::ostream& output, const std::string& message, const std::string& color);

  /**
   * Prints the given message ending in a newline to the output stream in the given color.
   * @param output std::ostream
   * @param message std::string
   */
  void PrintLn(std::ostream& output, const std::string& message, const std::string& color);
  
  /**
   * Prints the given Board to the output stream using colors.
   * @param output std::ostream
   * @param board Board
   * @param default_color std::string
   * @param semi_correct_color std::string
   * @param correct_color std::string
   */
  void PrintBoard(std::ostream& output,
                  const Board& board,
                  const std::string& default_color,
                  const std::string& semi_correct_color,
                  const std::string& correct_color);
  
  /**
   * Retrieves the user response from the input stream.
   * @param input std::istream
   * @return std::string
   */
  const std::string& GetResponse(std::istream& input);
  
 private:
  /**
   * Message received from the user.
   */
  std::string response_;
  
  /**
   * Message to send to the user.
   */
  std::string message_;
  
  /**
   * Map of colors to their numerical representations.
   */
  std::map<std::string, int> colors_;
};

} // namespace wordle