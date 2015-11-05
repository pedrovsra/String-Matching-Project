#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <set>
#include "FsmUkk.h"

int phy(char a, char b);
int index(std::vector< std::vector<int> > index, std::vector<int> s);
std::vector<int> next_collumn(std::vector<int>slinha, char a);
FsmUkk build_ukk_fda(std::string pat, int emax);
std::vector<int> ukkVec(std::string text, FsmUkk fsm);

int m; //tamanho do padrao
int r;// r = emax
std::string pattern;


int main (int argc, char **argv) {
	FsmUkk fsm = build_ukk_fda("pedro", 1);
	std::vector<int> ret = ukkVec("oi pedra oi", fsm);
			std::cout<<"\n RESPOSTA:" << ret.size();

	for (std::vector<int>::iterator i = ret.begin(); i != ret.end(); ++i)
	{
		std::cout<<*i << " ";
	}
	std::cout << std::endl;
	return 0;
}

std::vector<int> ukkVec(std::string text, FsmUkk fsm){
	std::vector<int> ret;
	// std::vector<int> s = fsm.q0; 
	int s = 0;
	std::vector< std::vector<int> > indice = fsm.indice;

	for (std::vector<int>::iterator i = fsm.f.begin(); i != fsm.f.end(); ++i){
		std::cout<<*i << " ";
	}

	// int index_s = index(indice, s);

	for (std::vector<int>::iterator i = fsm.f.begin(); i != fsm.f.end(); ++i){
		if(s == *i){
			ret.push_back(0);
			break;
		}
	}
	for (int j = 1; j < text.length(); ++j){
		// int k = fsm.o[index(indice, s)][(int)text[j]];
		s = fsm.o[s][(int)text[j]];

		// std::cout<<k<<" ";
		for (std::vector<int>::iterator p = fsm.f.begin(); p != fsm.f.end(); ++p){
			if(s == *p){
				ret.push_back(j);
			}
		}
	}
	return ret;
}

FsmUkk build_ukk_fda(std::string pat, int emax){
	pattern = pat;
	m = pattern.length();
	r = emax;

	std::vector<int> s; // livro*.txt por exemplo
	s.resize(m+1, 0); 
	for (int i = 0; i <= m; ++i){
		s[i] = i;
	}
	int i = 0;
	std::vector< std::vector<int> > indice;
	indice.push_back(s); // index(s) = 0
	std::queue< std::vector<int> > n;
	n.push(s);
	std::set< std::vector<int> > q;
	q.insert(s);
	std::vector<int> f;
	
	std::vector< std::vector<int> > o;
	///////////////////////////ver se isso ta certo e descobrir o max_estados
	int max_estados = 255, alfabeto = 255;
	
	o.resize(max_estados+1);
    for (int i = 0; i < max_estados+1; ++i){
        o[i].resize(alfabeto+1, 0);

    }
    //////////////////////////////////////////////
	if(m <= r){
		f.push_back(0);
	}

	while(!n.empty()){
		std::vector<int> slinha = n.front();
		n.pop();

		for (int a = 32; a < 125; ++a){
			s = next_collumn(slinha, (char)a);
	
			//if(q.find(s)==q.end()){
			// std::cout<<"S \n ";
			// for (std::vector<int>::iterator ik = s.begin(); ik != s.end(); ++ik){
			// 	 std::cout<<*ik << " ";
			// }
			// 	std::cout<<"q \n ";
			// for (std::set< std::vector<int> >::iterator it = q.begin(); it != q.end(); ++it){
			// 	std::vector<int> ab = (*it);
			// 	for (std::vector<int>::iterator ik = ab.begin(); ik != ab.end(); ++ik){
			// 		std::cout<<*ik << " ";
			// 	}
			// std::cout<<"\n ";
			// }
			// std::cout<<"end \n ";		
			//}
			if(q.find(s)==q.end()){
				q.insert(s);
				n.push(s);
				indice.push_back(s);// index (s) = i
				i++;
				if(s[m] <= r){
					// f.push_back(indice.size()-1);
					f.push_back(index(indice, s));
					// std::cout<< " ---- " <<(char)a << " - "<<i<<" " << index(indice, s) << "  "<< indice.size()<<" \n";
				}
			}
			// std::cout<< " kek " << a << " \n";
			o[index(indice, slinha)][a] = index(indice, s);
		}
	}
	// std::cout<< " ---- "<< "  "<< indice.size()<<" \n";

	FsmUkk fsmret;
	fsmret.o = o;
	fsmret.f = f;
	//q0 = (0....i)
	std::vector<int> q0; // livro*.txt por exemplo
	for (int p = 0; p <= i; ++p){
		q0.push_back(p);
	}
	fsmret.q0 = q0;
	fsmret.indice = indice;
	return fsmret;
}

int index(std::vector< std::vector<int> > index, std::vector<int> vector1){
	int ret = 0;
	// for (std::vector<int>::iterator i = s.begin(); i != s.end(); ++i){
	// 	 std::cout<<*i << " ";
	// }
	// std::cout << " \n";
	
	for (std::vector< std::vector<int> >::iterator vector2 = index.begin(); vector2 != index.end(); ++vector2){
		ret++;
		bool is_equal = false;
	 	if ( vector1.size() < (*vector2).size() )
	    	is_equal = std::equal ( vector1.begin(), vector1.end(), (*vector2).begin() );
	 	else
		    is_equal = std::equal ( (*vector2).begin(), (*vector2).end(), vector1.begin() );

		if(is_equal){
			return ret;
		}

	}
	return 0;
}

std::vector<int> next_collumn(std::vector<int>slinha, char a){
	std::vector<int> s; // livro*.txt por exemplo
	s.resize(m+1, 0); 
	for (int i = 1; i <= m; ++i){
		s[i] = std::min(slinha[i-1] + phy(pattern[i], a), std::min(slinha[i] +1, std::min(slinha[i-1]+1, r+1)));
	}
	return s;
}

int phy(char a, char b) {
	if (a == b) return 0;

	return 1;
}

