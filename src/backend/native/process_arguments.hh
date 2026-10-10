#pragma once
#include <string>

namespace LM::Backend::Native {
// _spawnvp flattens argv into a Windows command line. Quote using the CRT
// backslash rules, including trailing slashes and literal quotes.
inline std::string quote_windows_argument(const std::string& argument) {
  std::string result = "\"";
  std::size_t backslashes = 0;
  for (char character : argument) {
    if (character == '\\') {
      ++backslashes;
      continue;
    }
    result.append(character == '"' ? backslashes * 2 + 1 : backslashes, '\\');
    backslashes = 0;
    result += character;
  }
  result.append(backslashes * 2, '\\');
  return result + '"';
}
} // namespace LM::Backend::Native
