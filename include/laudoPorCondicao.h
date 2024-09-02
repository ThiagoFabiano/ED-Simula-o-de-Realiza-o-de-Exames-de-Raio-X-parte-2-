
#ifndef LAUDO_POR_CONDICAO_H
#define LAUDO_POR_CONDICAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar dados de db_report.txt
typedef struct {
    int id;
    int exam_id;
    char condition[50];
    int timestamp;
} ReportR;

// Definição da estrutura para armazenar dados de de_exam.txt
typedef struct {
    int id;
    int xr_id;
    int patient_id;
    char condition_IA[50];
    int timestamp;
} ExamR;

// Função para ler o arquivo db_report.txt
int lerArquivoDeLaudos(const char *nomeArquivo, ReportR **reports);

// Função para ler o arquivo de_exam.txt
int lerArquivoDeExames(const char *nomeArquivo, ExamR **exams);

// Função para encontrar o exame por ID
int encontrarExamePorID(ExamR *exams, int numExams, int exam_id);

// Função para imprimir o tempo médio de laudo por condição
void imprimirTempoMedioDeLaudoPorCondicao();

#endif // LAUDO_POR_CONDICAO_H
