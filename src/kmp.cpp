#include "kmp.h"

void KMP::search(std::string texto, std::string pattern) {
  // E <- {} 
  //this->index = 0;
  //std::vector<int> occ;
  // T = t1...tn
  int n = texto.length();
  // P = p1...pm
  int m = pattern.length();
  // next <- init_next(P)
  //init_next(pattern);
  
  // i, j <- 1, 0
  int i = 0, j = 0;
  // enquanto i <= n - m + 1 faça
  while (i <= (n - m + 1)) {
    // enquanto j < m e T[i+j] = P[1 + j]
    while ((j <= m) && (texto[i + j] == pattern[j])) {
      // j <- j + 1
      j++;
    }
    // se j = m entao // match
    if(j == m) {
      //occ.push_back(i);
      puts(texto.c_str());
      return;
    }
    // i <- i + j - next[j]
    i = (i + j - next[j]);
    // j <- max{0, next[j]}
    j = std::max(0, next[j]);
  }
  //return occ;
}

std::vector<int> KMP::search_c(std::string texto, std::string pattern) {
  // E <- {} 
  std::vector<int> occ;
  // T = t1...tn
  int n = texto.length();
  // P = p1...pm
  int m = pattern.length();
  // next <- init_next(P)
  //init_next(pattern);
  
  // i, j <- 1, 0
  int i = 0, j = 0;
  // enquanto i <= n - m + 1 faça
  while (i <= (n - m + 1)) {
    // enquanto j < m e T[i+j] = P[1 + j]
    while ((j <= m) && (texto[i + j] == pattern[j])) {
      // j <- j + 1
      j++;
    }
    // se j = m entao // match
    if(j == m) {
      occ.push_back(i);
    }
    // i <- i + j - next[j]
    i = (i + j - next[j]);
    // j <- max{0, next[j]}
    j = std::max(0, next[j]);
  }
  return occ;
}

void KMP::init_next(std::string pattern) {
  this->initialized = false;
  // B <- (-1, ..., -1)
  memset(next, -1, sizeof next);
  
  int tam = pattern.length();
  // memset(next, -1, sizeof next);
  
  // se P[1] != P[2] entao B[1] = 0
  if(pattern[0] != pattern[1]) {
  //if (seq[1 - 1] != seq[2 - 1]) { //-1 por causa do indice
      this->next[1] = 0;
  }
  // i, j <- 2, 0
  int i = 2, j = 0;
  // enquanto i <= m faça
  while(i <= tam) {
    // enquanto i+j <= m e P[i+j] = P[1+j] faça
    while(((i + j) < tam) && (pattern[i + j] == pattern[1 + j])) {
      // j <- j + 1
      j++;
      // se B[i + j - 1] = 1 entao // primeira vez nesse 'i'
      if(this->next[i + j - 1] == 1) {
        // se (i + j - 1) = m ou P[i+j] != P[j] entao
        if(((i + j - 1) == tam) || pattern[i + j] != pattern[j]) {
          // B[i + j - 1] <- j
          this->next[i + j - 1] = j;
        } // senao
        else {
          // B[i + j - 1] <- B[j]
          this->next[i + j - 1] = this->next[j];    
        }
      } 
    }
    // i <- i + j - B[j]
    i = (i + j - this->next[j]);
    // j <- max{0, B[j]}
    j = std::max(0, this->next[j]);
  }
  //return next;
  this->initialized = true;
}

bool KMP::isInitialized(void) {
  return this->initialized;
}