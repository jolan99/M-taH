#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;


// de Nico, modifiés 
struct arc {
    int predecesseur;
    int voisin;
    float cost;
};

typedef vector<arc> graphe;

/*graphe init_graphe( int n){
    unordered_map<int,arc> v;            //on cree nos sommets sans arcs 
    graphe gr;
    for (int i=0 ; i<n; i++){
        gr.push_back(v);    //on ajoute la map vide à notre graphe 
    }
    return gr;
}*/

/*fonction permettant d'ajouter un arc a ayant pour prédécesseur le noeud p, le successeur s au graphe gr */
void add_arc (arc &a, graphe &gr){  
        gr.push_back(a);   //on ajoute l'arc a à la liste d'arc =
}


void print_arc(arc &a){
    cout <<"predecesseur: "<<a.predecesseur<< " voisin : " << a.voisin<<" coût : " << a.cost << endl;
}

// void print_unordered_map (unordered_map<int,arc> &l){
//      for (auto it = l.begin(); it != l.end(); ++it){
//         cout << "[" << it->first << " : ";
//         print_arc(it->second);
//         cout << "]";
//      }
// }

void print_graph(graphe &gr){
    int i = 0;
    for (auto it = gr.begin(); it!= gr.end(); ++it) {
        print_arc(*it);
    }
}


graphe read_file (string str){
    ifstream file (str);
    int nb_sommet;
    int nb_arrete;
    int deg_min;
    int deg_max;  //ouverture fichier en mode lecture
    graphe gr;
    if (file){
        int compteur = 0;
        string thirst_word;
        string second_word;
        string first_word;
        string ligne;
        int sommet1;
        int sommet2;
        float poids;
        unordered_map <int,int> degre;
        int sommet;
        int deg;
        while(getline(file, ligne)){ //Tant qu'on n'est pas à la fin, on lit
            first_word = ligne[0];
            second_word = ligne[2];
            thirst_word = ligne[4];
            if (first_word == "#"){
                compteur += 1;
                continue;
            }
            if (compteur == 1){
                nb_sommet = stoi(first_word);
                nb_arrete = stoi(second_word);
                //gr = init_graphe(nb_sommet);
            }
            if (compteur == 2){
                deg_min = stoi(first_word);
                deg_max = stoi(second_word);
            }
            if (compteur == 3){
                sommet1 = stoi(first_word);
                sommet2 = stoi(second_word);
                poids = stof(thirst_word);
                arc a = {sommet1,sommet2,poids};
                add_arc(a,gr);
            }
            if (compteur == 4){
                sommet = stoi(first_word);
                deg = stoi(second_word);
                degre.emplace(sommet,deg);
            }
        }
        
        return gr;  
    }
    else{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture."  << endl;
    }
    return gr;
}

// de moi : 
typedef vector<vector<int>> solution;

solution init_solution(int nb_classes){
    vector<int> s;  // contenu d'une classe
    solution sol;  // solution qui sera vide
    for (int i=0 ; i<nb_classes; i++){
        sol.push_back(s);    //on ajoute la classe vide à notre solution
    }
    return sol;
}




solution enumeration(graphe gr, int nb_classes){
    queue<solution> L; // va stocker les sous_solutions au fur et à mesure
    queue<solution> S; // va stocker les solutions au fur et à mesure
    // la queue S au dessus est-elle vraiment necessaire? ça prend de la place, et
    // on ne veut que la solution optimale à la fin 
    solution solution_initiale = init_solution(nb_classes);
    solution sBest; // va stocker la meilleure solution
    while(!(L.empty())){
        solution s_parent = L.front(); // on étudie une sous-solution de L 
        for(auto it = gr.begin(); it!= gr.end(); ++it){ // on parcourt tous les arcs du graphe
        arc a= *it;
        int pred = a.predecesseur;
        int voisin = a.voisin;
        

        }

    }
    return sBest;
}



int main(){
    graphe gr = read_file("data/cinqSommets.txt");
    print_graph(gr);
    return 0;
}
