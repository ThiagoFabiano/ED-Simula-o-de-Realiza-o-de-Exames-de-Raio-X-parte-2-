#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "patient.h"

/* teste */

Patient* create_patient(int id, const char *name, struct tm *timestamp) {
    Patient *new_patient = (Patient*)malloc(sizeof(Patient));
    if (new_patient == NULL) {
        return NULL;
    }

    new_patient->id = id;
    new_patient->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    if (new_patient->name == NULL) {
        free(new_patient);

        return NULL;
    }

    strcpy(new_patient->name, name);
    new_patient->timestamp = timestamp;

    FILE *file = fopen("db_patient.txt", "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo db_patient.txt");
        free(new_patient->name);
        free(new_patient);
        return NULL;
    }

    time_t current_time;
    current_time = time(NULL); 
    struct tm *horario_chegada;
    horario_chegada = localtime(&current_time);
    
    fprintf(file, "ID: %d\n", id);
    fprintf(file, "Nome: %s\n", name);
    fprintf(file, "Horario de Chegada: %s\n", asctime(timestamp));
    fprintf(file, "-------------------------\n");
    fclose(file);

    return new_patient;
    
}

void destroy_patient(Patient *patient) {
    if (patient != NULL) {
        free(patient->name);
        free(patient);

    
    }
}

int get_patient_id(Patient *patient) {
    if (patient == NULL) {
        return -1;
    }
    return patient->id;
}

const char* get_patient_name(Patient *patient) {
    if (patient == NULL) {
        return NULL;
    }
    return patient->name;
}

struct tm* get_patient_horario_chegada(Patient *patient) {
    if (patient == NULL) {
        return NULL;
    }    
    return patient->timestamp;
}