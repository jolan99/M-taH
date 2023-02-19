#ifndef Utiles_h
#define Utiles_h
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
#include <Cmath>
using namespace std;

// Les structures utilisées 
struct arc {
    int predecesseur;
    int voisin;
    float cost;
};

typedef vector<arc> graphe;
struct donnees {
    graphe graphe;
    int nb_sommets;
};



typedef vector<vector<int>> solution;

// Fonctions généralistes 

pair<bool,int> is_in_solution(solution sol, int sommet);
bool is_valid(solution sol, donnees data,int nb_classes);
float valeur_solution(solution sol, donnees data);


// fonction d'affichage 
void print_arc(arc &a);
void print_graph(graphe &gr);
void print_solution(pair<solution,float> resultat);
void print_solution(solution sol);
void print_queue_solution(queue<solution> L);

#endif