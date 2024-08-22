#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "patient.h"
#include "PatientQueue.h"

#define TOTAL_MAQUINAS 5


typedef struct {
  int id_maquina[TOTAL_MAQUINAS];
  int status_maquina[TOTAL_MAQUINAS];
  Patient* paciente_maquina[TOTAL_MAQUINAS];
}MachineManager;

MachineManager* criar_XRManager() {
MachineManager* gerenciador = (MachineManager*)malloc(sizeof( MachineManager));
  for (int i = 0; i < TOTAL_MAQUINAS; i++) {
    gerenciador->id_maquina[i] = i + 1; // IDs de 1 a 5
    gerenciador->status_maquina[i] = 0; // 0 significa disponível
    gerenciador->paciente_maquina[i] = NULL; // Nenhum paciente alocado inicialmente
  }
  return gerenciador;
}

int alocar_paciente(MachineManager* gerenciador, Queue* patientQueue){
  while (!q_is_empty(patientQueue)) {  // Continuar enquanto houver pacientes na fila
  Patient* patient = q_dequeue(patientQueue);
  
  while(1){//fica até uma maquina ser desocupada
    for (int i=0; i<TOTAL_MAQUINAS; i++) 
        {
          if(gerenciador->status_maquina[i] == 0)
            gerenciador->status_maquina[i] = 1;
            gerenciador->paciente_maquina[i] = patient;
  
            return gerenciador->id_maquina[i];  
        }
      }    
  sleep(1);
  }
  return -1;
}

void liberar_maquina(MachineManager* gerenciador, int id_maquina)
{
  for (int i=0; i<TOTAL_MAQUINAS; i++) 
  {
    if(gerenciador->status_maquina[i] == id_maquina)
      gerenciador->status_maquina[i] = 0;
      gerenciador->paciente_maquina[i] = NULL;
      break;  
  }
}
