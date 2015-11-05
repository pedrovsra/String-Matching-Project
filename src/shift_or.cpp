#include <string>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "algs.h"

const int ALPHABET_SIZE = 256;

unsigned int S[ALPHABET_SIZE];

int char_mask(std::string pattern);

std::vector<int> shift_or(std::string text, std::string pattern) {
	std::vector<int> ret;

	int n = text.length();
	int m = pattern.length();

	unsigned int lim;
	unsigned int state = ~0;

	lim = char_mask(pattern);

	for(int i = 0; i < n; ++i) {
		state = (state << 1) | S[text[i]];

		if(state < lim) {
			ret.push_back(i - m + 1);
		}
	}
	return ret;
}

int char_mask(std::string pattern) {
	unsigned int j = 1, lim = 0;

	int m = pattern.length();

	for(int i = 0; i < ALPHABET_SIZE; ++i) {
		S[i] = ~0;
	}

	for(int i = 0; i < m; ++i, j <<= 1) {
		S[pattern[i]] &= ~j;
		lim |= j;
	}
	lim = ~(lim >> 1);
	return lim;
}