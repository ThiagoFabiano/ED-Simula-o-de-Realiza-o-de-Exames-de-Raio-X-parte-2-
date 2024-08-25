#include "ExamPriorityQueue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "exam.h"

//Criar fila
QueueExam* create_queue_exam()
{
  QueueExam *q = (QueueExam *)malloc(sizeof(QueueExam)); 
   q->inicio = q->final = NULL;                 
   return q;
}

//Liberar a memória da fila
void q_free_exam(QueueExam *q)
{
   QueueNodeExam *p = q->inicio;
   while (p != NULL)
   {
      QueueNodeExam *t = p->next; 
      free(p);                
      p = t;                  
   }
   free(q); 
}

//verificar se a fila esta vazia
int q_is_empty_exam(QueueExam *q)
{
   return q->inicio == NULL;
}

//Adicionar exame na fila
Exam* enqueue_exam(QueueExam *q, Exam *e)
{
   QueueNodeExam *node = (QueueNodeExam *)malloc(sizeof(QueueNodeExam)); // aloca a memoria para o no de um exame
   printf("Aqui 5\n");
   node->exam = e;
   printf("Aqui 6\n");
   node->next = NULL;
   printf("Aqui 7\n");

   if (q->inicio == NULL || q->inicio->exam->nivel_gravidade < e->nivel_gravidade) 
   {
       printf("Aqui 8\n");
      node->next=q->inicio;
       printf("Aqui 9\n");
      q->inicio = node;
       printf("Aqui 10\n");
   } else {
       printf("Aqui 11\n");
      QueueNodeExam *current = q->inicio;
       printf("Aqui 12\n");
  
       printf("%d\n",  node);
       printf("%d\n",  q);
       printf("%d\n", q->final);
       printf("%d\n", q->final->next);
      q->final->next = node;
       printf("Aqui 13\n");

      while (current->next != NULL && current->next->exam->nivel_gravidade >= e->nivel_gravidade) {
          printf("Aqui 14\n");
         current = current->next;
          printf("Aqui 15\n");
      }
      node->next = current->next;
       printf("Aqui 16\n");
      current->next = node;
       printf("Aqui 17\n");
   }  
}

//Remove e retorna o primeiro exame da fila
Exam* dequeue_exam(QueueExam *q)
{
   if (q_is_empty_exam(q)) {
        return NULL;
    }

    QueueNodeExam *prioridade = q->inicio;
    Exam *exam = prioridade->exam;

    q->inicio = q->inicio->next;

    if (q->inicio == NULL) {
        q->final = NULL;
    }
    free(prioridade);

    return exam;
}


void q_print_exam(QueueExam *q) {
    for (QueueNodeExam *node = q->inicio; node != NULL; node = node->next) {
      char time_buffer[80]; // Buffer para armazenar a string formatada do tempo
      strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &(node->exam->timestamp)); // Formata o tempo
      printf("ID do Exame:%d\n",node->exam->id);
      printf("ID do Paciente:%d\n",node->exam->patient_id);
      printf("Nivel de Gravidade:%d\n",node->exam->nivel_gravidade);
      printf("Horario do Exame:%s\n",time_buffer);
    }
    printf("\n");
}

