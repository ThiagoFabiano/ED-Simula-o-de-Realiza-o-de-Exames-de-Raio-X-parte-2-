#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    const char *nome;
    double probabilidade;
    int nivel_gravidade;
} Doenca;

const Doenca doencas[] = {
    {"Saude Normal", 0.3, 1},
    {"Bronquite", 0.2, 2},
    {"Pneumonia", 0.1, 3},
    {"COVID", 0.1, 4},
    {"Embolia pulmonar", 0.05, 4},
    {"Derrame pleural", 0.05, 4},
    {"Fibrose pulmonar", 0.05, 5},
    {"Tuberculose", 0.05, 5},
    {"Cancer de pulmao", 0.1, 6}
};

const int num_doencas = sizeof(doencas) / sizeof(doencas[0]);

void selecionarDoencaAleatoria(const char **nome, int *nivel_gravidade) {
    double r = (double)rand() / RAND_MAX; // Gera um número aleatório entre 0 e 1
    double acumulado = 0.0;

    for (int i = 0; i < num_doencas; i++) {
        acumulado += doencas[i].probabilidade;
        if (r < acumulado) {
            *nome = doencas[i].nome;
            *nivel_gravidade = doencas[i].nivel_gravidade;
            return;
        }
    }

}

int main() {
    srand(time(NULL));

    const char *nome;
    int nivel_gravidade;

    selecionarDoencaAleatoria(&nome, &nivel_gravidade);

    printf("Doenca selecionada: %s\n", nome);
    printf("Nivel de gravidade: %d\n", nivel_gravidade);

    return 0;
}
