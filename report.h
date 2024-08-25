#ifndef REPORT_H
#define REPORT_H
#include "exam.h"
#include "ExamPriorityQueue.h"

typedef struct report {
    int id;
    int exam_id;
    int patient_id;
    const char *condition;
    struct tm timestamp;
} Report;

const char* determinar_condicao(Exam *exame);

Report* criar_laudo(Queue *fila_exames);

#endif
