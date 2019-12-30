#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <time.h>


typedef struct node{
  /* data */
  int val;
  struct node *next;
}node_t;

const maxQueue = 10;

void enqueue(node_t **head){
  
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

node_t * head = NULL;


int main() {
  char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\nGoodbye, world~~~~~!\r\n";
  long strSize = sizeof(response);
  // node_t * head = NULL;
  int ret;

  srand(time(NULL));
  enqueue(&head);
  enqueue(&head);
  enqueue(&head);
  enqueue(&head);
  
  print_list(head);

  // while ( (ret=dequeue(&head)) > 0 ) {
  //   printf("dequeued %d\n", ret);
  // }
  // printf ("Done, head=%p\n",head);

  int data = dequeue(&head);
  printf("------\n");
  printf("%d\n",data);
  
  return 0;
}