#include <string>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <bitset>
#include <iostream>
#include "algs.h"

#define ALPHABET_SIZE 256
#define BIT_SIZE 32

unsigned int chmasks[500];
unsigned int Swu[100];

void char_mask(std::string pattern, int m);

bool wu_manber(std::string text, std::string pattern, int e_max) {	

	int n = text.length();
	int m = pattern.length();

	//C = (Ca1, ..., Cal) <- char_mask(P)
	char_mask(pattern, m);
	
	// msb_mask <- 2 ^ m-1
	unsigned int msb_mask = 1 << m-1;
	//cout << msb_mask << endl;
	
	// S[0] <- 11...1
	Swu[0] = ~0;
	Swu[0] >>= (BIT_SIZE - m);
	
	// para q <- 1, .., r faça
	for(int q = 1; q <= e_max; q++) {
		// S[q] <- S[q-1] << 1
		Swu[q] = Swu[q-1] << q;
	}
	
	int Slinha, S2linhas;
	// para j = 1, ..., n faça
	for(int j = 0; j < n; j++) {
		// S' < S[0]
		Slinha = Swu[0];
		// S[0] <- (S[0] << 1) | Ct[j]
		Swu[0] = ((Swu[0] << 1) | chmasks[j]);
		// para q = 1, ..., r faça
		for(int q = 1; q <= e_max; q++) {
			// S'' <- S[q]
			S2linhas = Swu[q];
			/* S[q] <- (S[q] << 1 | Ct[j]) // (a) 
					& (S' << 1) // (b) 
					& (S[q-1] << 1) // (c) 
					& (S') // (d) */
			Swu[q] = ((Swu[q] << 1) | chmasks[j]) & (Slinha << 1) & (Swu[q-1] << 1) & (Slinha);
			// S' <- S''
			Slinha = S2linhas;
		}
		// se S[r] & msb_mask = false, entao
		if((Swu[e_max] & msb_mask) == 0) {
			// A <- A U {j}
			return true;
		}
	}	
	return false;
}

void char_mask(std::string pattern, int m) {
	memset(chmasks, 0, sizeof chmasks);
	memset(Swu, 0, sizeof Swu);
	
	unsigned int j = 1;
	//int m = pattern.length();

	// C <- (111...1, ..., 111...1) 
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		chmasks[i] = ~0;
		chmasks[i] >>= (BIT_SIZE - m);
		// cout << chmasks[i] << endl;
	}
	// one <- 00...01
	 unsigned int one = 1;

	// pos_mask <- 111...10 // ~one
	 unsigned int pos_mask = ~one;
	 pos_mask >>= (BIT_SIZE - m);
	 pos_mask ^= 1;

	// para i <- 1, ..., m faça
	for(int i = 1; i < m; i++) {
		// Cp[i] <- Cp[i] & pos_mask
		chmasks[i] &= pos_mask;
		pos_mask = ((pos_mask << 1) | one);
	}
}