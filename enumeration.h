#ifndef enumeration_h
#define enumeration_h

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
using namespace std;

solution init_solution(int nb_classes);
pair<float,float> enumeration(donnees data, int nb_classes);
#endif

