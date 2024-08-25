#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "PatientQueue.h"
#include "XRMachineManager.h"


MachineManager* criar_XRManager() {
MachineManager* gerenciador = (MachineManager*)malloc(sizeof( MachineManager));
  for (int i = 0; i < TOTAL_MAQUINAS; i++) {
    gerenciador->id_maquina[i] = i + 1; // IDs de 1 a 5
    gerenciador->status_maquina[i] = 0; // 0 significa disponível
    gerenciador->paciente_maquina[i] = NULL; // Nenhum paciente alocado inicialmente
  }
  return gerenciador;
}

Paciente_Maquina alocar_paciente(MachineManager* gerenciador, Queue* patientQueue){
  Paciente_Maquina estrutura;
  while (!q_is_empty_patient(patientQueue)) {  // Continuar enquanto houver pacientes na fila
    Patient* patient = q_dequeue_patient(patientQueue);

  while(1){//fica até uma maquina ser desocupada
    for (int i=0; i<TOTAL_MAQUINAS; i++) 
        {
          if(gerenciador->status_maquina[i] == 0)
          { // ADICIONADO
            gerenciador->status_maquina[i] = 1;
            gerenciador->paciente_maquina[i] = patient;

            estrutura.maquina_id = gerenciador->id_maquina[i];
            estrutura.paciente_id = patient->id;
            
            return estrutura;
          }
        }
      }    
  sleep(1);
  }
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
