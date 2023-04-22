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

typedef vector<arc> graph;
struct donnees {
    graph graphe;
    int nb_sommets;
};



typedef vector<vector<int>> solution;

// Fonctions généralistes 

pair<bool,int> is_in_solution(solution sol, int sommet);
bool is_valid(solution sol, donnees data,int nb_classes);
bool is_in_queue(queue<solution> liste_tabou, solution sol);
float valeur_solution(solution sol, donnees data);
queue<solution> voisinage(donnees data, solution solution_initiale, int nb_classes); //stratégie Pick and Drop
pair<solution,float> init_solution3(int nb_classes, donnees data); // calcule une solution initiale pour les méthodes sauf les énumérations



// fonctions d'affichage 
void print_arc(arc &a);
void print_graph(graph &gr);
void print_solution(pair<solution,float> resultat);
void print_queue_solution(queue<solution> L);

#endif