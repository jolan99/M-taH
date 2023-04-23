#include "utiles.h"
#include "Lecturebis.h"
#include "recuit_simule.h"
// #include "Dgradient.h"
#include <time.h>
#include <queue>
#include <iostream>
using namespace std;

// pair<float,float> recuit_simule(donnees data, int nb_classes){
//     float time_spent = 0.0;
//     clock_t begin = clock();
//     pair<solution,float> X = init_solution3(nb_classes, data);
//     pair<solution,float> Xbest = X;
//     float temp = 1000;
//     float t = 0;
//     while (temp > 0.1){
//         while (t<data.nb_sommets*data.nb_sommets){
//             queue<solution> voisin = voisinage(data, X.first, nb_classes);
//             pair<solution,float> X1 (voisin.front(),valeur_solution(voisin.front(),data));
//             float delta = (X1.second - X.second);
//             if (delta<0){
//                 X = X1;
//                 if (X1.second < Xbest.second){
//                     Xbest = X1;
//                 }
//             }
//             else{
//                 float p = ((float) rand() / (RAND_MAX));
//                 if (p <= exp(-(delta/temp))){
//                     X = X1;
//                 }
//             }
//             t = t+1;            
//         }
//         temp = 0.9 * temp;
//     }
//     clock_t end = clock();
//     time_spent += (float)(end - begin) / CLOCKS_PER_SEC;
//     pair<float,float> res (time_spent,Xbest.second);
//     return res;
// }

// pair<float,float> recuit_simule(donnees data, int nb_classes){
//     float time_spent = 0.0;
//     clock_t begin = clock();
//     pair<solution,float> X = init_solution3(nb_classes, data);
//     pair<solution,float> X1;
//     pair<solution,float> Xbest = X;
//     queue<solution> voisin;
//     float temp = 1000;
//     float t = 0;
//     while (temp > 0.1){
//         while (t<data.nb_sommets*data.nb_sommets){
//             voisin = voisinage(data, X.first, nb_classes);
//             X1.first = voisin.front();
//             X1.second = valeur_solution(voisin.front(),data);
//             voisin.pop();
//             while(!(is_valid(X1.first,data,nb_classes))){ // on choisit dans le voisinage une solution réalisable
//                 X1.first = voisin.front();
//                 X1.second = valeur_solution(voisin.front(),data);
//                 voisin.pop();
//             }
//             queue<solution> voisin = voisinage(data, X.first, nb_classes);
//             pair<solution,float> X1 (voisin.front(),valeur_solution(voisin.front(),data));
//             float delta = (X1.second - X.second);
//             if (delta<0){
//                 X = X1;
//                 if (X1.second < Xbest.second){
//                     Xbest = X1;
//                 }
//             }
//             else{
//                 float p = ((float) rand() / (RAND_MAX));
//                 if (p <= exp(-(delta/temp))){
//                     X = X1;
//                 }
//             }
//             t = t+1;            
//         }
//         temp = 0.9 * temp;
//     }
//     clock_t end = clock();
//     time_spent += (float)(end - begin) / CLOCKS_PER_SEC;
//     pair<float,float> res (time_spent,Xbest.second);
//     return res;
// }



pair<float,float> recuit_simule(donnees data, int nb_classes){
    float time_spent = 0.0;
    clock_t begin = clock();
    pair<solution,float> X = init_solution3(nb_classes, data);
    pair<solution,float> Xbest = X;
    pair<solution,float> X1;
    bool valid = false;
    float temp = 1000;
    float t = 0;
    int change_sol_init;
    int count;
    // cout << "debug 1" << endl;
    while (temp > 0.1){
        // cout << "debug 2" << endl;
        while (t<data.nb_sommets*data.nb_sommets){
            // cout << "debug 3" << endl;
            queue<solution> voisin = voisinage(data, X.first, nb_classes);
            // cout << "taille du voisinage : " << voisin.size() << endl;
            change_sol_init = 0;
            count = 0;
            while (valid !=true){
                if(change_sol_init == voisin.size()){ // si aucune solution du voisinage n'est réalisable, on prend une nouvelle solution initiale
                    // cout << "debug ############" << endl;
                    X = init_solution3(nb_classes, data);
                    Xbest = X;
                    voisin = voisinage(data, X.first, nb_classes);
                    change_sol_init = 0; // on réinitialise le compte 
                    count += 1;
                    if(count == 5){
                        break;
                    }
                }
                else{
                    // cout << "debug 4" << endl;
                    X1.first = voisin.front();
                    X1.second = valeur_solution(voisin.front(),data);
                    valid = is_valid(X1.first,data, nb_classes);
                    voisin.pop();
                    change_sol_init +=1;
                }

            }
            // cout << "debug 5" << endl;
            float delta = (X1.second - X.second);
            if (delta<0){
                // cout << "debug 6" << endl;
                X = X1;
                if (X1.second < Xbest.second){
                    Xbest = X1;
                }
            }
            else{
                // cout << "debug 6bis" << endl;
                float p = ((float) rand() / (RAND_MAX));
                if (p <= exp(-(delta/temp))){
                    X = X1;
                }
            }
            // cout << "debug 7" << endl;
            t = t+1;            
        }
        // cout << "debug 8" << endl;
        temp = 0.9 * temp;
    }
    // cout << "debug 9" << endl;
    clock_t end = clock();
    time_spent += (float)(end - begin) / CLOCKS_PER_SEC;
    pair<float,float> res (time_spent,Xbest.second);
    return res;
}



