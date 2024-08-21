#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H
#include "patient.h"


typedef struct queue Queue;          
typedef struct queue_node QueueNode;

//Criar fila
Queue create_queue();

//Liberar a memória da fila
void q_free(Queue *q);

//verificar se a fila esta vazia
int q_is_empty(Queue *q);

//Adicionar paciente na fila
Patient* enqueue_patient(Queue *q, Patient *p);

//Remove e retorna o primeiro paciente da fila
Patient* q_dequeue(Queue *q);

#endif