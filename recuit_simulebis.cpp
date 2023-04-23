#include "utiles.h"
#include "Lecturebis.h"
#include "recuit_simule.h"
// #include "Dgradient.h"
#include <time.h>
#include <queue>
using namespace std;

pair<float,float> recuit_simule(donnees data, int nb_classes){
    float time_spent = 0.0;
    clock_t begin = clock();
    pair<solution,float> X = init_solution3(nb_classes, data);
    pair<solution,float> Xbest = X;
    pair<solution,float> X1;
    bool valid = false;
    float temp = 1000;
    float t = 0;
    while (temp > 0.1){
        while (t<data.nb_sommets*data.nb_sommets){
            queue<solution> voisin = voisinage(data, X.first, nb_classes);
            while (valid !=true){
                X1.first = voisin.front();
                X1.second = valeur_solution(voisin.front(),data);
                valid = is_valid(X1.first,data, nb_classes);
                voisin.pop();
            }
            float delta = (X1.second - X.second);
            if (delta<0){
                X = X1;
                if (X1.second < Xbest.second){
                    Xbest = X1;
                }
            }
            else{
                float p = ((float) rand() / (RAND_MAX));
                if (p <= exp(-(delta/temp))){
                    X = X1;
                }
            }
            t = t+1;            
        }
        temp = 0.9 * temp;
    }
    clock_t end = clock();
    time_spent += (float)(end - begin) / CLOCKS_PER_SEC;
    pair<float,float> res (Xbest.second,time_spent);
    return res;
}