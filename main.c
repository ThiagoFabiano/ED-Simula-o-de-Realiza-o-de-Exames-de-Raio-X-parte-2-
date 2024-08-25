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
#define TEMPO_RELATORIO 100
#define TEMPO_LIMITE 7200

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

void realizarLaudos(QueueExam* filaDeExamesPorPrioridade, int tempoSimulacao){
    Report* laudo = criar_laudo(filaDeExamesPorPrioridade, tempoSimulacao);
    printf("Fianlizou o laudo\n"); 
}

int main() {

    int probabilidade;
    srand(time(NULL));

    int id = 1;
    int tempoSimulacao = 0;
    int tempoQueExecutouOUltimoLaudo = -1;
    int ultimoExameId = 0;
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
            realizarLaudos(filaDeExamesPorPrioridade, tempoSimulacao);
        } 
        printf("ultimo laudo %d\n", get_last_laudo_id());
        printf("ultimo exame %d\n", get_last_exam_id());

        if((tempoSimulacao % TEMPO_RELATORIO == 0) && (tempoSimulacao > 1)){
            
            printf("Relatorio:\n");
            printf("Numero de pacientes que visitaram o hospital: %d\n", id);
            printf("Numero pacientes na fila aguardando exame: %d\n", quantidade_pacientes(filaDePacientes));
            printf("Numero de pacientes que ja realizaram exame: %d\n", get_last_exam_id() - 1);
            printf("Porcentagem de pacientes que fizeram exames e recebeu o laudo: %.2f%%\n", ((get_last_laudo_id() / (float)get_last_exam_id()) * 100));
            printf("Tempo médio de laudo: tempo medio que os exames ocupam a fila de prioridades: %d\n", get_time_first_to_last() / get_last_laudo_id());
        } 

        if((tempoSimulacao % TEMPO_LIMITE == 0) && (tempoSimulacao > 1)){
            
            printf("Relatório:\n");
            printf("Número de exames realizados após o limite de tempo estabelecido: %d\n", get_last_exam_id() - 1);
        } 


        tempoSimulacao += UNIDADE_DE_TEMPO;
        
        sleep(UNIDADE_DE_TEMPO);  
    };

    return 0;
}

