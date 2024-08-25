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
  struct tm timestamp;
} Exam;

Exam *realizar_exame(int id_rx, int patient_id);

void destroy_exam(Exam *exam);

int get_exam_id(Exam *exam);

int get_exam_patient_id(Exam *exam);

int get_exam_rx_id(Exam *exam);

struct tm *get_exam_time(Exam *exam);

int get_last_exam_id();

#endif // EXAM_H
