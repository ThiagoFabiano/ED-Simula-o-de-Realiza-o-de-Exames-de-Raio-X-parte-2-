#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "exam.h"
#include "IA.h"
#include "ExamPriorityQueue.h"
#include "report.h"

static int id_laudo = 1;

const char* determinar_condicao(Exam *exame) 
{
    double p = (double)rand() / RAND_MAX;

    if (p < 0.8) 
    {
        return exame->condition_IA;  
    } 
    else 
    {
        const char *condicao_medico;
        int nivel_gravidade_temporario;
        do {
            IADiagnostico(&condicao_medico, &nivel_gravidade_temporario); 
        } while (condicao_medico == exame->condition_IA);  

        return condicao_medico;
    }
}

Report* criar_laudo(QueueExam *fila_exames,int tempoSimulacao, Exam *exame) {
   

    if (exame == NULL) {
        printf("Nenhum exame disponível na fila para a realização do laudo.\n");
        return NULL;
    }

    Report *laudo = (Report *)malloc(sizeof(Report));

    if (laudo == NULL) {
        return NULL;
    }

    laudo->id = id_laudo++; 
    laudo->exam_id = exame->id;
    laudo->patient_id = exame->patient_id;
    laudo->condition = determinar_condicao(exame);
    laudo->timestamp = tempoSimulacao;

    FILE *file = fopen("db_report.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de laudos.\n");
        free(laudo); 
        return NULL;
    }

    fprintf(file, "id: %d\n", laudo->id);
    fprintf(file, "exam_id: %d\n", laudo->exam_id);
    fprintf(file, "condition: %s\n", laudo->condition);
    fprintf(file, "timestamp: %d\n", laudo->timestamp);
    fprintf(file, "-------------------------\n");
    fclose(file);

    return laudo;
}

int get_last_laudo_id(){
    return id_laudo - 1;
}
