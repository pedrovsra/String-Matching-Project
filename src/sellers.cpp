#include <string>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "algs.h"
#include <iostream>

int phy(char a, char b) {
	if (a == b) return 0;

	return 1;
}

bool sellers_bool(std::string text, std::string pattern, int e_max) {
        int n = text.length();
        int m = pattern.length();
 
        int S[m], Slinha[m];
 
        for(int i = 0; i < m; i++) {
                Slinha[i] = i;
        }
       
        for(int j = 0; j < n; j++) {
                S[0] = 0;
                for(int i = 1; i < m; i++) {
                        int aux = std::min(Slinha[i] + 1, S[i - 1] + 1);
                        S[i] = std::min(Slinha[i - 1] + phy(pattern[i], text[j]), aux);
                }
               
                if (S[m-1] <= e_max) {
                        return true;
                }
               
               memcpy(Slinha, S, sizeof S);
        }
        return false;
}

std::vector<int> sellers(std::string text, std::string pattern, int e_max) {
        std::vector<int> ret;
        int n = text.length();
        int m = pattern.length();      
 
        int S[m], Slinha[m];
 
        for(int i = 0; i < m; i++) {
                Slinha[i] = i;
        }
       
        for(int j = 0; j < n; j++) {
                S[0] = 0;
                for(int i = 1; i < m; i++) {
                        int aux = std::min(Slinha[i] + 1, S[i - 1] + 1);
                        S[i] = std::min(Slinha[i - 1] + phy(pattern[i], text[j]), aux);
                }
               
                if (S[m-1] <= e_max) {
                        ret.push_back(j - m + e_max + S[m-1]);
                        ret.push_back(j + 1);
                }
               
               memcpy(Slinha, S, sizeof S);
        }
        return ret;
}