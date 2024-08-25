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

Queue* create_queue_exam();

void q_free_exam(Queue *q);

int q_is_empty_exam(Queue *q);

Exam* enqueue_exam(Queue *q, Exam *e);

Exam* dequeue_exam(Queue *q);

void q_print_exam(Queue *q);

#endif
