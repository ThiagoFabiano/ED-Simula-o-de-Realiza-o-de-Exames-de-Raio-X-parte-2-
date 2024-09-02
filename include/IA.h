#ifndef IA_H
#define IA_H

typedef struct {
    const char *nome;
    double probabilidade;
    int nivel_gravidade;
    int contador;  
} Doenca;

void IADiagnostico(const char **nome, int *nivel_gravidade);

#endif
