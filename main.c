#define TEMPO_EXAME 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "exam.h"
#include "PatientQueue.h"
#include "patient.h"
#include "XRMachineManager.h"
#include "IA.h"
#include "ExamPriorityQueue.h"
#include "report.h"
#include "laudoPorCondicao.h"

#define UNIDADE_DE_TEMPO 1 
#define TEMPO_LAUDO 30
#define TEMPO_RELATORIO 100
#define TEMPO_LIMITE 7200
#define TEMPO_TOTAL_SIMULACAO 43200

void enfileirarPacientes(int probabilidade, char *nomePaciente, int *id, Queue* filaDePacientes){
    struct tm timestamp;
    time_t t = time(NULL);
    probabilidade = rand() % 100;


    if(probabilidade < 20){
        sprintf(nomePaciente, "Maria %d", *id);
        timestamp = *localtime(&t);
        Patient* paciente = create_patient(*id, nomePaciente, &timestamp); 
        enqueue_patient(filaDePacientes, paciente);         
        (*id)++;

    } 

}

void realizarExames(MachineManager* gerenciadorDeMaquinas, Queue* filaDePacientes, QueueExam* filaDeExamesPorPrioridade, int tempoSimulacao) {
    if(!q_is_empty_patient(filaDePacientes)){
        Paciente_Maquina pacienteMaquina = alocar_paciente(gerenciadorDeMaquinas, filaDePacientes, tempoSimulacao);
    }

    liberar_maquina(gerenciadorDeMaquinas, tempoSimulacao, filaDeExamesPorPrioridade); 
    
}

void realizarLaudos(QueueExam* filaDeExamesPorPrioridade, int tempoSimulacao, Exam *exame){
    Report* laudo = criar_laudo(filaDeExamesPorPrioridade, tempoSimulacao, exame);
}

int main() {

    int probabilidade;
    srand(time(NULL));

    int id = 1;
    int tempoSimulacao = 0;
    int tempoQueExecutouOUltimoLaudo = -1;
    int ultimoExameId = 0;
    int medicoTerminouLaudo = 1;
    Queue* filaDePacientes = create_queue_patient();
    QueueExam* filaDeExamesPorPrioridade = create_queue_exam();
    MachineManager* gerenciadorDeMaquinas = criar_XRManager();
    char nomePaciente[50];
    Exam *exame = NULL;
    
    //Loop para criar a fila de pacientes
    while (tempoSimulacao <= TEMPO_TOTAL_SIMULACAO){  
        enfileirarPacientes(probabilidade, nomePaciente, &id, filaDePacientes);

        realizarExames(gerenciadorDeMaquinas, filaDePacientes, filaDeExamesPorPrioridade,  tempoSimulacao);

        if(medicoTerminouLaudo && (!q_is_empty_exam(filaDeExamesPorPrioridade))){
            exame = dequeue_exam(filaDeExamesPorPrioridade, tempoSimulacao);
            medicoTerminouLaudo = 0;
        }
        //Condição que verifica se passou 30 unidades de tempo para realizar o laudo
        if((tempoSimulacao - tempoQueExecutouOUltimoLaudo >= TEMPO_LAUDO)){
            tempoQueExecutouOUltimoLaudo = tempoSimulacao;
            realizarLaudos(filaDeExamesPorPrioridade, tempoSimulacao, exame);
            medicoTerminouLaudo = 1;
        } 


    
        if((tempoSimulacao % TEMPO_RELATORIO == 0) && (tempoSimulacao > 1)){

            printf("Relatorio:\n");
            printf("Numero de pacientes que visitaram o hospital: %d\n", id);
            printf("Numero pacientes na fila aguardando exame: %d\n", quantidade_pacientes(filaDePacientes));
            printf("Numero de pacientes que ja realizaram exame: %d\n", get_last_exam_id() - 1);
            printf("Porcentagem de pacientes que fizeram exames e recebeu o laudo: %.2f%%\n", ((get_last_laudo_id() / (float)get_last_exam_id()) * 100));
            printf("Tempo medio de laudo: tempo medio que os exames ocupam a fila de prioridades: %.2f\n", calcular_tempo_medio_na_fila());
            imprimirTempoMedioDeLaudoPorCondicao();
            printf("---------------------------\n");
        } 

        if((tempoSimulacao % TEMPO_LIMITE == 0) && (tempoSimulacao > 1)){

            printf("Relatorio:\n");
            printf("Numero de exames realizados apos o limite de tempo estabelecido: %d\n", get_last_exam_id() - 1);
            printf("---------------------------\n");

        }


        tempoSimulacao += UNIDADE_DE_TEMPO;

        sleep(UNIDADE_DE_TEMPO);  
    };

    return 0;
}
