#include <vector>
#include <string>

const char COLOR_RED[] = {"\033[1;31m"};
const char COLOR_DEF[] = {"\033[0m"};

void showHelp();
void printColorResult(std::vector<int> occ, std::string text, std::string pattern);
void printColorResultAho(std::vector<int> occ, std::string text);