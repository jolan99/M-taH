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
    ofstream fichier("test.txt", ios::out | ios::trunc);
    if(fichier){
        fs::path current_dir = "data/"; // Chemin absolu du répertoire courant
        pair<solution,float> sol;
        int nb_classes = 3;
        float moyenne ;
        for (const auto& entry : fs::directory_iterator(current_dir)) {
            moyenne = 0;
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                fichier << entry.path().filename().string() << std::endl; // Afficher le nom du fichier
                for(int r= 0; r< 1000; ++r){
                    donnees data = read_file("data/" + entry.path().filename().string());
                    sol= Dgradient(data,nb_classes);
                    //print_solution(sol);
                    moyenne += sol.second;
                }
                fichier << " valeur optimale moyenne après 1000 essais : " << moyenne/1000 << endl;
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