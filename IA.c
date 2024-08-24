#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "IA.h"

Doenca doencas[] = {
    {"Saude Normal", 0.3, 1, 0},
    {"Bronquite", 0.2, 2, 0},
    {"Pneumonia", 0.1, 3, 0},
    {"COVID", 0.1, 4, 0},
    {"Embolia pulmonar", 0.05, 4, 0},
    {"Derrame pleural", 0.05, 4, 0},
    {"Fibrose pulmonar", 0.05, 5, 0},
    {"Tuberculose", 0.05, 5, 0},
    {"Câncer de pulmao", 0.1, 6, 0}
};

const int num_doencas = sizeof(doencas) / sizeof(doencas[0]);

void IADiagnostico(const char **nome, int *nivel_gravidade) {
    double r = (double)rand() / RAND_MAX; 
    double acumulado = 0.0;

    for (int i = 0; i < num_doencas; i++) {
        acumulado += doencas[i].probabilidade;
        if (r < acumulado) {
            *nome = doencas[i].nome;
            *nivel_gravidade = doencas[i].nivel_gravidade;
            doencas[i].contador++; 
            return;
        }
    }
}