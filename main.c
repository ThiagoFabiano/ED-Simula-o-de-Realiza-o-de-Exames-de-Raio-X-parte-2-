#define TEMPO_EXAME 10
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

void realizarExames(MachineManager* gerenciadorDeMaquinas, Queue* filaDePacientes, QueueExam* filaDeExamesPorPrioridade, int tempoSimulacao) {
    if(!q_is_empty_patient(filaDePacientes)){
        Paciente_Maquina pacienteMaquina = alocar_paciente(gerenciadorDeMaquinas, filaDePacientes, tempoSimulacao);
    }

    liberar_maquina(gerenciadorDeMaquinas, tempoSimulacao, filaDeExamesPorPrioridade); // ADICIONAR COMO PARAMETRO ESSES TREM DEBAIXO E COLOCAR NO .H  
    
}

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

        realizarExames(gerenciadorDeMaquinas, filaDePacientes, filaDeExamesPorPrioridade,  tempoSimulacao);

        if((!q_is_empty_exam(filaDeExamesPorPrioridade)) && (tempoSimulacao - tempoQueExecutouOUltimoLaudo >= TEMPO_LAUDO)){
            tempoQueExecutouOUltimoLaudo = tempoSimulacao;
            realizarLaudos(filaDeExamesPorPrioridade);
        } 


        tempoSimulacao += UNIDADE_DE_TEMPO;
        
        sleep(UNIDADE_DE_TEMPO);  
    };

    

 

    return 0;
}

