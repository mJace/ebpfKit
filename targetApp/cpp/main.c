#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>


typedef struct node{
  int val;
  struct node *next;
}node_t;

const int maxQueue = 10;

int queue_size(node_t *head) {
  node_t *current = head;
  int size = 0;
  while (current != NULL) {
    // printf("%d\n", current->val);
    size++;
    current = current->next;
  }
  return size;
}

void enqueue(node_t **head) {
  if ( ( queue_size(*head) ) == maxQueue ) {
    return;
  }
  int r = rand()%100;
  node_t *new_node = malloc(sizeof(node_t));
  if (!new_node) {
    return;
  }
  new_node->val = r;
  new_node->next = *head;
  *head = new_node;
}

int dequeue(node_t **head) {
  node_t *current, *prev = NULL;
  int retval = -1;

  if (*head ==NULL) return -1;

  current = *head;
  while (current->next != NULL) {
    prev = current;
    current = prev->next;
  }

  retval = current-> val;
  free(current);

  if (prev) {
    prev->next = NULL;
  }else{
    *head = NULL;
  }
  return retval;
}

void print_list(node_t *head) {
  node_t *current = head;

  while (current != NULL) {
    printf("%d\n", current->val);
    current = current->next;
  }
}

void *producer_func(void *input){

  int r = rand()%5;
  while (1){
    enqueue((node_t **)input);
    sleep(r);
  }
}

void *consumer_func(void *input) {
  int r = rand()%5;
  while (1) {
    dequeue((node_t **)input);
    sleep(r);
  }
}

node_t * head = NULL;


int main() {

  srand(time(NULL));
  pthread_t producer_1, producer_2, producer_3, producer_4;
  pthread_t consumer_1, consumer_2, consumer_3, consumer_4;

  pthread_create(&producer_1, NULL, &producer_func, &head);
  pthread_create(&producer_2, NULL, &producer_func, &head);
  pthread_create(&producer_3, NULL, &producer_func, &head);
  pthread_create(&producer_4, NULL, &producer_func, &head);

  pthread_create(&consumer_1, NULL, &consumer_func, &head);
  pthread_create(&consumer_2, NULL, &consumer_func, &head);
  pthread_create(&consumer_3, NULL, &consumer_func, &head);
  pthread_create(&consumer_4, NULL, &consumer_func, &head);
  

  while( 1 ) {
    print_list(head);
    sleep(1);
    printf("Queue size:%d\n",queue_size(head));
  }
  
  return 0;
}