#include <stdio.h>
#include <stdlib.h>

struct node{
    struct node* next_node;
    int data;
};

struct linked_list{
    struct node* head;
    int length;
};

void print_list(struct linked_list* list){
    printf("Here is your list of length %d:\n", list->length);
    struct node* current = list->head;
    for (int i = 0; i < list->length; i++){
        printf("%d ", current->data);
        current = current->next_node;
    }
    printf("\n");
}

void insert_node(struct linked_list* list, int position, int data){
    if (position > list->length || position < 0){
        printf("Unsuccessful insertion : index out of range\n");
    } else {
        struct node* prev = NULL;
        struct node* cur = list->head;
        for (int i = 0; i < position; i++){
            prev = cur;
            cur = cur->next_node;
        }
        struct node* node1 = malloc(sizeof(struct node));
        node1->data = data;
        node1->next_node = cur;
        if (position == 0){
            list->head = node1;
        } else {
            prev->next_node = node1;
        }
        list->length++;
        printf("Successeful insertion of %d\n", data);
    }
}

void delete_node(struct linked_list* list, int position){
    if (list->length <= position || position < 0){
        printf("Unsuccessful deletion : index out of range\n");
    } else {
        struct node* prev = NULL;
        struct node* cur = list->head;
        for (int i = 0; i < position; i++){
            prev = cur;
            cur = cur->next_node;
        }
        if (position == 0){
            list->head = cur->next_node;
        } else {
            prev->next_node = cur->next_node;
        }  
        list->length--;
        printf("Successeful deletion of list [%d]\n", position);
    }
}

int main(){
    struct linked_list* mylist = malloc(sizeof(struct linked_list));
    mylist->length = 0;
    mylist->head = NULL;
    insert_node(mylist, 0, 1);
    insert_node(mylist, 1, 2);
    insert_node(mylist, 1, 3);
    insert_node(mylist, 3, 4);
    insert_node(mylist, 111, 4); // fails and not executes
    print_list(mylist);
    delete_node(mylist, 0);
    delete_node(mylist, 2);
    delete_node(mylist, 2); // fails and not executes
    delete_node(mylist, 0);
    delete_node(mylist, 0);
    print_list(mylist);
    insert_node(mylist, 0, 11);
    insert_node(mylist, 0, 123);
    print_list(mylist);
    /*
        Here is the output:
    Successeful insertion of 1
    Successeful insertion of 2
    Successeful insertion of 3
    Successeful insertion of 4
    Unsuccessful insertion : index out of range
    Here is your list of length 4:
    1 3 2 4 
    Successeful deletion of list [0]
    Successeful deletion of list [2]
    Unsuccessful deletion : index out of range
    Successeful deletion of list [0]
    Successeful deletion of list [0]
    Here is your list of length 0:
    Successeful insertion of 11
    Successeful insertion of 123
    Here is your list of length 2:
    123 11 
    */

    return 0;
}