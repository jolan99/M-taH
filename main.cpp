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
#include "enumeration.h"
#include "enumerationbis.h"
#include "Dgradient.h"
#include <chrono>
#include <filesystem>
#include <string>  
using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

namespace fs = std::filesystem;



int main() {
    // ofstream fichier("test5groupes.txt", ios::out | ios::trunc);
    // if(fichier){
    //     fs::path current_dir = "data/"; // Chemin absolu du répertoire courant
    //     pair<float,float> sol_enum;
    //     pair<float,float> sol_enumbis;
    //     pair<float,float> sol_gradient;
    //     int nb_classes = 5;
    //     float moyenne_enum ;
    //     float moyenne_enumbis ;
    //     float moyenne_gradient ;
    //     float tempsmoy_enum ;
    //     float tempsmoy_enumbis ;
    //     float tempsmoy_gradient ;
    //     int nb_essais = 1;
    //     for (const auto& entry : fs::directory_iterator(current_dir)) {
    //         moyenne_enum = 0;
    //         moyenne_enumbis = 0;
    //         moyenne_gradient = 0;
    //         if (entry.is_regular_file() && entry.path().extension() == ".txt") {
    //             fichier << entry.path().filename().string() << std::endl; // Afficher le nom du fichier
    //             donnees data = read_file("data/" + entry.path().filename().string());
    //             if(entry.path().filename().string() == "quatreSommets.txt" || entry.path().filename().string() == "cinqSommets.txt" ){
    //                     sol_enum= enumeration(data,nb_classes);
    //                     sol_enumbis= enumerationbis(data,nb_classes);
    //                     moyenne_enum = sol_enum.second;
    //                     moyenne_enumbis = sol_enumbis.second;
    //                     tempsmoy_enum = sol_enum.first;
    //                     tempsmoy_enumbis = sol_enumbis.first;
    //                 }
    //             for(int r= 0; r< nb_essais; ++r){
                    
                    
    //                 sol_gradient = Dgradient(data,nb_classes);
                    
    //                 moyenne_gradient += sol_gradient.second;
    //                 tempsmoy_gradient += sol_gradient.first;
    //             }
    //             fichier << "Valeur optimale moyenne après "<<nb_essais <<" essais : " <<endl;
    //             if(moyenne_enum != 0){
    //                 fichier<< "Méthode d'énumération explicite : " <<  moyenne_enum  << "  et temps  : " <<tempsmoy_enum  << " s."<< endl;
    //                 fichier<< "Méthode d'énumération améliorée : " <<  moyenne_enumbis<< "  et temps  : " << tempsmoy_enumbis<< " s."<<endl;
    //             }
                
    //             fichier<< "Méthode de la descente de gradient : " <<  moyenne_gradient/nb_essais <<"  et temps moyen : " <<tempsmoy_gradient/nb_essais << " s."<< endl;
    //             fichier << "\n" << endl;
                
    //         }
    //     }
    //     fichier.close();
    // }
    // else{
    //     cout << "erreur à l'ouverture!" << endl;
    // }
    cout << "coucou" << endl;
    return 0;
}

