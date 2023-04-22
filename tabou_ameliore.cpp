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



pair<float,float> tabou_ameliore(donnees data, int nb_classes){
    auto start = std::chrono::high_resolution_clock::now();
    // on initialise avec une solution réalisable
    pair<solution,float> sol;
    sol = init_solution3(nb_classes, data); // solution initiale

    graph gr=data.graphe;
    //on stocke la meilleure solution, initialisée par la première solution réalisable
    pair<solution,float> sBest=sol;
    
    // on crée la liste tabou : 
    queue<solution> liste_tabou;
    
    int iter = 0;
    while(iter < (data.nb_sommets)*(data.nb_sommets)){
    // while(iter < min((data.nb_sommets)*(data.nb_sommets),100)){
        iter += 1;

        // on va chercher Y tel que c'est la sol avec la meilleure fonction obj : 
        queue<solution> V = voisinage(data, sol.first, nb_classes); 
        while(!(V.empty())){
            float value_sol = valeur_solution(sol.first,data);
            solution sol_voisin = V.front();
            V.pop();
            if(!(is_in_queue(liste_tabou, sol_voisin))){ // on vérifie que la solution n'est pas dans la liste
                if(is_valid(sol_voisin,data,nb_classes) && value_sol < sBest.second){ //si la sol est mieux et valide, on la garde
                    sBest.first = sol_voisin;
                    sBest.second = value_sol;
                }
                //on ne met le bloc suivant que dans l'amélioration
                if(is_valid(sol_voisin,data,nb_classes) && value_sol > sBest.second){ // si la solution n'est pas meilleure, elle a quand même été visitée, et donc on l'ajoute à la liste tabou
                    // on veut garder une liste tabou de taille 7 : 
                    if(liste_tabou.size() == 7){
                        liste_tabou.pop();
                        liste_tabou.push(sol_voisin);
                    }
                    else{
                        liste_tabou.push(sol_voisin);
                    }
                    
                }
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
