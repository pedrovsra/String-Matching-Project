#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX_SIZE 10000

class KMP {
  private:
    int next[MAX_SIZE];
    int occ[MAX_SIZE];
    int index;
    bool initialized;
 
 public:
    void search(std::string texto, std::string pattern);
    std::vector<int> search_c(std::string texto, std::string pattern);
    void init_next(std::string pattern);
    bool isInitialized(void);
};