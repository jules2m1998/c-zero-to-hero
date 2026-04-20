#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  struct node *next;
};

struct node *list_append(struct node *head, int value);
void list_print(struct node *head);
void list_free(struct node *head);

int main(void) {
  struct node head = {.value = 10, .next = NULL};
  list_append(&head, 1);
  list_print(&head);

  list_append(&head, 2);
  list_print(&head);

  list_append(&head, 2);
  list_print(&head);

  list_append(&head, 3);
  list_print(&head);

  list_append(&head, 27);
  list_print(&head);

  list_free(head.next);
  head.next = NULL;
  list_print(&head);

  return 0;
}

struct node *list_append(struct node *head, int value) {
  struct node *current = head;
  if (head == NULL) {
    return NULL;
  }
  while (current->next != NULL) {
    current = current->next;
  }
  struct node *new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    fprintf(stderr, "Something wrong happened !\n");
    return NULL;
  }

  new_node->value = value;
  new_node->next = NULL;

  current->next = new_node;

  return new_node;
}

void list_print(struct node *head) {
  struct node *current = head;
  while (current != NULL) {
    printf("%d -> ", current->value);
    current = current->next;
  }
  printf("NULL\n");
}

void list_free(struct node *head) {
  if (head == NULL) {
    return;
  }
  struct node *next = head->next;
  list_free(next);
  free(head);
}
