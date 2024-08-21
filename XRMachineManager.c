#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

#define TOTAL_MAQUINAS 5


typedef struct {
  int id_maquina[TOTAL_MAQUINAS];
  int* status_maquinas[TOTAL_MAQUINAS];
  Patient* pacientes[TOTAL_MAQUINAS];
}MachineManager;

MachineManager* criar_XRManager() {
MachineManager* gerenciador = (MachineManager*)malloc(sizeof( MachineManager));
  for (int i = 0; i < TOTAL_MAQUINAS; i++) {
    gerenciador->id_maquina[i] = i + 1; // IDs de 1 a 5
    gerenciador->status_maquinas[i] = 0; // 0 significa disponível
    gerenciador->pacientes[i] = NULL; // Nenhum paciente alocado inicialmente
  }
  return gerenciador;
}

int alocar_paciente(MachineManager* gerenciador, Patient* patient){
    
}


