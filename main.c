#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "exam.h"
#include "PatientQueue.h"
#include "patient.h"
#include "XRMachineManager.h"
#include "IA.h"
#include "ExamPriorityQueue.h"
#include "report.h"

#define UNIDADE_DE_TEMPO 1
#define TEMPO_EXAME 10
#define TEMPO_LAUDO 30

    
void enfileirarPacientes(int probabilidade, char *nomePaciente, int *id, Queue* filaDePacientes){
    struct tm timestamp;
    time_t t = time(NULL);
    probabilidade = rand() % 100;
    

    if(probabilidade < 101){
        printf("CHAMOU\n");
        sprintf(nomePaciente, "Maria %d", *id);
        timestamp = *localtime(&t);
        Patient* paciente = create_patient(*id, nomePaciente, &timestamp); 
        enqueue_patient(filaDePacientes, paciente);         
        (*id)++;
        
    } else {
        printf("Nao chama paciente\n"); 
    };

}

void realizarExames(MachineManager* gerenciadorDeMaquinas, Queue* filaDePacientes, QueueExam* filaDeExamesPorPrioridade){
    Paciente_Maquina pacienteMaquina = alocar_paciente(gerenciadorDeMaquinas, filaDePacientes);
    Exam *exame = realizar_exame(pacienteMaquina.maquina_id, pacienteMaquina.paciente_id);
    liberar_maquina(gerenciadorDeMaquinas, pacienteMaquina.maquina_id);
    enqueue_exam(filaDeExamesPorPrioridade, exame);
    printf("Realizou exame"); 
};

void realizarLaudos(QueueExam* filaDeExamesPorPrioridade){
    Report* laudo = criar_laudo(filaDeExamesPorPrioridade);
    printf("Fianlizou o laudo\n"); 
}

int main() {

    int probabilidade;
    srand(time(NULL));

    int id = 1;
    int tempoSimulacao = 0;
    int tempoQueExecutouOUltimoLaudo = -1;
    Queue* filaDePacientes = create_queue_patient();
    QueueExam* filaDeExamesPorPrioridade = create_queue_exam();
    MachineManager* gerenciadorDeMaquinas = criar_XRManager();
    char nomePaciente[50];
    
    //Loop para criar a fila de pacientes
    while (1) {  
        printf("%d\n",tempoSimulacao);
        enfileirarPacientes(probabilidade, nomePaciente, &id, filaDePacientes);

        if (tempoSimulacao % UNIDADE_DE_TEMPO == 0) {
            // Verifica se há pacientes na fila e máquinas disponíveis
            while (!q_is_empty_patient(filaDePacientes) && tempoSimulacao % TEMPO_EXAME < TEMPO_EXAME) {
                realizarExames(gerenciadorDeMaquinas, filaDePacientes, filaDeExamesPorPrioridade);
            }
        }

        if((!q_is_empty_exam(filaDeExamesPorPrioridade)) && (tempoSimulacao - tempoQueExecutouOUltimoLaudo >= TEMPO_LAUDO)){
            tempoQueExecutouOUltimoLaudo = tempoSimulacao;
            realizarLaudos(filaDeExamesPorPrioridade);
        } 


        tempoSimulacao += UNIDADE_DE_TEMPO;
        
        sleep(UNIDADE_DE_TEMPO);  
    };

    

 

    return 0;
}

