#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "patient.h"
#include "exam.h"
#include "machine_manager.h"

#define UNIDADE_DE_TEMPO 1
#define TEMPO_EXAME 10

void chegada_paciente(int *id, PatientQueue *filaDePacientes) {
    int probabilidade = rand() % 100;
    if (probabilidade < 20) {
        char nomePaciente[50];
        struct tm timestamp;
        time_t t = time(NULL);

        sprintf(nomePaciente, "Maria %d", *id);
        timestamp = *localtime(&t);

        Patient* paciente = create_patient(*id, nomePaciente, &timestamp);
        enqueue_patient(filaDePacientes, paciente);
        (*id)++;
        printf("Paciente %s adicionado à fila.\n", nomePaciente);
    } else {
        printf("Não chama paciente.\n");
    }
}

void alocar_exame(XRMachineManager *gerenciadorDeMaquinas, PatientQueue *filaDePacientes) {
    if (!is_empty(filaDePacientes)) {
        int maquinaAlocadaId = alocar_paciente(gerenciadorDeMaquinas, filaDePacientes);
        Patient *paciente = dequeue_patient(filaDePacientes);
        Exam *exame = realizar_exame(maquinaAlocadaId, paciente->id);
        printf("Exame realizado para o paciente %d na máquina %d.\n", paciente->id, maquinaAlocadaId);
    } else {
        printf("Nenhum paciente na fila para alocar.\n");
    }
}

int main() {
    int id = 0;
    int tempoSimulacao = 0;
    PatientQueue *filaDePacientes = create_patient_queue();
    XRMachineManager *gerenciadorDeMaquinas = create_machine_manager();

    srand(time(NULL));

    while (1) {
        // A cada 1 unidade de tempo, verificamos a chegada de pacientes
        chegada_paciente(&id, filaDePacientes);

        // A cada 10 unidades de tempo, realizamos um exame
        if (tempoSimulacao % TEMPO_EXAME == 0) {
            alocar_exame(gerenciadorDeMaquinas, filaDePacientes);
        }

        // Incrementa o tempo total da simulação
        tempoSimulacao += UNIDADE_DE_TEMPO;

        // Pausa por 1 unidade de tempo
        Sleep(UNIDADE_DE_TEMPO);
    }

    return 0;
}
