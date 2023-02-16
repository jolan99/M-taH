#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

struct arc {
    float cout;
};

typedef vector<unordered_map<int,arc>> graphe;



graphe init_graphe( int n){
    unordered_map<int,arc> v;            //on cree nos sommets sans arcs 
    graphe gr;
    for (int i=0 ; i<n; i++){
        gr.push_back(v);    //on ajoute la map vide à notre graphe 
    }
    return gr;
}

/*fonction permettant d'ajouter un arc a ayant pour prédécesseur le noeud p, le successeur s au graphe gr */
void add_arc (arc &a, graphe &gr, int p, int s){
          if (0<=p && p<=gr.size() && 0 <= s && s <= gr.size()){      //on vérifie que la destination et le départ de notre arc appartiennent à notre graphe 
        gr[p-1].insert({s,a});                             //on ajoute l'arc a à la liste d'arc partant de p  
    }
}

void print_arc( arc &a){
    cout << a.cout;
}

void print_unordered_map (unordered_map<int,arc> &l){
     for (auto it = l.begin(); it != l.end(); ++it){
        cout << "[" << it->first << " : ";
        print_arc(it->second);
        cout << "]";
     }
}



void print_graph (graphe &gr){
    int i = 0;
    for (auto it = gr.begin(); it!= gr.end(); ++it) {
        cout << "noeud" << i+1 << " ";
        print_unordered_map(*it);
        cout << endl;
        i = i+1;
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
                gr = init_graphe(nb_sommet);
            }
            if (compteur == 2){
                deg_min = stoi(first_word);
                deg_max = stoi(second_word);
            }
            if (compteur == 3){
                sommet1 = stoi(first_word);
                sommet2 = stoi(second_word);
                poids = stof(thirst_word);
                arc a = {poids};
                add_arc(a,gr,sommet1,sommet2);
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


int main(){
    graphe gr = read_file("data/cinqSommets.txt");
    print_graph(gr);
    return 0;
}

