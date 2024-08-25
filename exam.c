#include "IA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "exam.h"

static int id_exam = 1;



Exam *realizar_exame(int id_rx, int patient_id) {
  const char *condition_IA;
  int nivel_gravidade;

  Exam *exame = (Exam *)malloc(sizeof(Exam));

  if (exame == NULL) {
    return NULL;
  }

  IADiagnostico(&condition_IA, &nivel_gravidade);

  exame->id = id_exam++;
  exame->id_rx = id_rx;
  exame->patient_id = patient_id;
  exame->condition_IA = condition_IA;
  exame->nivel_gravidade = nivel_gravidade;

  time_t rawtime = time(NULL);
  exame->timestamp = *localtime(&rawtime);

  FILE *file = fopen("db_exam.txt", "a");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo de exames.\n");                   
    free(exame);
    return NULL;
  } 

  fprintf(file, "ID do exame: %d\n", exame->id);
  fprintf(file, "ID da máquina: %d\n", exame->id_rx);
  fprintf(file, "ID do paciente: %d\n", exame->patient_id);
  fprintf(file, "Diagnóstico da IA: %s\n", exame->condition_IA);
  fprintf(file, "Horário do exame: %s", asctime(&(exame->timestamp)));
  fprintf(file, "-------------------------\n");
  fclose(file);

  return exame;
}

void destroy_exam(Exam *exam) {
  if (exam != NULL) {
    free(exam);
  }
}

int get_exam_id(Exam *exam) {
  if (exam == NULL) {
    return -1;
  }
  return exam->id;
}

int get_exam_patient_id(Exam *exam) {
  if (exam == NULL) {
    return -1;
  }
  return exam->patient_id;
}

int get_exam_rx_id(Exam *exam) {
  if (exam == NULL) {
    return -1;
  }
  return exam->id_rx;
}

struct tm *get_exam_time(Exam *exam) {
  if (exam == NULL) {
    return NULL;
  }
  return &(exam->timestamp);
}

int get_last_exam_id(){
  return id_exam - 1;
};

