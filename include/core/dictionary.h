#pragma once

#include <string>
#include <vector>

namespace wordle {

class Dictionary {
 public:
  Dictionary();
  
  const std::string& GenerateNewWord();
  bool Contains(const std::string& target) const;
 private:
  std::string path_to_dictionary_ =
          R"(C:\Users\Mary\Desktop\Cinder\my-projects\final-project-ebready2\resources\dictionary.txt)";
  std::vector<std::string> words_;
  size_t word_counter_;
};

} // namespace wordle