#include "ExamPriorityQueue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "exam.h"

//Criar fila
Queue* create_queue_exam()
{
  Queue *q = (Queue *)malloc(sizeof(Queue)); 
   q->inicio = q->final = NULL;                 
   return q;
}

//Liberar a memória da fila
void q_free_exam(Queue *q)
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
int q_is_empty_exam(Queue *q)
{
   return q->inicio == NULL;
}

//Adicionar exame na fila
Exam* enqueue_exam(Queue *q, Exam *e)
{
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode)); // aloca a memoria para o no de um exame
   node->exam = e;
   node->next = NULL;

   if (q->inicio == NULL || q->inicio->exam->nivel_gravidade < e->nivel_gravidade) 
   {
      node->next=q->inicio;
      q->inicio = node;
   }

   else 
   {
      QueueNode *current = q->inicio;
      q->final->next = node;

      while (current->next != NULL && current->next->exam->nivel_gravidade >= e->nivel_gravidade) {
         current = current->next;
      }
      node->next = current->next;
      current->next = node;
   }  
}

//Remove e retorna o primeiro exame da fila
Exam* exam_dequeue(Queue *q)
{
   if (q_is_empty_exam(q)) {
        return NULL;
    }

    QueueNode *prioridade = q->inicio;
    Exam *exam = prioridade->exam;

    q->inicio = q->inicio->next;

    if (q->inicio == NULL) {
        q->final = NULL;
    }
    free(prioridade);

    return exam;
}


void q_print_exam(Queue *q) {
    for (QueueNode *node = q->inicio; node != NULL; node = node->next) {
      char time_buffer[80]; // Buffer para armazenar a string formatada do tempo
      strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &(node->exam->timestamp)); // Formata o tempo
      printf("ID do Exame:%d\n",node->exam->id);
      printf("ID do Paciente:%d\n",node->exam->patient_id);
      printf("Nivel de Gravidade:%d\n",node->exam->nivel_gravidade);
      printf("Horario do Exame:%s\n",time_buffer);
    }
    printf("\n");
}

