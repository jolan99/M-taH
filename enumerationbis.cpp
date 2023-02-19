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



queue<solution> init_solutionbis(int nb_classes, donnees data){
    graphe gr = data.graphe;
    queue<solution> L; // solutions initiales
    solution solution_vide;
    solution s1;
    solution s2;
    vector<int> s;  // contenu d'un groupe vide
    // solution sol;  // solution qui contiendra les deux premiers sommets
    for (int i=0 ; i<nb_classes; i++){
        solution_vide.push_back(s);    //on crée une solution vide
    }
    
    
    for(auto it = gr.begin(); it!= gr.end(); ++it){
        s1 = solution_vide;
        s2 = solution_vide;
        arc a = *it;
        s1[0].push_back(a.predecesseur);
        s1[1].push_back(a.voisin);
        L.push(s1);
        s2[0].push_back(a.predecesseur);
        s2[0].push_back(a.voisin);
        L.push(s2);
    }

    return L;
}


pair<solution,float> enumerationbis(donnees data, int nb_classes){
    auto start = std::chrono::high_resolution_clock::now(); // départ de la mesure du temps
    pair<solution,float> resultat;
    graphe gr=data.graphe;
    queue<solution> L = init_solutionbis(nb_classes,data); // va stocker les sous_solutions au fur et à mesure
    queue<solution> S; // va stocker les solutions au fur et à mesure
    // la queue S au dessus est-elle vraiment necessaire? ça prend de la place, et
    // on ne veut que la solution optimale à la fin 
    
    solution sBest; // va stocker la meilleure solution
    float best_value = std::numeric_limits< float >::infinity();
    solution s_parent;
    solution s_enfant;
    while(!(L.empty())){
        // cout<< "debeug1 " << endl;
        s_parent = L.front(); // on étudie une sous-solution de L 
        // cout << "##################"<< endl;
        // cout <<"solution parent : "<< endl;
        // print_solution(s_parent);
        // cout << "##################"<< endl;
        
        L.pop();
        for(auto it = gr.begin(); it!= gr.end(); ++it){ // on parcourt tous les arcs du graphe
            arc a = *it;
            // cout << "-----------------------"<< endl;
            // cout<< "on étudie l'arc " ;
            // print_arc(a);
            int pred = a.predecesseur;
            int voisin = a.voisin;
            // les trois cas possibles : 
            // si le predecesseur n'est pas encore dans un groupe
            if(!(is_in_solution(s_parent, pred).first) && is_in_solution(s_parent, voisin).first){
                //cout << "cas 1 " << endl;
                for(int i = 0; i<nb_classes; ++i){ //On crée toutes les combinaisons possibles, pred peut être dans tous les groupes possibles
                    s_enfant = s_parent;
                    s_enfant[i].push_back(pred);
                    // cout << "solution enfant : "<< endl;
                    // print_solution(s_enfant);
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
                // cout << "cas 2 " << endl;
                for(int i = 0; i < nb_classes; ++i){ //On crée toutes les combinaisons possibles, pred peut être dans tous les groupes possibles
                    s_enfant = s_parent;
                    s_enfant[i].push_back(voisin);
                    // cout << "solution enfant : "<< endl;
                    // print_solution(s_enfant);
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
                // cout << "cas 3 " << endl;
                for(int a = 0; a < nb_classes; ++a){
                    s_enfant = s_parent;
                    s_enfant[a].push_back(pred);
                    solution s_enfantbis = s_enfant;
                    for(int b = 0; b < nb_classes; ++b){
                        s_enfantbis = s_enfant;
                        s_enfantbis[b].push_back(voisin);
                        // cout << "solution enfant : ";
                        // print_solution(s_enfantbis);
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
    cout << "Temps : là" << temps << " s " << endl;
    resultat.first = sBest;
    resultat.second = best_value;
    return resultat;
}
