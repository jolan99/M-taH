#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
#include "utiles.h"
#include <cmath>
using namespace std;



void print_arc(arc &a){
    cout <<"predecesseur: "<<a.predecesseur<< " voisin : " << a.voisin<<" coût : " << a.cost << endl;
}

void print_graph(graph &gr){
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
    for(int i=0; i < nb_sommets; ++i){
        if(!(is_in_solution(sol, i+1).first)){ // si un sommet n'est pas dans la solution, alors pas réalisable
            resultat = false;
        }
    }
    // respecte la condition d'équilibre 
    for(int i = 0; i< nb_classes; ++i){
        if(sol[i].size() > ceil(nb_sommets_float/nb_classes_float) + (0.01 * (nb_sommets_float/nb_classes_float)) || sol[i].size() < floor(nb_sommets_float/nb_classes_float) - (0.01 * (nb_sommets_float/nb_classes_float))){
            resultat = false;
        }
        if(sol[i].size() == 0){
            resultat = false;
        }
    }
    return resultat;
}

bool is_in_queue(queue<solution> liste_tabou, solution sol){
    /*
    Fonction permettant de savoir si un entier donné est déjà dans une liste donnée.
    */
    solution verif;
    bool isinqueue = false;
    while(!(liste_tabou.empty())){
        verif = liste_tabou.front();
        liste_tabou.pop();
        if(verif == sol){
            isinqueue = true;
            break;
        }
    }
    return isinqueue;
}

float valeur_solution(solution sol, donnees data){
    graph gr = data.graphe;
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

void print_queue_solution(queue<solution> L){
    while(!(L.empty())){
        solution sol = L.front();
        L.pop();
        pair<solution,float> resultat;
        resultat.first = sol;
        resultat.second = -1;
        print_solution(resultat);
    }
}


