#ifndef XRMACHINEMANAGER_H
#define XRMACHINEMANAGER_H
#include "PatientQueue.h"


#define TOTAL_MAQUINAS 5

typedef struct {
int paciente_id;
int maquina_id;
}Paciente_Maquina;

typedef struct {
  int id_maquina[TOTAL_MAQUINAS];
  int status_maquina[TOTAL_MAQUINAS];
  Patient* paciente_maquina[TOTAL_MAQUINAS];
}MachineManager;

//criar organização das maquinas
MachineManager* criar_XRManager();

//alocar primeiro paciente da fila em uma maquina desocupada
Paciente_Maquina alocar_paciente(MachineManager* gerenciador, Queue* patientQueue);

//liberar maquina ocupada
void liberar_maquina(MachineManager* gerenciador, int id_maquina);

#endif
