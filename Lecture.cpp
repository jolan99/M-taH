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

vector<int> A, B, C; //p=3
//construire une solution initiale
void init_groups(graphe& gr){
    int n = gr.size();
    vector<int> indices(n);
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    random_shuffle(indices.begin(), indices.end());
    for (int i = 0; i < n; i++) {
        int num_A = A.size(), num_B = B.size(), num_C = C.size();
        if (num_A <= num_B && num_A <= num_C) {
            A.push_back(indices[i]+1);
        } else if (num_B <= num_A && num_B <= num_C) {
            B.push_back(indices[i]+1);
        } else {
            C.push_back(indices[i]+1);
        }
    }
}

float calc_weight(vector<int>& A, vector<int>& B, graphe& gr) {
    float total_weight = 0.0;
    for (int i = 0; i < A.size(); i++) {
        int u = A[i];
        const auto& neighbors = gr[u];
        for (const auto& [v, edge] : neighbors) { 
            if (std::find(B.begin(), B.end(), v) != B.end()) {
                total_weight += edge.cout;
            }
        }
    }
    return total_weight;
}

/*float calculateGroupWeights(const graphe& gr, const vector<int>& A, const vector<int>& B, const vector<int>& C) {
    float weightAB = 0;
    for (int i = 0; i < A.size(); i++) {
        for (auto it = gr[A[i]].begin(); it != gr[A[i]].end(); ++it) {
            int v = it->first;
            arc edge = it->second;
            if (find(B.begin(), B.end(), v) != B.end()) {
                cout << edge.cout <<endl;
                weightAB += edge.cout;
            }              
        }
            
    }

    float weightAC = 0;
    for (int i = 0; i < A.size(); i++) {
        for (auto it = gr[A[i]].begin(); it != gr[A[i]].end(); ++it) {
            int v = it->first;
            arc edge = it->second;
            if (find(C.begin(), C.end(), v) != C.end()) {
                weightAC += edge.cout;
            }              
        }
            
    }

    float weightBC = 0;
    for (int i = 0; i < B.size(); i++) {
        for (auto it = gr[B[i]].begin(); it != gr[B[i]].end(); ++it) {
            int v = it->first;
            arc edge = it->second;
            if (find(C.begin(), C.end(), v) != C.end()) {
                weightBC += edge.cout;
            }              
        }
            
    }

    return weightAB + weightAC + weightBC;
}*/

void print_solution(vector<int> A, vector<int> B, vector<int> C){
    cout << "Solution: A={";
    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << (i == A.size() - 1 ? "}" : ", ");
    }
    cout << ", B={";
    for (int i = 0; i < B.size(); i++) {
        cout << B[i] << (i == B.size() - 1 ? "}" : ", ");
    }
    cout << ", C={";
    for (int i = 0; i < C.size(); i++) {
        cout << C[i] << (i == C.size() - 1 ? "}" : ", ")<<endl;
    }
}

//voisinages:3-sweep
void enumerate_neighbors(vector<int> A, vector<int> B, vector<int> C) {
    vector<int> neighbor_A = A;
    vector<int> neighbor_B = B;
    vector<int> neighbor_C = C;
    for (int i = 0; i < A.size(); i++){
        for (int j = 0; j < B.size(); j++){
            for (int k = 0; k < C.size(); k++){
                int a = neighbor_A[i];
                neighbor_A[i] = neighbor_B[j];
                neighbor_B[j] = neighbor_C[k];
                neighbor_C[k] = a;
                print_solution(neighbor_A,neighbor_B,neighbor_C);
            }
        }
    }
}

void descente_de_gradient(graphe &gr){
    init_groups(gr);
    print_solution(A,B,C);
    enumerate_neighbors(A,B,C);
    float weight_total = calc_weight(A,B,gr);
    cout << weight_total << endl;
}

int main(){
    graphe gr = read_file("data/cinqSommets.txt");
    print_graph(gr);
    descente_de_gradient(gr);
    //float calculateGroupWeights(const graphe& gr, const vector<int>& A, const vector<int>& B, const vector<int>& C);
    return 0;
}

