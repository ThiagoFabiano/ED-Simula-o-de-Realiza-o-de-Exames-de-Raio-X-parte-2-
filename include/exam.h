#ifndef EXAM_H
#define EXAM_H
#include <time.h>

typedef struct exam Exam;

typedef struct exam {
  int id;
  int id_rx;
  int patient_id;
  const char *condition_IA;
  int nivel_gravidade;
  int timestamp;
  int tempo_entrada_na_fila;
} Exam;

Exam *realizar_exame(int id_rx, int patient_id, int tempoSimulacao);

void destroy_exam(Exam *exam);

int get_exam_id(Exam *exam);

int get_exam_patient_id(Exam *exam);

int get_exam_rx_id(Exam *exam);

int *get_exam_time(Exam *exam);

int get_last_exam_id();

#endif // EXAM_H
