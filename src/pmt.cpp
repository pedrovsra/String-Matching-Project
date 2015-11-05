#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <glob.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include "algs.h"
#include "utils.h"

static int findPatternFlag;

bool equalsToOptions(char str[]);
std::string fileToString(std::string textFile);
void getPatterns(std::string fileName);


// FUNCOES/VARIAVEIS AUXILIARES
std::vector<std::string> wildcard; // livro*.txt por exemplo
std::string tracop = "-p", tracoe = "-e", edit = "--edit", pattern = "--pattern", tracoc = "-c", color = "--color";
/////////////////////////////////

inline std::vector<std::string> glob(const std::string& pat) {
    glob_t glob_result;
    glob(pat.c_str(), GLOB_TILDE, NULL, &glob_result);
	
    std::vector<std::string> ret;
	
    for(unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
        ret.push_back(std::string(glob_result.gl_pathv[i]));
    }
	
    globfree(&glob_result);
	
    return ret;
}

// vector de arquivos texto
std::vector<std::string> textFiles;
// set dos padroes
std::set<std::string> patterns_set;

int main (int argc, char **argv) {
	findPatternFlag = 0;
	std::string patternFile = "", patternStr = "";
	
	int c, color_flag = 0, help_flag = 0, edit_flag = 0, pattern_flag = 0, emax;
	
	while (1) {
		static struct option long_options[] = {
			{"help", no_argument, 0, 'h'},
			{"edit", required_argument, 0, 'e'},
			{"pattern", required_argument, 0, 'p'},
			{"color", no_argument, 0, 'c'},
			{0, 0, 0, 0}
		};
		// getopt_long guarda o indice da opcao aqui
		int option_index = 0;
		
		c = getopt_long (argc, argv, "che:p:", long_options, &option_index);
		
		// detecta o fim das opcoes
		if (c == -1) {
			break;
		}
		
		switch (c) {
			case 'c':
				color_flag = 1;
			break;
			case 'h':
				help_flag = 1;				
			break;
			case 'e':
				emax = atoi(optarg);
				edit_flag = 1;
			break;
			case 'p':
				// optarg eh o argumento da option;
				patternFile = std::string(optarg);
				pattern_flag = 1;
			break;
			default:
				abort();
		}
	}
	
	
	if (pattern_flag) {
		// pegando os padroes do arquivo
		wildcard = glob(patternFile);
		
		for(std::vector<std::string>::iterator itPF = wildcard.begin(); itPF != wildcard.end(); ++itPF) {
			getPatterns(*itPF);
		}
	}	
	
	for (int i = 1; i < argc; i++) {
		if(!equalsToOptions(argv[i])) {
			if((pattern_flag == 0) && (patternStr.compare("") == 0)) {
				// nao achou a patternFlag e pattern continua vazio
				patternStr = std::string(argv[i]);
			} else {				
				/*
				um pouco mais lento que o normal,
				mas ja garante o caso de wildcards
				*/
				wildcard = glob(std::string(argv[i]));

				for(int w = 0; w < wildcard.size(); w++) {
					textFiles.push_back(wildcard[w]);
				}
			}
		} else {
			// pula o proximo ja que toda opt tem argumento, exceto a color
			if (!(((tracoc.compare(argv[i])) == 0) || ((color.compare(argv[i])) == 0))) {
				i++;
			}
		}
	}

	// se o usuario n tiver utilizado -h, --help
	if(!help_flag) {
		// percorrendo pelo vector de arquivos texto
		for(std::vector<std::string>::iterator it = textFiles.begin() ; it != textFiles.end(); ++it) {
		// pegando o texto dentro do arquivo
			std::string file_string;
	
			char tab2[1024];
			strcpy(tab2, (*it).c_str());
			
			std::ifstream myfile (tab2);
			if (myfile.is_open()) {
				FsmAho fsmAho;
				KMP kmp;
				Boyer_Moore bm_in;
				while (!myfile.eof()) {
					getline (myfile,file_string);

					// caso seja -e, --edit
					if(edit_flag) {
						bool ret = false;
						if(pattern_flag) {
							for (std::set<std::string>::iterator itP = patterns_set.begin(); itP != patterns_set.end(); ++itP) {
								if (color_flag) {
									std::vector<int> sell_ret = sellers(file_string, *itP, emax);
	
									if (sell_ret.size() > 0){
										printColorResultAho(sell_ret, file_string);
										break;
									}
								} else {
									if(sellers_bool(file_string, *itP, emax)) {
										printf("%s\n", file_string.c_str());
										break;
									}
								}
							}
						} else {
							if(color_flag){
								std::vector<int> sell_ret = sellers(file_string, patternStr, emax);
								if(sell_ret.size() > 0)
									printColorResultAho(sell_ret, file_string);
							} else {
								if(sellers_bool(file_string, patternStr, emax)) {
									printf("%s\n", file_string.c_str());
								}
							}
						}			
					}
					// caso seja -p, --patterns
					else if(pattern_flag) {
						if(fsmAho.g.size() == 0){
							fsmAho = returnFsmAho(patterns_set);
						}
						
						if(color_flag) {
							std::vector<int> aho_r = aho_c(file_string, fsmAho);
							
							if(aho_r.size() > 0) {
								printColorResultAho(aho_r, file_string);
							}
						} else {
							if(aho(file_string, fsmAho))
								printf("%s\n", file_string.c_str());	
						}
					}
					// caso nao seja --edit
					else {						
						if(!bm_in.isInitialized()) {
							bm_in.init(patternStr, patternStr.length());
						}
						
						if (color_flag) {
							std::vector<int> bm_r = bm_in.search_c(file_string, patternStr);
							if(bm_r.size() > 0) 
								printColorResult(bm_r, file_string, patternStr);
						} else {
							if(bm_in.search(file_string, patternStr)) {
								printf("%s\n", file_string.c_str());
							}
						}
					}
				}	
				myfile.close();
			} else {
				printf("Unable to open text file\n");
			}
		}
	} else { // opcao -h, --help foi escolhida
		showHelp();
	}
	
	exit (0);
}

// FUNCOES AUXILIARES ------------------------

bool equalsToOptions(char str[]) {
	if (((tracoe.compare(str)) == 0) || ((edit.compare(str)) == 0) ||
	((tracop.compare(str)) == 0) || ((pattern.compare(str)) == 0) ||
	((tracoc.compare(str)) == 0) || ((color.compare(str)) == 0)) {
		return true;
	} else {
		return false;
	}
}

std::string fileToString (std::string textFile) {
	std::string line, retorno;
	
	char tab2[1024];
	strcpy(tab2, textFile.c_str());
	
	std::ifstream myfile (tab2);
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			getline (myfile,line);
			retorno += line;
			retorno += "\n";
		}
		myfile.close();
	} else {
		printf("Unable to open text file\n");
	}
	return retorno;
}

void getPatterns(std::string fileName) {
	std::string line;
	
	char tab2[1024];
	strcpy(tab2, fileName.c_str());
	
	std::ifstream myfile(tab2);
	
	if(myfile.is_open()) {
		while(!myfile.eof()) {
			getline(myfile, line);
			patterns_set.insert(line);
		}
		myfile.close();
	} else {
		printf("Unable to open pattern file\n");
	}
}