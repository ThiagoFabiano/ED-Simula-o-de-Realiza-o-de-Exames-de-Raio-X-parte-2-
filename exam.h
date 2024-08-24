#ifndef EXAM_H
#define EXAM_H
#include <time.h>

typedef struct exam Exam;

Exam *realizar_exame(int id_rx, int patient_id);

void destroy_exam(Exam *exam);

int get_exam_id(Exam *exam);

int get_exam_patient_id(Exam *exam);

int get_exam_rx_id(Exam *exam);

struct tm *get_exam_time(Exam *exam);

#endif // EXAM_H
