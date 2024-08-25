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

typedef struct {
    int tempoInicioExame;
    int maquinaOcupada;
} ControleExame;

void enfileirarPacientes(int probabilidade, char nomePaciente, int *id, Queue filaDePacientes){
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

void realizarExames(MachineManager* gerenciadorDeMaquinas, Queue* filaDePacientes, QueueExam* filaDeExamesPorPrioridade, ControleExame* controleExame, int tempoSimulacao) {
    for (int i = 0; i < TOTAL_MAQUINAS; i++) {
        if (gerenciadorDeMaquinas->status_maquina[i] == 0 && !q_is_empty_patient(filaDePacientes)) {
            // Alocar paciente à máquina e iniciar o exame
            Paciente_Maquina pacienteMaquina = alocar_paciente(gerenciadorDeMaquinas, filaDePacientes);
            controleExame[i].tempoInicioExame = tempoSimulacao;
            controleExame[i].maquinaOcupada = 1;
            printf("Iniciou exame na máquina %d\n", gerenciadorDeMaquinas->id_maquina[i]);
        }

        // Verifica se o exame terminou
        if (controleExame[i].maquinaOcupada && (tempoSimulacao - controleExame[i].tempoInicioExame) >= TEMPO_EXAME) {
            Exam *exame = realizar_exame(gerenciadorDeMaquinas->id_maquina[i], gerenciadorDeMaquinas->paciente_maquina[i]->id);
            liberar_maquina(gerenciadorDeMaquinas, gerenciadorDeMaquinas->id_maquina[i]);
            enqueue_exam(filaDeExamesPorPrioridade, exame);
            controleExame[i].maquinaOcupada = 0;
            printf("Finalizou exame na máquina %d\n", gerenciadorDeMaquinas->id_maquina[i]);
        }
    }
}

void realizarLaudos(QueueExam* filaDeExamesPorPrioridade){
    Report* laudo = criar_laudo(filaDeExamesPorPrioridade);
    printf("Finalizou o laudo\n"); 
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
    ControleExame controleExame[TOTAL_MAQUINAS] = {0}; // Controle de exame por máquina
    char nomePaciente[50];
    
    // Loop para criar a fila de pacientes
    while (1) {  
        printf("Tempo de simulação: %d\n", tempoSimulacao);
        enfileirarPacientes(probabilidade, nomePaciente, &id, filaDePacientes);

        realizarExames(gerenciadorDeMaquinas, filaDePacientes, filaDeExamesPorPrioridade, controleExame, tempoSimulacao);

        if ((!q_is_empty_exam(filaDeExamesPorPrioridade)) && (tempoSimulacao - tempoQueExecutouOUltimoLaudo >= TEMPO_LAUDO)) {
            tempoQueExecutouOUltimoLaudo = tempoSimulacao;
            realizarLaudos(filaDeExamesPorPrioridade);
        } 

        tempoSimulacao += UNIDADE_DE_TEMPO;
        sleep(UNIDADE_DE_TEMPO);  
    }

    return 0;
}