#include <string.h>
#include <vector>
#include <set>
#include "FsmAho.h"
#include "kmp.h"
#include "boyer_moore.h"

std::vector<int> shift_or (std::string texto, std::string pattern);
std::vector<int> sellers (std::string texto, std::string pattern, int e_max);
bool sellers_bool (std::string text, std::string pattern, int e_max);
bool wu_manber (std::string text, std::string pattern, int e_max);
bool aho (std::string text, FsmAho fsm);
std::vector<int> aho_c (std::string text, FsmAho fsm);
FsmAho returnFsmAho (std::set<std::string> p);