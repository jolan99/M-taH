#ifndef D_gradient 
#define D_gradient

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
#include "utiles.h"
#include "Lecturebis.h"
#include <chrono>
using namespace std;


pair<solution,float> init_solution3(int nb_classes, donnees data);
queue<solution> voisinage(donnees data, solution solution_initiale, int nb_classes);
pair<float,float> Dgradient(donnees data, int nb_classes);
#endif 