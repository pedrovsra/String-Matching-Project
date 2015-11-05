#include <vector>
#include <set>
#include <string>
#include "FsmAho.h"

void build_goto();
void build_fsm();
void build_fail();
int calcEst(std::vector<std::string> p);
void setG(int max_estados, int alfabeto);
void fillVector(std::set<std::string> p);

std::vector<std::string> pat;
std::vector< std::vector<int> > occ ;
std::vector<int> f;
std::vector<std::vector<int> > g; 

 FsmAho returnFsmAho(std::set<std::string> p){
    fillVector(p);
    int alfabeto = 255; // tamanho do alfabeto
    int max_estados = calcEst(pat); //numero maximo de estados
    
    f.resize(max_estados+1, -1);
    occ.resize(max_estados+1);     
    setG(max_estados+1, alfabeto+1);

    build_fsm();
    
    FsmAho fsm_ret;
    fsm_ret.occ = occ;
    fsm_ret.f = f;
    fsm_ret.g = g;

    return fsm_ret;
 }

bool aho(std::string text, FsmAho fsm){
    
    occ = fsm.occ;
    g = fsm.g;
    f = fsm.f;

    int cur = 0;
    for (int i = 0; i < text.length(); i++){
        while ( g[cur][(int)text.at(i)] == -1){
            if(f[cur] == -1){
                cur = 0;
            }else{
                cur = f[cur];
            }
        }

        if((int)text.at(i) < 255 && (int)text.at(i) > 0)
            cur = g[cur][(int)text.at(i)];

        for (std::vector<int>::iterator it = occ[cur].begin(); it != occ[cur].end(); ++it) {
            return true;
        } 
    }
    return false;
}

std::vector<int> aho_c(std::string text, FsmAho fsm){
    
    occ = fsm.occ;
    g = fsm.g;
    f = fsm.f;

    std::vector<int> ret;

    int cur = 0;
    for (int i = 0; i < text.length(); i++){
        while ( g[cur][(int)text.at(i)] == -1){
            if(f[cur] == -1){
                cur = 0;
            }else{
                cur = f[cur];
            }
        }

        if((int)text.at(i) < 255 && (int)text.at(i) > 0)
            cur = g[cur][(int)text.at(i)];

        for (std::vector<int>::iterator it = occ[cur].begin(); it != occ[cur].end(); ++it) {
            ret.push_back(i - pat[(*it)].length()+1);
            ret.push_back(i + 1); //index do fim do padrao
        } 
    }
    return ret;
}

void build_fsm(){
    build_goto();
    build_fail();
}

void build_goto(){
    int next = 0;
    int k = -1;
    for (std::vector<std::string>::iterator i = pat.begin(); i != pat.end(); ++i){
        k++;
        int cur = 0, j=0;
        while( (j < (*i).length()) && (g[cur][(int)(*i).at(j)]) != -1 ) {
            cur = g[cur] [(int)((*i).at(j))];
            j++;
        }
        while (j < (*i).length()){
            next++;
            g[cur][(int)(*i).at(j)] = next;
            cur = next;
            j++;
        }
        occ[cur].push_back(k);
    }

    for (int i = 0; i<255; i++) {
        if( (g[0][i]) == -1){
            g[0][i] = 0;
        }
    }
}

void build_fail(){
    std::vector<int> Q;
    for(int c = 0; c<255; c++){
        if(g[0][c] != 0){
            Q.push_back(g[0][c]);
            f[g[0][c]] = 0;
        }
    }
    
    while(Q.size() > 0){
        int cur = Q.back();
        Q.pop_back();
        for (int a = 0; a<255; a++) {
            int  next = g[cur][a];
            if(next!=-1){
                Q.push_back(next);
                int brd = f[cur];
                while(g[brd][a] == -1){
                    brd = f[brd];
                }
                f[next] = g[brd][a];
                for (std::vector<int>::iterator i = occ[f[next]].begin(); i != occ[f[next]].end(); ++i){
                    occ[next].push_back(*i);
                }
            }
        }
    }
}

int calcEst(std::vector<std::string> p){
    int k =0;
    for (std::vector<std::string>::iterator i = p.begin(); i != p.end(); ++i){
        k += (*i).size();
    }
    return k;
}

void setG(int max_estados, int alfabeto){
    g.resize(max_estados+1);
    for (int i = 0; i < max_estados+1; ++i){
        g[i].resize(alfabeto+1, -1);

    }
}

void fillVector(std::set<std::string> p){
    for(std::set<std::string>::iterator itSet = p.begin(); itSet != p.end(); ++itSet) {   
        pat.push_back(*itSet);
    }
}