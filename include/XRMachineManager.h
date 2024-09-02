#ifndef XRMACHINEMANAGER_H
#define XRMACHINEMANAGER_H
#include "PatientQueue.h"
#include "exam.h"
#include "ExamPriorityQueue.h"


#define TOTAL_MAQUINAS 5
#define TEMPO_EXAME 10

typedef struct {
int paciente_id;
int maquina_id;
}Paciente_Maquina;

typedef struct {
  int id_maquina[TOTAL_MAQUINAS];
  int status_maquina[TOTAL_MAQUINAS];
  int tempo_inicio_exame[TOTAL_MAQUINAS];
  Patient* paciente_maquina[TOTAL_MAQUINAS];
}MachineManager;

//criar organização das maquinas
MachineManager* criar_XRManager();

//alocar primeiro paciente da fila em uma maquina desocupada
Paciente_Maquina alocar_paciente(MachineManager* gerenciador, Queue* patientQueue, int tempo_inicio_exame);

//liberar maquina ocupada
void liberar_maquina(MachineManager* gerenciador, int tempoSimulacao, QueueExam* filaDeExamesPorPrioridade);

#endif
