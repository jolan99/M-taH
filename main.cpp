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



///////////////// Enumération et Enumération bis //////////////

// int main(){
//     donnees data = read_file("data/quatreSommets.txt");
//     pair<solution,float> sol;
//     cout << "Instance : quatreSommets.txt" << endl;
//     cout << "Algorithme d'énumération "<< endl;
//     sol = enumeration(data,3);
//     print_solution(sol);
//     cout << "Algotithme d'énumération bis " << endl;
//     sol = enumerationbis(data,3);
//     print_solution(sol);
//     cout << "############################"<< endl;

//     data = read_file("data/dixSommets.txt");
//     cout << "Instance : dixSommets.txt" << endl;
//     cout << "Algorithme d'énumération "<< endl;
//     sol = enumeration(data,3);
//     print_solution(sol);
//     cout << "Algotithme d'énumération bis " << endl;
//     sol = enumerationbis(data,3);
//     print_solution(sol);
//     cout << "############################"<< endl;

//     data = read_file("data/quinzeSommets.txt");
//     cout << "Instance : quinzeSommets.txt" << endl;
//     cout << "Algorithme d'énumération "<< endl;
//     sol = enumeration(data,3);
//     print_solution(sol);
//     cout << "Algotithme d'énumération bis " << endl;
//     sol = enumerationbis(data,3);
//     print_solution(sol);
//     cout << "############################"<< endl;
//     return 0;
// }

namespace fs = std::filesystem;
/////////////////// Boucle sur les fichiers //////////////////


// int main() {
//     fs::path current_dir = "data/"; // Chemin absolu du répertoire courant
//     for (const auto& entry : fs::directory_iterator(current_dir)) {
//         if (entry.is_regular_file() && entry.path().extension() == ".txt") {
//             std::cout << entry.path().filename().string() << std::endl; // Afficher le nom du fichier
//             if(entry.path().filename().string() != "centSommets.txt"  && entry.path().filename().string() != "cinqCentSommets.txt" && entry.path().filename().string() != "cinquanteSommets.txt"  && entry.path().filename().string() != "milleSommets.txt"){
//                 donnees data = read_file("data/" + entry.path().filename().string());
//                 print_solution(enumeration(data,3));
//                 print_solution(enumerationbis(data,3));
//             }
            
//         }
//     }
//     return 0;
// }


////////////////// Descente de gradient //////////////////////


int main() {
    ofstream fichier("test5groupes.txt", ios::out | ios::trunc);
    if(fichier){
        fs::path current_dir = "data/"; // Chemin absolu du répertoire courant
        pair<float,float> sol_enum;
        pair<float,float> sol_enumbis;
        pair<float,float> sol_gradient;
        int nb_classes = 5;
        float moyenne_enum ;
        float moyenne_enumbis ;
        float moyenne_gradient ;
        float tempsmoy_enum ;
        float tempsmoy_enumbis ;
        float tempsmoy_gradient ;
        int nb_essais = 1000;
        for (const auto& entry : fs::directory_iterator(current_dir)) {
            moyenne_enum = 0;
            moyenne_enumbis = 0;
            moyenne_gradient = 0;
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                fichier << entry.path().filename().string() << std::endl; // Afficher le nom du fichier
                donnees data = read_file("data/" + entry.path().filename().string());
                if(entry.path().filename().string() == "quatreSommets.txt" || entry.path().filename().string() == "cinqSommets.txt" ){
                        sol_enum= enumeration(data,nb_classes);
                        sol_enumbis= enumerationbis(data,nb_classes);
                        moyenne_enum = sol_enum.second;
                        moyenne_enumbis = sol_enumbis.second;
                        tempsmoy_enum = sol_enum.first;
                        tempsmoy_enumbis = sol_enumbis.first;
                    }
                for(int r= 0; r< nb_essais; ++r){
                    
                    
                    sol_gradient = Dgradient(data,nb_classes);
                    
                    moyenne_gradient += sol_gradient.second;
                    tempsmoy_gradient += sol_gradient.first;
                }
                fichier << "Valeur optimale moyenne après "<<nb_essais <<" essais : " <<endl;
                if(moyenne_enum != 0){
                    fichier<< "Méthode d'énumération explicite : " <<  moyenne_enum  << "  et temps  : " <<tempsmoy_enum  << " s."<< endl;
                    fichier<< "Méthode d'énumération améliorée : " <<  moyenne_enumbis<< "  et temps  : " << tempsmoy_enumbis<< " s."<<endl;
                }
                
                fichier<< "Méthode de la descente de gradient : " <<  moyenne_gradient/nb_essais <<"  et temps moyen : " <<tempsmoy_gradient/nb_essais << " s."<< endl;
                fichier << "\n" << endl;
                
            }
        }
        fichier.close();
    }
    else{
        cout << "erreur à l'ouverture!" << endl;
    }
    return 0;
}