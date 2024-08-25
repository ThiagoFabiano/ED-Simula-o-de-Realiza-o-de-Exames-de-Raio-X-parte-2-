#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "exam.h"
#include "PatientQueue.h"
#include "patient.h"
#include "XRMachineManager.h"
#include "IA.h"
#include "ExamPriorityQueue.h"
#include "report.h"

int main() {

    int probabilidade;
    srand(time(NULL));

    int unidadeDeTempo = 500;

    int id = 1;
    Queue* filaDePacientes = create_queue_patient();
    Queue* filaDeExamesPorPrioridade = create_queue_exam()
    MachineManager* gerenciadorDeMaquinas = criar_XRManager();
    char nomePaciente[50];


    //Loop para criar a fila de pacientes
    while (1) {  
        struct tm timestamp;
        time_t t = time(NULL);
        probabilidade = rand() % 100;
        

        if(probabilidade < 20){
            sprintf(nomePaciente, "Maria %d", id);
            timestamp = *localtime(&t);
            Patient* paciente = create_patient(id, nomePaciente, &timestamp); 
            enqueue_patient(filaDePacientes, paciente);         
            id++;
            
        } else {
            printf("Nao chama paciente\n"); 
        };
        Sleep(unidadeDeTempo);  
    }

    //Loop para a realização dos exames
    while(1){
        int maquinaAlocadaId = alocar_paciente(gerenciadorDeMaquinas, filaDePacientes);
        Exam *exame = realizar_exame(maquinaAlocadaId, paciente->id);
        Sleep(unidadeDeTempo * 10); 
        liberar_maquina(gerenciadorDeMaquinas, maquinaAlocadaId);
        enqueue_exam(filaDeExamesPorPrioridade, exame);
    }

    //Loop para realização dos laudos
    while(1){
        Sleep(unidadeDeTempo * 30); 
        Report* laudo = criar_laudo(filaDeExamesPorPrioridade)
    }

    //Loop para imprimir retlatório
    while (1) {  
        printf("Numero de pacientes que visitaram o hospital: %d", id);
        printf("Numero de pacientes na fila aguardando o exame: %d", id);

    }

    return 0;
}
