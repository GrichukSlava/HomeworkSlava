//
// Created by 79690 on 11.08.2023.
//
//очередь список
#include <stdio.h>
#include <stdlib.h>
// Очередь - список

struct Item{
    int val;
    struct Item *next;
};

struct QueueList {
    struct Item *head;
    struct Item *tail;
} ;


int push( struct QueueList* queue, int element){
    if( queue == NULL){
        return 1;
    }
    struct Item *curr = (struct Item*) malloc( 1 * sizeof(struct Item));
    curr->val = element;
    if(queue->tail == NULL){
        queue->tail = curr;
        queue->head = curr;
    }else{
        queue->tail->next = curr;
        queue->tail = queue->tail->next;
        curr->next = queue->head;

    }
    return 0;
}

int pop( struct QueueList* queue, int *element){
    if(queue == NULL ) {
        return -1;
    }
    if(queue->head == NULL ) {
        return -2;
    }
    struct Item* curr = queue->head;
    queue->head = queue->head->next;
    queue->tail->next = queue->head;
    curr->next = NULL;
    *element = curr->val;
    free(curr);

    return 0;
}


void printQueue(struct QueueList *queue) {
    struct Item *item = queue->head;
    do {
        printf("%d ", item->val);
        item = item->next;
    } while (item != queue->head);

}

int main(void) {

    int el = 13;
    int el1 = 10;
    struct QueueList *queue = (struct QueueList *) calloc(1,sizeof(struct QueueList ));
    push(queue, 10);
    push(queue, 13);
    push(queue, 5);
    printQueue(queue);
    int k;
    printf("\n");
    k = pop(queue, &el);
    printf("%d\n", k);
    printf("%d\n", el);
    printQueue(queue);
    return 0;
}