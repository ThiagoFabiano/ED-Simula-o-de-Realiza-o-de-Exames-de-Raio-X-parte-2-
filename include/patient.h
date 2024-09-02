#ifndef PATIENT_H
#define PATIENT_H

#include <time.h>

typedef struct patient Patient;

struct patient {
    int id;
    char* name;
    struct tm *timestamp;
};

//Cria um novo paciente.
Patient* create_patient(int id, const char *name, struct tm *timestamp);
//Libera a memória alocada para a estrutura do paciente.
void destroy_patient(Patient *patient);
//Retorna a identificação única do paciente.
int get_patient_id(Patient *patient);
//Retorna o nome do paciente.
const char* get_patient_name(Patient *patient);
// Retorna a data de nascimento do paciente.
struct tm* get_patient_horario_chegada(Patient *patient);

#endif