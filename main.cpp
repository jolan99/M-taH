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
#include "tabou.h"
#include "tabou_ameliore.h"
#include <chrono>
#include <filesystem>
#include <string>  
using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

namespace fs = std::filesystem;



int main() {
    // cout << "Les résultats s'impriment dans le fichier \"test5groupes.txt\"" << endl;
    // cout << endl;
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
    //     fichier << "Valeurs optimales moyennes après "<<nb_essais <<" essais : " <<endl;
        
    //     fichier <<"                       Enumération            Enumération bis            Descente de gradient   " << endl;
    //     fichier <<"                       valeur_obj   temps     valeur_obj   temps         valeur_obj   temps" << endl;
    //     for (const auto& entry : fs::directory_iterator(current_dir)) {
    //         moyenne_enum = 0;
    //         moyenne_enumbis = 0;
    //         moyenne_gradient = 0;
    //         if (entry.is_regular_file() && entry.path().extension() == ".txt") {
    //             fichier << entry.path().filename().string() ; // Afficher le nom du fichier
                
    //             cout << "Etude du fichier  : "<< entry.path().filename().string() << endl;
    //             donnees data = read_file("data/" + entry.path().filename().string());
    //             if(entry.path().filename().string() == "quatreSommets.txt" || entry.path().filename().string() == "cinqSommets.txt" ){
    //                     cout << " Méthode de l'énumeration en cours ..." << endl;
    //                     sol_enum= enumeration(data,nb_classes);
    //                     cout << " Méthode de l'énumeration améliorée en cours ..." << endl;
    //                     sol_enumbis= enumerationbis(data,nb_classes);
    //                     moyenne_enum = sol_enum.second;
    //                     moyenne_enumbis = sol_enumbis.second;
    //                     tempsmoy_enum = sol_enum.first;
    //                     tempsmoy_enumbis = sol_enumbis.first;
    //                 }
    //             for(int r= 0; r< nb_essais; ++r){
                    
    //                 cout << " Méthode de descente du gradient en cours ..." << endl;
    //                 sol_gradient = Dgradient(data,nb_classes);
                    
    //                 moyenne_gradient += sol_gradient.second;
    //                 tempsmoy_gradient += sol_gradient.first;
    //             }
    //             // fichier << "Valeur optimale moyenne après "<<nb_essais <<" essais : " <<endl;
    //             if(moyenne_enum != 0){
    //                 // fichier <<"                       valeur_obj   temps     valeur_obj   temps         valeur_obj   temps" << endl;
    //                 fichier <<"                      "<<moyenne_enum <<"  " <<tempsmoy_enum<< " s.    "<<  moyenne_enumbis<< " " << tempsmoy_enumbis<< " s."<< endl;
    //                 // fichier<< "Méthode d'énumération explicite : " <<  moyenne_enum  << "  et temps  : " <<tempsmoy_enum  << " s."<< endl;
    //                 // fichier<< "Méthode d'énumération améliorée : " <<  moyenne_enumbis<< "  et temps  : " << tempsmoy_enumbis<< " s."<<endl;
    //             }
    //             // fichier <<"                       valeur_obj   temps     valeur_obj   temps         valeur_obj   temps" << endl;
    //             fichier <<"                                                       "<<moyenne_gradient/nb_essais <<"  " <<tempsmoy_gradient/nb_essais << " s."<< endl;
    //             // fichier<< "Méthode de la descente de gradient : " <<  moyenne_gradient/nb_essais <<"  et temps moyen : " <<tempsmoy_gradient/nb_essais << " s."<< endl;
    //             fichier << "\n" << endl;
                
    //         }
    //     }
    //     fichier.close();
    // }
    // else{
    //     cout << "erreur à l'ouverture!" << endl;
    // }
    // // cout << "La compilation a fonctionné" << endl;
    int nb_classes = 4;
    pair<float,float> sol_tabou;
    donnees data = read_file("data/dixSommets.txt");
    sol_tabou = tabou(data, nb_classes);
    cout << "data/dixSommets.txt" << endl;
    cout << " la sol du tabou est : " << sol_tabou.second << " en " << sol_tabou.first<< " s." << endl;
    sol_tabou = tabou_ameliore(data, nb_classes);
    cout << " la sol du tabou amélioré est : " << sol_tabou.second << " en " << sol_tabou.first<< " s." << endl;
    data = read_file("data/cinqSommets.txt");
    cout << "data/cinqSommets.txt" << endl;
    sol_tabou = tabou(data, nb_classes);
    cout << " la sol du tabou est : " << sol_tabou.second << " en " << sol_tabou.first<< " s." << endl;
    sol_tabou = tabou_ameliore(data, nb_classes);
    cout << " la sol du tabou amélioré est : " << sol_tabou.second << " en " << sol_tabou.first<< " s." << endl;
    data = read_file("data/trenteSommets.txt");
    cout << "data/trenteSommets.txt" << endl;
    sol_tabou = tabou(data, nb_classes);
    cout << " la sol du tabou est : " << sol_tabou.second << " en " << sol_tabou.first<< " s." << endl;
    sol_tabou = tabou_ameliore(data, nb_classes);
    cout << " la sol du tabou amélioré est : " << sol_tabou.second << " en " << sol_tabou.first<< " s." << endl;
    data = read_file("data/quinzeSommets.txt");
    cout << "data/quinzeSommets.txt" << endl;
    sol_tabou = tabou(data, nb_classes);
    cout << " la sol du tabou est : " << sol_tabou.second << " en " << sol_tabou.first<< " s." << endl;
    sol_tabou = tabou_ameliore(data, nb_classes);
    cout << " la sol du tabou amélioré est : " << sol_tabou.second << " en " << sol_tabou.first<< " s." << endl;
    return 0;

}

