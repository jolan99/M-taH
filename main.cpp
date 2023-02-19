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
#include <chrono>
#include <filesystem>
#include <string>  
using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;


pair<float,pair<solution,float>> temps_execution(string file, int nb_classes){    
    pair<float, pair<solution,float>> res;
    donnees data = read_file(file); // On initialise le graphe.
    print_graph(data.graphe);
    auto start = std::chrono::high_resolution_clock::now(); // départ de la mesure du temps
    
    pair<solution,float> sol = enumerationbis(data,nb_classes);

    auto end = std::chrono::high_resolution_clock::now(); // fin de mesure du temps.
    
    auto diff_time = std::chrono::duration<float>(end - start); // std::chrono::milliseconds

    res.first = diff_time.count(); // Retour au format float en passant par le format string.
    res.second = sol;

    return(res); 
}




int main(){
    
    //print_graph(gr);
    //solution sol={{1,2},{3,4}};
    // cout << is_in_group(sol, 7).first << endl;
    // donnees data;
    // graphe gr;
    // arc a = {1,2,30};
    // add_arc(a,gr);
    // arc b = {1,3,10};
    // add_arc(b,gr);
    // arc c = {3,4,5};
    // add_arc(c,gr);
    // data.graphe = gr;
    // data.nb_sommets = 4;
    //cout << "valeur solution : " << valeur(sol, data);
    //print_solution(enumeration(data,3));
    //print_solution(enumerationbis(data,3));
    // pair<float,pair<solution,float>> res = temps_execution("data/cinqSommets.txt", 3);
    donnees data = read_file("data/cinqSommets.txt");
    pair<solution,float> sol;
    cout << "Instance : cinqSommets.txt" << endl;
    cout << "Algorithme d'énumération "<< endl;
    sol = enumeration(data,3);
    print_solution(sol);
    cout << "Algotithme d'énumération bis " << endl;
    sol = enumerationbis(data,3);
    print_solution(sol);
    cout << "############################"<< endl;

    data = read_file("data/quatreSommets.txt");
    cout << "Instance : cinqSommets.txt" << endl;
    cout << "Algorithme d'énumération "<< endl;
    sol = enumeration(data,3);
    print_solution(sol);
    cout << "Algotithme d'énumération bis " << endl;
    sol = enumerationbis(data,3);
    print_solution(sol);
    cout << "############################"<< endl;

    data = read_file("data/dixSommets.txt");
    cout << "Instance : cinqSommets.txt" << endl;
    cout << "Algorithme d'énumération "<< endl;
    sol = enumeration(data,3);
    print_solution(sol);
    cout << "Algotithme d'énumération bis " << endl;
    sol = enumerationbis(data,3);
    print_solution(sol);
    cout << "############################"<< endl;

    data = read_file("data/quinzeSommets.txt");
    cout << "Instance : cinqSommets.txt" << endl;
    cout << "Algorithme d'énumération "<< endl;
    sol = enumeration(data,3);
    print_solution(sol);
    cout << "Algotithme d'énumération bis " << endl;
    sol = enumerationbis(data,3);
    print_solution(sol);
    cout << "############################"<< endl;
    //queue<solution> L = init_solution(4,data);
    //cout << "coucou";
    

    // for (const auto& dirEntry : recursive_directory_iterator("data/"))
    //  std::cout << dirEntry << std::endl;
    return 0;
}

namespace fs = std::filesystem;

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