#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
#include "utiles.h"
#include "Lecturebis.h"
using namespace std;



void add_arc (arc &a, graph &gr){  
        gr.push_back(a);   //on ajoute l'arc a à la liste d'arc =
}


// donnees read_file (string str){
//     donnees data;
//     ifstream file (str);
//     int nb_sommet;
//     int nb_arrete;
//     int deg_min;
//     int deg_max;  //ouverture fichier en mode lecture
//     graphegr;
//     if (file){
//         int compteur = 0;
//         string thirst_word;
//         string second_word;
//         string first_word;
//         string ligne;
//         int sommet1;
//         int sommet2;
//         float poids;
//         unordered_map <int,int> degre;
//         int sommet;
//         int deg;
//         while(getline(file, ligne)){ //Tant qu'on n'est pas à la fin, on lit
//             first_word = ligne[0];
//             second_word = ligne[2];
//             thirst_word = ligne[4];
//             if (first_word == "#"){
//                 compteur += 1;
//                 continue;
//             }
//             if (compteur == 1){
//                 data.nb_sommets = stoi(first_word);
//                 nb_arrete = stoi(second_word);
//                 //gr = init_graphe(nb_sommet);
//             }
//             if (compteur == 2){
//                 deg_min = stoi(first_word);
//                 deg_max = stoi(second_word);
//             }
//             if (compteur == 3){
//                 sommet1 = stoi(first_word);
//                 sommet2 = stoi(second_word);
//                 poids = stof(thirst_word);
//                 arc a = {sommet1,sommet2,poids};
//                 add_arc(a,gr);
//             }
//             if (compteur == 4){
//                 sommet = stoi(first_word);
//                 deg = stoi(second_word);
//                 degre.emplace(sommet,deg);
//             }
//         }
        
//         //return gr;  
//     }
//     else{
//     cout << "ERREUR: Impossible d'ouvrir le fichier en lecture."  << endl;
//     }
//     data.graphe = gr;
    
//     return data;
// }

donnees read_file (string str){
    donnees data;
    ifstream file (str);
    int nb_sommet;
    int nb_arrete;
    int deg_min;
    int deg_max;  //ouverture fichier en mode lecture
    graph gr;
    if (file){
        int compteur = 0;
        // string thirst_word;
        // string second_word;
        // string first_word;
        string ligne;
        int sommet1;
        int sommet2;
        float poids;
        unordered_map <int,int> degre;
        int sommet;
        int deg;
        string info;
        while(getline(file, ligne)){ //Tant qu'on n'est pas à la fin, on lit
            istringstream stream_line{ ligne };
            stream_line >> info;
            // first_word = ligne[0];
            // second_word = ligne[2];
            // thirst_word = ligne[4];
            if (info == "#"){
                compteur += 1;
                continue;
            }
            if (compteur == 1){
                data.nb_sommets = atoi(info.c_str());
                stream_line >> nb_arrete;
                // data.nb_sommets = stoi(first_word);
                // nb_arrete = stoi(second_word);
                
            }
            if (compteur == 2){
                deg_min = atoi(info.c_str());
                stream_line  >> deg_max;
                // deg_min = stoi(first_word);
                // deg_max = stoi(second_word);
            }
            if (compteur == 3){
                sommet1 = atoi(info.c_str());
                stream_line >> sommet2 >> poids;
                // sommet1 = stoi(first_word);
                // sommet2 = stoi(second_word);
                // poids = stof(thirst_word);
                arc a = {sommet1,sommet2,poids};
                add_arc(a,gr);
            }
            if (compteur == 4){
                sommet = atoi(info.c_str());
                stream_line >> deg ;
                // sommet = stoi(first_word);
                // deg = stoi(second_word);
                degre.emplace(sommet,deg);
            }
        }
        
        //return gr;  
    }
    else{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture."  << endl;
    }
    data.graphe = gr;
    
    return data;
}