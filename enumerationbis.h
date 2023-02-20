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
#include <chrono>
#include <sstream>
using namespace std;

queue<solution> init_solutionbis(int nb_classes, donnees data);
pair<float,float> enumerationbis(donnees data, int nb_classes);
#endif