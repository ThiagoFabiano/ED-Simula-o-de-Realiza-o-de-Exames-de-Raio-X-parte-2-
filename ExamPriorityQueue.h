#ifndef EXAMPRIORITYQUEUE_H
#define EXAMPRIORITYQUEUE_H
#include "exam.h"

typedef struct queue_node QueueNode;
typedef struct queue Queue;     

struct queue
{
   QueueNode *inicio; // Pointer to the front of the queue.
   QueueNode *final;  // Pointer to the rear of the queue.
};
//struct queue_node
struct queue_node
{
   Exam *exam;      
   QueueNode *next; 
};

//Criar fila
Queue* create_queue_exam();

//Liberar a memória da fila
void q_free_exam(Queue *q);

//verificar se a fila esta vazia
int q_is_empty_exam(Queue *q);

//Adicionar paciente na fila
Exam* enqueue_exam(Queue *q, Exam *p);

//Remove e retorna o primeiro paciente da fila
Exam* q_dequeue_exam(Queue *q);

void q_print_exam(Queue *q);

#endif