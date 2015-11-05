#include "boyer_moore.h"
#include <iostream>

void Boyer_Moore::init(std::string pattern, int m) {
	bad_char(pattern, m);
	good_suffix(pattern, m);
	this->initialized = true;
}

std::vector<int> Boyer_Moore::search_c(std::string text, std::string pattern) {
	std::vector<int> ret;
	
	int n = text.length();
	int m = pattern.length();

	int j;
	int i = 0;

	while(i < (n - m + 1)) {
		j = m - 1;
		while (j > 0 && text[i + j] == pattern[j]) {
			j--;
		}
		if (j == 0) {
			ret.push_back(i);
		}
		int bcskip;
		if(j > 0 && (pattern.find(text[i + j]) != std::string::npos)) {
			bcskip = j - C[text[i+j]];
		} else {
			bcskip = j + 1;
		}
		int gsskip = Sbm[j];
		
		i += std::max(bcskip, gsskip);
	}
	return ret;
}

bool Boyer_Moore::search(std::string text, std::string pattern) {

	int n = text.length();
	int m = pattern.length();

	int j;
	int i = 0;

	while(i < (n - m + 1)) {
		j = m - 1;
		while (j >= 0 && text[i + j] == pattern[j]) {
			j--;
		}
		
		if (j < 0)
			return true;
			
		int bcskip;
		if(j > 0 && (pattern.find(text[i + j]) != std::string::npos)) {
			bcskip = j - C[text[i+j]];
		} else {
			bcskip = j + 1;
		}
		int gsskip = Sbm[j];
		
		i += std::max(bcskip, gsskip);
		
	}
	return false;
}

void Boyer_Moore::bad_char(std::string pattern, int m) {
	for(int i = 0; i < m; i++) {
		C[pattern[i]] = i;
	}
}

void Boyer_Moore::good_suffix(std::string pattern, int m) {
	
	borderB(pattern, m);
	std::reverse(pattern.begin(), pattern.end());
	borderR(pattern, m);
	
	for(int i = 0; i <= m+1; i++) {
		Sbm[i] = m - B[m];
	}
	
	int j;
	for(int t = 1; t <= m; t++) {
		j = m - 1 - R[t];
		assert(j >= 0 && j < m);
		if(Sbm[j] > t - R[t]) {
			Sbm[j] = t - R[t];
		}
	}
}

void Boyer_Moore::borderB(std::string pattern, int m) {
	
	B[0] = -1;
	for(int i = 1; i <= m; i++) B[i] = 0;
	
	if(m == 1 || (m > 1 && pattern[0] != pattern[1])) 
		B[1] = 0;
		
	int i = 1, j = 0;
	
	while(i < m) {
		while ((i + j) < m && pattern[j] == pattern[i + j]) {
			j++;
			B[i + j] = j;
		}
		i += (j - B[j]);
		j = std::max(0 , B[j]);
	}
}

void Boyer_Moore::borderR(std::string pattern, int m) {
	
	R[0] = -1;
	for(int i = 1; i <= m; i++) R[i] = 0;
	
	if(m == 1 || (m > 1 && pattern[0] != pattern[1]))
		R[1] = 0;
		
	int i = 1, j = 0;
	
	while(i < m) {
		while ((i + j) < m && pattern[j] == pattern[i + j]) {
			j++;
			R[i + j] = j;
		}
		i += (j - R[j]);
		j = std::max(0 , R[j]);
	}
}

bool Boyer_Moore::isInitialized(void) {
  return this->initialized;
}