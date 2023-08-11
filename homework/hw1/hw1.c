#include <stdio.h>
#include <stdlib.h>
struct Item {
    int val;
    struct Item *next;
};


int ordered_list( struct Item *head) {
    if( head->next == NULL || head == NULL){
        return -1;
    }
    struct Item *prev = head;
    struct Item *curr = head->next;
    while (curr != NULL) {
        if (prev->val > curr->val) {
            return -1;
        }
        prev = prev->next;
        curr = curr->next;
        }
    return 1;
}


int main() {
    struct Item *item1 =  malloc(sizeof(struct Item));
    item1->val = 1;
    item1->next = NULL;

    int res = ordered_list(item1);
    printf("ответ -%d", res );
    return 0;
}

