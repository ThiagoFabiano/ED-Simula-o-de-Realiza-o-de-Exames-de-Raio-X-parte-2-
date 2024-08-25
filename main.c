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

    
void enfileirarPacientes(int probabilidade, char *nomePaciente, int *id, Queue* filaDePacientes){
    struct tm timestamp;
    time_t t = time(NULL);
    probabilidade = rand() % 100;
    

    if(probabilidade < 20){
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
    printf("realizou um exame\n");
    Paciente_Maquina pacienteMaquina = alocar_paciente(gerenciadorDeMaquinas, filaDePacientes);
    Exam *exame = realizar_exame(pacienteMaquina.maquina_id, pacienteMaquina.paciente_id);
    liberar_maquina(gerenciadorDeMaquinas, pacienteMaquina.maquina_id);
    enqueue_exam(filaDeExamesPorPrioridade, exame);

};

int main() {

    int probabilidade;
    srand(time(NULL));

    int id = 1;
    int tempoSimulacao = 0;
    Queue* filaDePacientes = create_queue_patient();
    QueueExam* filaDeExamesPorPrioridade = create_queue_exam();
    MachineManager* gerenciadorDeMaquinas = criar_XRManager();
    char nomePaciente[50];
    
    //Loop para criar a fila de pacientes
    while (1) {  
        printf("%d\n",tempoSimulacao);
        enfileirarPacientes(probabilidade, nomePaciente, &id, filaDePacientes);

        if ((tempoSimulacao % TEMPO_EXAME == 0) && (tempoSimulacao >= TEMPO_EXAME)) {
            realizarExames( gerenciadorDeMaquinas,filaDePacientes, filaDeExamesPorPrioridade);
        };

        tempoSimulacao += UNIDADE_DE_TEMPO;
        
        sleep(UNIDADE_DE_TEMPO);  
    };

    

    //Loop para realização dos laudos
    /* while(1){
        Sleep(unidadeDeTempo * 30); 
        Report* laudo = criar_laudo(filaDeExamesPorPrioridade);
    } */
    /* 
    //Loop para imprimir retlatório
    while (1) {  
        printf("Numero de pacientes que visitaram o hospital: %d", id);
        printf("Numero de pacientes na fila aguardando o exame: %d", id);

    } */

    return 0;
}

