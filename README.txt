Recife, 25 de Outubro de 2015
Centro de Informática - CIn/UFPE
Processamento de Cadeias de Caracteres - if767

Implementação do primeiro projeto
pmt - ferramenta de identificação de padrões exatos e/ou aproximados

Ferramenta desenvolvida utilizando C++ na plataforma Linux (Ubuntu 14.04 LTS)

Integrantes:
	Carlos Henrique Gonçalves e Silva - chgs
	Pedro Tiago de V. S. R. Araújo - ptvsr
	
Instruções para compilação:
	- para compilar o projeto, basta executar o comando "make" no terminal, na pasta base do mesmo.
	
Instruções para execução:
	- para executar o projeto, basta executar o seguinte comando no terminal, na pasta base do mesmo:
		$ pmt [option(s)] pattern textfile [textfile...]
	onde [option(s)] pode/m sem uma/as seguintes:
		-e/--edit e_max: localiza todas as ocorrências aproximadas do padrão a uma distância de edição máxima 'e_max'
		-p/--pattern pattern_file: realiza a busca de todos os padrões contidos no arquivo 'patternfile'
		-c, --color: imprime os resultados com os padrões destacados na cor vermelha