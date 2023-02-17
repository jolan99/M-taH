#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
#include "utiles.h"
#include "Lecturebis.h"
#include "enumeration.h"
#include "enumerationbis.h"
using namespace std;


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
    print_solution(enumerationbis(data,4));
    //queue<solution> L = init_solution(4,data);
    //cout << "coucou";
    return 0;
}