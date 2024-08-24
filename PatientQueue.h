#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H
#include "patient.h"


typedef struct queue_node QueueNode;
typedef struct queue Queue;      

//struct queue_node
struct queue_node
{
   Patient *patient;      
   QueueNode *next; 
};
struct queue
{
   QueueNode *inicio; // Pointer to the front of the queue.
   QueueNode *final;  // Pointer to the rear of the queue.
};

//Criar fila
Queue* create_queue_patient();

//Liberar a memória da fila
void q_free_patient(Queue *q);

//verificar se a fila esta vazia
int q_is_empty_patient(Queue *q);

//Adicionar paciente na fila
Patient* enqueue_patient(Queue *q, Patient *p);

//Remove e retorna o primeiro paciente da fila
Patient* q_dequeue_patient(Queue *q);

#endif
