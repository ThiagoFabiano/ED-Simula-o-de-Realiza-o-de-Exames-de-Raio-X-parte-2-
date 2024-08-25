#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "exam.h"
#include "IA.h"
#include "ExamPriorityQueue.h"
#include "report.h"

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
        do {
            IADiagnostico(&condicao_medico, NULL);  
        } while (condicao_medico == exame->condition_IA);  

        return condicao_medico;
    }
}

Report* criar_laudo(Queue *fila_exames) {
    Exam *exame = dequeue_exam(fila_exames);

    if (exame == NULL) {
        printf("Nenhum exame disponível na fila para a realização do laudo.\n");
        return NULL;
    }

    Report *laudo = (Report *)malloc(sizeof(Report));

    if (laudo == NULL) {
        return NULL;
    }

    laudo->id = rand();  
    laudo->exam_id = exame->id;
    laudo->patient_id = exame->patient_id;
    laudo->condition = determinar_condicao(exame);
    laudo->timestamp = exame->timestamp;

    FILE *file = fopen("db_report.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de laudos.\n");
        free(laudo); 
        return NULL;
    }

    fprintf(file, "ID do Laudo: %d\n", laudo->id);
    fprintf(file, "ID do Exame: %d\n", laudo->exam_id);
    fprintf(file, "ID do Paciente: %d\n", laudo->patient_id);
    fprintf(file, "Condição Final: %s\n", laudo->condition);
    fprintf(file, "Horário do Laudo: %s", asctime(&(laudo->timestamp)));
    fprintf(file, "-------------------------\n");
    fclose(file);

    return laudo;
}
