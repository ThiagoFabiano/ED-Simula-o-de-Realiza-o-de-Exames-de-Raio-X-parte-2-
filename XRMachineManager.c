#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "PatientQueue.h"
#include "XRMachineManager.h"
#include "exam.h"
#include "ExamPriorityQueue.h"


MachineManager* criar_XRManager() {
MachineManager* gerenciador = (MachineManager*)malloc(sizeof( MachineManager));
  for (int i = 0; i < TOTAL_MAQUINAS; i++) {
    gerenciador->id_maquina[i] = i + 1; // IDs de 1 a 5
    gerenciador->status_maquina[i] = 0; // 0 significa disponível
    gerenciador->paciente_maquina[i] = NULL; // Nenhum paciente alocado inicialmente
  }
  return gerenciador;
}

Paciente_Maquina alocar_paciente(MachineManager* gerenciador, Queue* patientQueue, int tempo_inicio_exame){
  Paciente_Maquina estrutura;

  
    for (int i=0; i<TOTAL_MAQUINAS; i++) 
        {
          if(gerenciador->status_maquina[i] == 0)
          { // ADICIONADO
            Patient* patient = q_dequeue_patient(patientQueue);
            gerenciador->status_maquina[i] = 1;
            gerenciador->paciente_maquina[i] = patient;
            gerenciador->tempo_inicio_exame[i] = tempo_inicio_exame;

            estrutura.maquina_id = gerenciador->id_maquina[i];
            estrutura.paciente_id = patient->id;
             printf("Alocou na maquina %d\n", i); 
            return estrutura;
          }
        }
     
  
}

void liberar_maquina(MachineManager* gerenciador, int tempoSimulacao, QueueExam* filaDeExamesPorPrioridade)
{
  for (int i=0; i<TOTAL_MAQUINAS; i++) 
  {
    if(gerenciador->status_maquina[i] == 1 && (tempoSimulacao - gerenciador->tempo_inicio_exame[i]) >= TEMPO_EXAME){
      Exam *exame = realizar_exame(gerenciador->id_maquina[i], gerenciador->paciente_maquina[i]->id);
      enqueue_exam(filaDeExamesPorPrioridade, exame);
      gerenciador->status_maquina[i] = 0;
      gerenciador->paciente_maquina[i] = NULL;
      printf("Desalocou na maquina %d\n", i);

      break;  
    }
  }
}
