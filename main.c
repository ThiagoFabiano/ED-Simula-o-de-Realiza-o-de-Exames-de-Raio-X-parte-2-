#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "patient.h"

typedef struct {
    const char *nome;
    double probabilidade;
    int nivel_gravidade;
    int contador;  
} Doenca;

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

int main() {
    /* srand(time(NULL));

    const char *nome;
    int nivel_gravidade;
    int num_simulacoes = 1000;  

    for (int i = 0; i < num_simulacoes; i++) {
        IADiagnostico(&nome, &nivel_gravidade);
    }

    
    printf("Resultados apos %d simulaçoes:\n", num_simulacoes);
    for (int i = 0; i < num_doencas; i++) {
        printf("%s: %d vezes\n", doencas[i].nome, doencas[i].contador);
    }

    return 0; */

    int probabilidade;
    srand(time(NULL));


    while (1) {  
        struct tm timestamp;
        time_t t = time(NULL);
        probabilidade = rand() % 100;

        if(probabilidade < 20){
            timestamp = *localtime(&t);
            Patient* p = create_patient(1, "John Doe", &timestamp);
            printf("%d\n",get_patient_horario_chegada(p)); 
        } else {
            printf("Nao chama paciente\n"); 
        };
        Sleep(500);  
    }

    return 0;
}
