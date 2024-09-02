#ifndef EXAMPRIORITYQUEUE_H
#define EXAMPRIORITYQUEUE_H
#include "exam.h"

typedef struct queue_node_exam QueueNodeExam;
typedef struct queue_exam QueueExam;     

struct queue_exam
{
   QueueNodeExam *inicio; // Pointer to the front of the queue.
   QueueNodeExam *final;  // Pointer to the rear of the queue.
};
//struct queue_node
struct queue_node_exam
{
   Exam *exam;      
   QueueNodeExam *next; 
};

QueueExam* create_queue_exam();

void q_free_exam(QueueExam *q);

int q_is_empty_exam(QueueExam *q);

Exam* enqueue_exam(QueueExam *q, Exam *e, int tempoSimulacao);

Exam* dequeue_exam(QueueExam *q, int tempoSimulacao);

void q_print_exam(QueueExam *q);

float calcular_tempo_medio_na_fila();

float calcular_tempo_medio_na_fila();

#endif
