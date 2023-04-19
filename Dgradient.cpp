#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
#include "utiles.h"
#include "Lecturebis.h"
#include <chrono>
using namespace std;


queue<solution> voisinage(donnees data, solution solution_initiale, int nb_classes){
    // mouvement élémentaire : Pick and Drop
    // A partir de la solution <abd><c><ef> , le mvt élémentaire (3[2],1) donne : 
    // <abd><c><ef>  --> <abd><c><e>  --> <abdf><c><e> 

    // Il faut donc à chaque fois vérifier si la nouvelle solution obtenue est réalisable
    
    queue<solution> voisinage; // Va stocker les solutions réalisables du voisinage 
    // print_queue_solution(voisinage);
    solution sol = solution_initiale; 
    // cout << " solution initiale : " << endl;
    // print_solution(sol);
    int sommet;
    int i = 0 ; // va noter le numéro de la classe départ du sommet
    // cout << "debug 1 " << endl;
    for(int k = 0; k < nb_classes; ++k){ // parcours des classes
        // cout <<"--------------------------" << endl;
        // cout << "on parcourt la classe "<< k << endl;
        //for(int l = 0; l < sol[k].size; ++l){ 
        i = 0;
        for(auto it = sol[k].begin(); it!= sol[k].end(); ++it){ // parcours des éléments d'une classe
            // PnD : on change le sommet de classe
            sommet = *it; // on choisit le sommet qui subit le mouvement
            // cout << "on prend le sommet " << sommet << endl; 
            // std::vector<int>::iterator itr = std::find(sol[k].begin(), sol[k].end(), sommet); // on regarde où il est placé 
            
            
            for(int s = 0; s < nb_classes; ++s){ 
                sol[k].erase(sol[k].begin() +i); // on le retire de sa place 
                // cout << " on retire le sommet de la solution :" << endl;
                // print_solution(sol);
                if( s != k){
                    
                    sol[s].push_back(sommet); // on ajoute le sommet à sa nouvelle destination 
                    // cout << "nouvelle solution" << endl;
                    // print_solution(sol);
                    voisinage.push(sol);
                    
                }
                sol = solution_initiale;
            }
            i += 1;
        }
    }

    return voisinage;
}


pair<solution,float> init_solution3(int nb_classes, donnees data){
    pair<solution,float> resultat;
    int nb_sommets = data.nb_sommets;
    // création du vecteur qui nous permettra de tirer au sort une classe
    vector<int> classes(nb_classes); 
    for(int i=0;i<nb_classes;++i){
        classes[i] = i+1;
    }
    // création d'une solution vide : 
    solution sol;
    vector<int> s; 
    for (int i=0 ; i<nb_classes; i++){
        sol.push_back(s);    //on crée une solution vide
    }
    // on veut d'abord remplir les classes au minimum :
    vector<int> classes_min = classes;
    vector<int> classes_max = classes;
    int indice_classe;
    float nb_sommets_float = float(nb_sommets);
    float nb_classes_float = float(nb_classes);
    for(int i = 0; i < nb_sommets; ++i){
        // pour s'assurer que la solution est valide, on remplit d'abord au minimum les classes
        
        
        
        if(classes_min.size() != 0){
            indice_classe = rand() % classes_min.size();
            
            
            sol[classes_min[indice_classe]-1].push_back(i+1);
            
            // vérification si un groupe est assez remplit pour être valide
            if(sol[classes_min[indice_classe]-1].size()  >= floor(nb_sommets_float/nb_classes_float) - (0.01 * (nb_sommets_float/nb_classes_float))){
                classes_min.erase(classes_min.begin() + indice_classe);
            }
        }
        else{ /* Il faut s'assurer qu'on ne dépasse pas la limite de contenance d'un groupe */

            indice_classe = rand() % classes_max.size();
            sol[classes_max[indice_classe]-1].push_back(i+1);
            // vérification si un groupe est assez remplit pour être valide
            if(sol[classes_max[indice_classe]-1].size() +1 >= ceil(nb_sommets_float/nb_classes_float) + (0.01 * (nb_sommets_float/nb_classes_float))){
                classes_max.erase(classes_max.begin() + indice_classe);
            }
           
            
        }

        
    }
    resultat.first = sol;
    resultat.second = valeur_solution(sol, data);
    return resultat;
}

pair<float,float> Dgradient(donnees data, int nb_classes){
    auto start = std::chrono::high_resolution_clock::now();
    // on initialise avec une solution réalisable
    pair<solution,float> sol;
    sol = init_solution3(nb_classes, data);

    graph gr=data.graphe;
    //on stocke la meilleure solution, initialisée par la première solution réalisable
    pair<solution,float> sBest;
    sBest = sol; 
    
    bool stop = false; // critère d'arrêt

    while(!(stop)){
        queue<solution> V = voisinage(data, sol.first, nb_classes);
        while(!(V.empty())){
            float value_sol = valeur_solution(sol.first,data);
            solution voisin = V.front();
            V.pop();
            if(is_valid(voisin,data,nb_classes) && value_sol < sBest.second){
                sBest.first = voisin;
                sBest.second = value_sol;
            }
            else{
                stop = true;
                break;
            }
        }
    }



    auto end = std::chrono::high_resolution_clock::now(); // fin de mesure du temps.
    auto diff_time = std::chrono::duration<float>(end - start); // std::chrono::millisecond
    float temps = diff_time.count(); // Retour au format float en passant par le format string.
    
    pair<float,float> resultat;
    resultat.first = temps;
    resultat.second = sBest.second;

    return resultat;
}

