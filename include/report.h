#ifndef REPORT_H
#define REPORT_H
#include "exam.h"
#include "ExamPriorityQueue.h"

typedef struct report {
    int id;
    int exam_id;
    int patient_id;
    const char *condition;
    int timestamp;
} Report;

const char* determinar_condicao(Exam *exame);

Report* criar_laudo(QueueExam *fila_exames,int tempoSimulacao, Exam *exame);

int get_last_laudo_id();

#endif
