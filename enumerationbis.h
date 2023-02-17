#ifndef enumerationbis_h
#define enumerationbis_h

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include<limits>
#include "utiles.h"
#include "Lecturebis.h"
using namespace std;

queue<solution> init_solutionbis(int nb_classes, donnees data);
pair<solution,float> enumerationbis(donnees data, int nb_classes);
#endif