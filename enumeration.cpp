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
#include <time.h>
using namespace std;



solution init_solution(int nb_classes){
    vector<int> s;  // contenu d'une classe
    solution sol;  // solution qui sera vide
    for (int i=0 ; i<nb_classes; i++){
        sol.push_back(s);    //on ajoute la classe vide à notre solution
    }
    return sol;
}



pair<float,float> enumeration(donnees data, int nb_classes){
    auto start = std::chrono::high_resolution_clock::now(); // départ de la mesure du temps
    pair<float,float> resultat;
    graphe gr=data.graphe;
    queue<solution> L; // va stocker les sous_solutions au fur et à mesure
    solution initialisation = init_solution(nb_classes);
    L.push(initialisation);
    queue<solution> S; // va stocker les solutions au fur et à mesure
    solution solution_initiale = init_solution(nb_classes);
    solution sBest; // va stocker la meilleure solution
    float best_value = std::numeric_limits< float >::infinity();
    solution s_parent;
    solution s_enfant;
    while(!(L.empty())){
        s_parent = L.front(); // on étudie une sous-solution de L 
        L.pop();
        for(auto it = gr.begin(); it!= gr.end(); ++it){ // on parcourt tous les arcs du graphe
            arc a = *it;
            int pred = a.predecesseur;
            int voisin = a.voisin;
            // les trois cas possibles : 
            // si le predecesseur n'est pas encore dans un groupe
            if(!(is_in_solution(s_parent, pred).first) && is_in_solution(s_parent, voisin).first){
                for(int i = 0; i<nb_classes; ++i){ //On crée toutes les combinaisons possibles, pred peut être dans tous les groupes possibles
                    s_enfant = s_parent;
                    s_enfant[i].push_back(pred);
                    float value_sol = valeur_solution(s_enfant,data);
                    if(is_valid(s_enfant,data,nb_classes)){
                        if(value_sol < best_value){
                            // on garde la solution ssi elle est meilleure que la sBest précédente. A la fin, 
                            // elle donnera donc la valeur optimale
                            best_value = value_sol;
                            sBest = s_enfant;
                        }
                        
                    }
                    else{L.push(s_enfant);}

                }
            }
            // si le voisin n'est pas encore dans un groupe
            if(!(is_in_solution(s_parent, voisin).first) && is_in_solution(s_parent, pred).first){
                for(int i = 0; i < nb_classes; ++i){ //On crée toutes les combinaisons possibles, pred peut être dans tous les groupes possibles
                    s_enfant = s_parent;
                    s_enfant[i].push_back(voisin);
                    float value_sol = valeur_solution(s_enfant,data);
                    if(is_valid(s_enfant,data,nb_classes)){
                        if(value_sol < best_value){
                            // on garde la solution ssi elle est meilleure que la sBest précédente. A la fin, 
                            // elle donnera donc la valeur optimale
                            best_value = value_sol;
                            sBest = s_enfant;
                        }
                        
                    }
                    else{L.push(s_enfant);}

                }
            }
            // si ni le voisin ni le predecesseur n'ont été assigné à un groupe
            if(!(is_in_solution(s_parent, pred).first) && !(is_in_solution(s_parent, voisin).first)){
                for(int a = 0; a < nb_classes; ++a){
                    s_enfant = s_parent;
                    s_enfant[a].push_back(pred);
                    solution s_enfantbis = s_enfant;
                    for(int b = 0; b < nb_classes; ++b){
                        s_enfantbis = s_enfant;
                        s_enfantbis[b].push_back(voisin);
                        float value_sol = valeur_solution(s_enfantbis,data);
                        if(is_valid(s_enfantbis,data,nb_classes)){
                            if(value_sol < best_value){
                                // on garde la solution ssi elle est meilleure que la sBest précédente. A la fin, 
                                // elle donnera donc la valeur optimale
                                best_value = value_sol;
                                sBest = s_enfantbis;
                            }
                        }
                        else{L.push(s_enfantbis);}
                    }
                }
            }

        }

    }
    auto end = std::chrono::high_resolution_clock::now(); // fin de mesure du temps.
    
    auto diff_time = std::chrono::duration<float>(end - start); // std::chrono::milliseconds

    float temps = diff_time.count(); // Retour au format float en passant par le format string.
    
    resultat.first = temps;
    resultat.second = best_value;
    return resultat;
}

