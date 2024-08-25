#include "PatientQueue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "patient.h"



//Criar fila
Queue* create_queue_patient()
{
  Queue *q = (Queue *)malloc(sizeof(Queue)); 
   q->inicio = q->final = NULL;                 
   return q;
}

//Liberar a memória da fila
void q_free_patient(Queue *q)
{
   QueueNode *p = q->inicio;
   while (p != NULL)
   {
      QueueNode *t = p->next; 
      free(p);                
      p = t;                  
   }
   free(q); 
}

//verificar se a fila esta vazia
int q_is_empty_patient(Queue *q)
{
   return q->inicio == NULL;
}

//Adicionar paciente na fila
Patient* enqueue_patient(Queue *q, Patient *p)
{
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode)); // aloca a memoria para o no de um paciente
   node->patient = p;
   node->next = NULL;

   if (q_is_empty_patient(q))
      q->inicio = node;
   else
      q->final->next = node;

   q->final = node;
}

//Remove e retorna o primeiro paciente da fila
Patient* q_dequeue_patient(Queue *q)
{
   assert(!q_is_empty_patient(q));

   Patient *p = q->inicio->patient;
   QueueNode *node = q->inicio; // Store for removal

   if (q->inicio != q->final)
      q->inicio = q->inicio->next;
   else
      q->inicio = q->final = NULL;

   free(node);
   return p;
}


void q_print_patient(Queue *q) {
   for (QueueNode *node = q->inicio; node != NULL; node = node->next) {
      char time_buffer[80]; // Buffer for formatted time string
      strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", node->patient->timestamp); // Format time
      printf("Paciente ID: %d, Nome: %s, Horario de chegada: %s\n", 
             node->patient->id, node->patient->name, time_buffer); 
   }
   printf("\n");
}

int quantidade_pacientes(Queue *q) {
   int count = 0;
   for (QueueNode *node = q->inicio; node != NULL; node = node->next) {
      count++;
   }
   return count;
}
