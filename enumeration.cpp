#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
using namespace std;


// de Nico, modifiés 
struct arc {
    int predecesseur;
    int voisin;
    float cost;
};

typedef vector<arc> graphe;

struct donnees {
    graphe graphe;
    int nb_sommets;
};


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


donnees read_file (string str){
    donnees data;
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
                data.nb_sommets = stoi(first_word);
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
        
        //return gr;  
    }
    else{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture."  << endl;
    }
    data.graphe = gr;
    
    return data;
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


pair<bool,int> is_in_group(solution sol, int sommet){ // regarde si un sommet est déjà dans mis dans un groupe et lequel
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
    
    //graphe gr = data.graphe;
    // tous les  sommets sont dans la solution
    //vector<bool> condition1(false,nb_sommets);
    for(int i=0; i < nb_sommets; ++i){
        if(!(is_in_group(sol, i+1).first)){ // si un sommet n'est pas dans la solution, alors pas réalisable
            resultat = false;
        }
    }
    // respecte la condition d'équilibre 
    for(int i = 0; i< nb_classes; ++i){
        if(sol[i].size() >= 4){
            resultat = false;
        }
    }
    return resultat;
}

float valeur(solution sol, donnees data){
    graphe gr = data.graphe;
    int sommet1;
    int sommet2;
    float valeur_sol = 0;
    for(auto it = gr.begin(); it!= gr.end(); ++it){
        arc a = *it;
        sommet1 = a.predecesseur;
        sommet2 = a.voisin;
        if(is_in_group(sol, sommet1).second != is_in_group(sol, sommet2).second){
            valeur_sol += a.cost;
        }
    }
    return valeur_sol;
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
    cout << " Cette solution a pour valeur " << value<< endl;
}


pair<solution,float> enumeration(donnees data, int nb_classes){
    pair<solution,float> resultat;
    graphe gr=data.graphe;
    queue<solution> L; // va stocker les sous_solutions au fur et à mesure
    solution initialisation = init_solution(nb_classes);
    L.push(initialisation);
    queue<solution> S; // va stocker les solutions au fur et à mesure
    // la queue S au dessus est-elle vraiment necessaire? ça prend de la place, et
    // on ne veut que la solution optimale à la fin 
    solution solution_initiale = init_solution(nb_classes);
    solution sBest; // va stocker la meilleure solution
    float best_value = std::numeric_limits< float >::infinity();
    solution s_parent;
    solution s_enfant;
    while(!(L.empty())){
        // cout<< "debeug1 " << endl;
        s_parent = L.front(); // on étudie une sous-solution de L 
        // cout << "##################"<< endl;
        // cout <<"solution parent : "<< endl;
        // print_solution(s_parent);
        // cout << "##################"<< endl;
        
        L.pop();
        for(auto it = gr.begin(); it!= gr.end(); ++it){ // on parcourt tous les arcs du graphe
            arc a = *it;
            // cout << "-----------------------"<< endl;
            // cout<< "on étudie l'arc " ;
            // print_arc(a);
            int pred = a.predecesseur;
            int voisin = a.voisin;
            // les trois cas possibles : 
            // si le predecesseur n'est pas encore dans un groupe
            if(!(is_in_group(s_parent, pred).first) && is_in_group(s_parent, voisin).first){
                //cout << "cas 1 " << endl;
                for(int i = 0; i<nb_classes; ++i){ //On crée toutes les combinaisons possibles, pred peut être dans tous les groupes possibles
                    s_enfant = s_parent;
                    s_enfant[i].push_back(pred);
                    // cout << "solution enfant : "<< endl;
                    // print_solution(s_enfant);
                    float value_sol = valeur(s_enfant,data);
                    if(is_valid(s_enfant,data,nb_classes)){
                        if(value_sol < best_value){
                            // on garde la solution ssi elle est meilleure que la sBest précédente. A la fin, 
                            // elle donnera donc la valeur optimale
                            best_value = value_sol;
                            sBest = s_enfant;
                        }
                        
                    }
                    else{L.push(s_enfant);}

                }
            }
            // si le voisin n'est pas encore dans un groupe
            if(!(is_in_group(s_parent, voisin).first) && is_in_group(s_parent, pred).first){
                // cout << "cas 2 " << endl;
                for(int i = 0; i < nb_classes; ++i){ //On crée toutes les combinaisons possibles, pred peut être dans tous les groupes possibles
                    s_enfant = s_parent;
                    s_enfant[i].push_back(voisin);
                    // cout << "solution enfant : "<< endl;
                    // print_solution(s_enfant);
                    float value_sol = valeur(s_enfant,data);
                    if(is_valid(s_enfant,data,nb_classes)){
                        if(value_sol < best_value){
                            // on garde la solution ssi elle est meilleure que la sBest précédente. A la fin, 
                            // elle donnera donc la valeur optimale
                            best_value = value_sol;
                            sBest = s_enfant;
                        }
                        
                    }
                    else{L.push(s_enfant);}

                }
            }
            // si ni le voisin ni le predecesseur n'ont été assigné à un groupe
            if(!(is_in_group(s_parent, pred).first) && !(is_in_group(s_parent, voisin).first)){
                // cout << "cas 3 " << endl;
                for(int a = 0; a < nb_classes; ++a){
                    s_enfant = s_parent;
                    s_enfant[a].push_back(pred);
                    solution s_enfantbis = s_enfant;
                    for(int b = 0; b < nb_classes; ++b){
                        s_enfantbis = s_enfant;
                        s_enfantbis[b].push_back(voisin);
                        // cout << "solution enfant : ";
                        // print_solution(s_enfantbis);
                        float value_sol = valeur(s_enfantbis,data);
                        if(is_valid(s_enfantbis,data,nb_classes)){
                            if(value_sol < best_value){
                                // on garde la solution ssi elle est meilleure que la sBest précédente. A la fin, 
                                // elle donnera donc la valeur optimale
                                best_value = value_sol;
                                sBest = s_enfantbis;
                            }
                        }
                        else{L.push(s_enfantbis);}
                    }
                }
            }

        }

    }
    resultat.first = sBest;
    resultat.second = best_value;
    return resultat;
}



int main(){
    donnees data = read_file("data/cinqSommets.txt");
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
    // //cout << "valeur solution : " << valeur(sol, data);
    print_solution(enumeration(data,4));
    
    return 0;
}
