#include <stdio.h>
#include "utils.h"

void showHelp() {
	puts("pmt versão final 0.25.10.15 - 25/10/2015");
	puts("Desenvolvido por:");
	puts("Carlos Henrique Gonçalves e Silva (chgs@cin.ufpe.br)");
	puts("Pedro Tiago de V. S. R. Araújo (ptvsr@cin.ufpe.br)\n");
	puts("Sintaxe básica:");
	puts("$ pmt [options] pattern textfile [textfile...]");
	puts("O padrão 'pattern' será procurado no(s) arquivo(s) 'textfile'");
	puts("Também é possível utilizar 'wildcards' (e.g. livro*.txt).");
	puts("Para busca aproximada:");
	puts("-e, --edit e_max");
	puts("localiza todas as ocorrências aproximadas do padrão a uma distância de edição máxima e_max\n");
	puts("-p, --pattern patternfile");
	puts("realiza a busca de todos os padrões contidos no arquivo 'patternfile'.\n");
	puts("-c, --color");
	puts("imprime os resultados com os padrões destacados na cor vermelha.\n");
}

void printColorResult(std::vector<int> occ, std::string text, std::string pattern) {
	int size = pattern.length();
	int text_size = text.length();
	std::string aux;
	int i = 0;
	
	for(std::vector<int>::iterator it = occ.begin() ; it != occ.end(); ++it) {
		aux = text.substr(i, *it);

		printf("%s", aux.c_str());

		printf("%s%s%s", COLOR_RED, pattern.c_str(), COLOR_DEF);
		i = *it + size;
	}
	aux = text.substr(i, text_size);

	printf("%s\n", aux.c_str());
}

void printColorResultAho(std::vector<int> occ, std::string text){
	int x = 0, y = 0, par = 0, text_size = text.length();
	
	std::string aux, pattern;
	
	for(std::vector<int>::iterator it = occ.begin() ; it != occ.end(); ++it) {
		if (par) {
			aux = text.substr(y, x - y); //do ultimo padrao ate o novo
			pattern = text.substr(x, *it - x); //o padrao em s
			
			printf("%s", aux.c_str());
			
			printf("%s%s%s", COLOR_RED, pattern.c_str(), COLOR_DEF);

			y = *it;
			par = 0;
		} else {
			if(*it < y)
				x = y;
			else
				x = *it;
			par = 1;
		}
	}
	aux = text.substr(y, text_size);
	printf("%s\n", aux.c_str());
}