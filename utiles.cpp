#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
#include "utiles.h"
#include <Cmath>
using namespace std;



void print_arc(arc &a){
    cout <<"predecesseur: "<<a.predecesseur<< " voisin : " << a.voisin<<" coût : " << a.cost << endl;
}

void print_graph(graphe &gr){
    int i = 0;
    for (auto it = gr.begin(); it!= gr.end(); ++it) {
        print_arc(*it);
    }
}


pair<bool,int> is_in_solution(solution sol, int sommet){ // regarde si un sommet est déjà dans mis dans un groupe et lequel
    bool verif = false;
    int num_groupe = -1;
    int iterateur = 1;
    pair<bool,int> resultat;
    for(auto it = sol.begin(); it!= sol.end(); ++it){ // on énumère sur tous les groupes
        vector<int> groupe = *it;
        for(auto is = groupe.begin(); is!= groupe.end(); ++is){ // on énumère sur tous les membres du groupe
            if(sommet == *is){
                verif = true;
                num_groupe = iterateur ;
            }
        }
        iterateur +=1;
    }
    resultat.first = verif;
    resultat.second = num_groupe;
    return resultat;
}


bool is_valid(solution sol, donnees data,int nb_classes){
    bool resultat = true;
    int nb_sommets = data.nb_sommets;
    float nb_sommets_float = float(nb_sommets);
    float nb_classes_float = float(nb_classes);

    
    //graphe gr = data.graphe;
    // tous les  sommets sont dans la solution
    //vector<bool> condition1(false,nb_sommets);
    for(int i=0; i < nb_sommets; ++i){
        if(!(is_in_solution(sol, i+1).first)){ // si un sommet n'est pas dans la solution, alors pas réalisable
            resultat = false;
        }
    }
    // respecte la condition d'équilibre 
    for(int i = 0; i< nb_classes; ++i){
        if(sol[i].size() > ceil(nb_sommets_float/nb_classes_float) + (0.01 * (nb_sommets_float/nb_classes_float)) || sol[i].size() < floor(nb_sommets_float/nb_classes_float) - (0.01 * (nb_sommets_float/nb_classes_float))){
            // cout << "borne sup : " << ceil(nb_sommets/nb_classes) + (0.01 * (nb_sommets/nb_classes)) << endl; 
            // cout <<"borne inf " << floor(nb_sommets/nb_classes) - (0.01 * (nb_sommets/nb_classes)) << endl;
            resultat = false;
        }
        if(sol[i].size() == 0){
            resultat = false;
        }
    }
    return resultat;
}


float valeur_solution(solution sol, donnees data){
    graphe gr = data.graphe;
    int sommet1;
    int sommet2;
    float valeur_sol = 0;
    for(auto it = gr.begin(); it!= gr.end(); ++it){
        arc a = *it;
        sommet1 = a.predecesseur;
        sommet2 = a.voisin;
        if(is_in_solution(sol, sommet1).second != is_in_solution(sol, sommet2).second){
            valeur_sol += a.cost;
        }
    }
    return valeur_sol;
}

void print_solution(pair<solution,float> resultat){
    solution sol = resultat.first;
    float value = resultat.second;
    int i = 1;
    for(auto it = sol.begin(); it!= sol.end(); ++it){
        vector<int> groupe = *it;
        cout << "Dans le groupe "<< i<< " se trouvent les sommets ";
        for(auto is = groupe.begin(); is!= groupe.end(); ++is){
            cout<< *is << " " ;
        }
        i +=1;
        cout << " "<< endl;
    }
    cout << " "<< endl;
    cout << "Cette solution a pour valeur " << value<< endl;
}

void print_solution(solution sol){

    int i = 1;
    for(auto it = sol.begin(); it!= sol.end(); ++it){
        vector<int> groupe = *it;
        cout << "Dans le groupe "<< i<< " se trouvent les sommets ";
        for(auto is = groupe.begin(); is!= groupe.end(); ++is){
            cout<< *is << " " ;
        }
        i +=1;
        cout << " "<< endl;
    }
    cout << " "<< endl;
    
}

void print_queue_solution(queue<solution> L){
    // cout << "debug 1 ";
    while(!(L.empty())){
        // cout << "debug" ;
        solution sol = L.front();
        L.pop();
        pair<solution,float> resultat;
        resultat.first = sol;
        resultat.second = -1;
        print_solution(resultat);
    }
}

