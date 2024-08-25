#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "PatientQueue.h"
#include "patient.h"
#include "XRMachineManager.h"
#include "Exam.h"
#include "IA.h"

int main() {

    int probabilidade;
    srand(time(NULL));

    int unidadeDeTempo = 500;

    int id = 1;
    Queue* filaDePacientes = create_queue_patient();
    MachineManager* gerenciadorDeMaquinas = criar_XRManager();
    char nomePaciente[50];

    while (1) {  
        struct tm timestamp;
        time_t t = time(NULL);
        probabilidade = rand() % 100;
        

        if(probabilidade < 20){
            sprintf(nomePaciente, "Maria %d", id);
            timestamp = *localtime(&t);
            Patient* paciente = create_patient(id, nomePaciente, &timestamp); 
            enqueue_patient(filaDePacientes, paciente);

            //Teste
            const char *nomeDoenca;
            int nivel_gravidade;
            int maquinaAlocadaId = alocar_paciente(gerenciadorDeMaquinas, filaDePacientes);
            IADiagnostico(&nomeDoenca, &nivel_gravidade);
            
           
            id++;
        } else {
            printf("Nao chama paciente\n"); 
        };

        
        Sleep(unidadeDeTempo);  
    }

    return 0;
}
