#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <assert.h>

#define MAX_SIZE 10000
#define ALPHABET_LENGTH 256

class Boyer_Moore {
  private:
    int B[MAX_SIZE];
    int R[MAX_SIZE];
	int Sbm[MAX_SIZE];
	int C[ALPHABET_LENGTH];
    bool initialized;
	void borderB(std::string pattern, int m);
	void borderR(std::string pattern, int m);
 
 public:
    bool search(std::string texto, std::string pattern);
    std::vector<int> search_c(std::string texto, std::string pattern);
    void bad_char(std::string pattern, int m);
	void good_suffix(std::string pattern, int m);
    bool isInitialized(void);
    void init(std::string pattern, int m);
};