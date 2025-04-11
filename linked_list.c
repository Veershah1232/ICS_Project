#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure for each node of linked list
struct node {
    int value;
    struct node* ptr_next;
};

//struct for linked list 
typedef struct {
    char name[50];
    int length;
    struct node* head_ptr; //pointer to the head node
    struct node* tail_ptr; //pointer to the tail node
} linked_list;

//struct to create a vector to store the linked lists
typedef struct {
    linked_list** lists;
    int size;
    int capacity;
} linked_list_vector;

void initialise_vector(linked_list_vector** storage) {
    *storage = (linked_list_vector*)malloc(sizeof(linked_list_vector));
    if (*storage == NULL) {
        printf("Memory Allocation Failed.\n");
        return;
    }
    (*storage)->capacity = 1;
    (*storage)->size = 0;
    (*storage)->lists = (linked_list**)malloc(sizeof(linked_list*) * (*storage)->capacity);

    if ((*storage)->lists == NULL) {
        printf("Memory Allocation Failed\n");
        free(*storage);
        *storage = NULL;
        return;
    }
}

void initialise_and_add_list(linked_list_vector* vector, char* name, int length) {
    if (vector == NULL) {
        printf("Invalid vector pointer.\n");
        return;
    }

    // Allocate memory for the linked list
    linked_list* list = (linked_list*)malloc(sizeof(linked_list));
    if (list == NULL) {
        printf("Memory Allocation Failed for linked list.\n");
        return;
    }

    strncpy(list->name, name, sizeof(list->name) - 1);
    list->name[sizeof(list->name) - 1] = '\0';
    list->length = length;
    list->head_ptr = NULL;
    list->tail_ptr = NULL;

    // Initialize linked list nodes with value 0
    for (int i = 0; i < length; i++) {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        if (new_node == NULL) {
            printf("Memory Allocation Failed for node.\n");
            return;
        }

        new_node->value = 0;
        new_node->ptr_next = NULL;

        if (list->head_ptr == NULL) { // First node
            list->head_ptr = new_node;
            list->tail_ptr = new_node;
        } else {                        //append tail node for later nodes
            list->tail_ptr->ptr_next = new_node;
            list->tail_ptr = new_node;
        }
    }

    // Expand vector capacity if needed
    if (vector->size == vector->capacity) {
        vector->capacity *= 2;
        linked_list** temp = (linked_list**)realloc(vector->lists, sizeof(linked_list*) * vector->capacity);
        if (temp == NULL) {
            printf("Memory Allocation Failed while resizing vector.\n");
            free(list); // Prevent memory leak
            return;
        }
        vector->lists = temp;
    }

    // Add linked list to vector
    vector->lists[vector->size] = list;
    vector->size++;
}
//function to insert element at a given position
void insert_element(linked_list* list, int position, int value) {
    if (position < 0 || position > list->length) { //validating position
        printf("Invalid Position");
        return;
    }
    struct node* new_node = (struct node*)malloc(sizeof(struct node)); //creating the new node
    if (new_node == NULL) {
        printf("Memory Allocation Failed");
        return;
    }

    new_node->value = value;
    new_node->ptr_next = NULL;
    if (position == 0) { //if to be added at the beginning change the head pointer as well
        new_node->ptr_next = list->head_ptr;
        list->head_ptr = new_node;
        list->length = list->length + 1;
        return;
    }
    else if (position == list->length) { //if to be added at the end change the tail pointer
        list->tail_ptr->ptr_next = new_node;
        list->tail_ptr = new_node;
        list->length = list->length + 1;
        return;
    }
    else {
        struct node* temp = list->head_ptr; //temp struct to traverse through the list to get to the position needed
        for (int i = 0; i < position - 1 && temp!=NULL; i++) {
            temp = temp->ptr_next;
        }
        new_node->ptr_next = temp->ptr_next;
        temp->ptr_next = new_node;
        list->length = list->length + 1;
        return;
    }
}
//function to modify the value at a given position
void modify_value(linked_list* list, int position, int value) {
    
    if (position<0 || position >= list->length) { //validating position
        printf("Invalid Position");
        return;
    }
    
    struct node* temp = list->head_ptr; //temp struct to traverse through the linked list
    for (int i = 0; i < position; i++) {
        temp = temp->ptr_next;
    }
    temp->value = value;
    return;
}
//function to get the value at a given position
int read_node(linked_list* list, int position) {
    if (position<0 || position >= list->length) {
        printf("Invalid Position");
        return -1;
    }

    struct node* temp = list->head_ptr;
    for (int i = 0; i < position; i++) {
        temp = temp->ptr_next;
    }
    return temp->value;
}

void search_element(linked_list* list, int value) {
    struct node* temp = list->head_ptr;
    while(temp!=NULL) {
        if (value == temp->value) {
            printf("Element Found.\n");
            return;
        }
        temp = temp->ptr_next;
    }
    printf("Element not found.\n");
    return;
}

int get_First(linked_list* list, int value) {
    struct node* temp = list->head_ptr;
    int index = 0;
    while(temp!=NULL) {
        if (value == temp->value) {
            return index;
        }
        temp = temp->ptr_next;
        index++;
    }
    printf("Element not in list.\n");
    return -1;
}

//function to print the entire linked list
void print_values(linked_list* list) {
    struct node* temp = list->head_ptr;
    for (int i = 0; i < list->length; i++) {
        printf("%d -> ",temp->value);
        temp = temp->ptr_next;
    }
    printf("\n\n");
    return;
}

//function to print all the details of the list
void print_list(linked_list* list) {
    printf ("%s %d\n",list->name,list->length);
    print_values(list);
}

void sort_list(linked_list* list) {
    struct node* current = list->head_ptr;
    struct node* index = NULL;
    while (current != NULL) { //tried bubble sort kinda thing, it is not bubble sort but it works lol its some random sort method
        index = current->ptr_next;
        while (index != NULL) {
            if (current->value > index->value) {
                int temp = current->value;
                current->value = index->value;
                index->value = temp;
            }
            index = index->ptr_next;
        }
        current = current->ptr_next;
    }
}

//function to delete a specific node
void delete_node(linked_list* list,int position) {
    if (position < 0 || position >= list->length) {
        printf("Invalid position");
        return;
    }
    struct node* temp = list->head_ptr;

    if (position == 0) {
        list->head_ptr = temp->ptr_next;
        list->length = list->length - 1;
        if (list->length == 0) {
            list->tail_ptr = NULL;
        }
        free(temp);
        return;
    }
    for (int i = 0; i < position - 1; i++) {
        temp = temp->ptr_next;
    }
    struct node* delete_node = temp->ptr_next;
    temp->ptr_next = delete_node->ptr_next;

    if (delete_node->ptr_next == list->tail_ptr) {
        list->tail_ptr = temp;
    }
    list->length = list->length - 1;
    free(delete_node);
}
//function to delete the list itself
void delete_list(linked_list* list,linked_list_vector* storage) {
    if (list == NULL) {
        return;
    }
    struct node* temp = list->head_ptr;
    //freeing all the nodes of the list
    while(temp!=NULL) {
        struct node* next = temp->ptr_next;
        free(temp);
        temp = next;
    }
    for (int i = 0; i < storage->size; i++) {
        if (storage->lists[i] == list) {
            storage->lists[i] = NULL;
            break;
        }
    }
    free(list);
}

void empty_list(linked_list* list) {
    if (list == NULL) {
        return;
    }
    struct node* temp = list->head_ptr;
    //freeing all the nodes of the list
    while(temp!=NULL) {
        struct node* next = temp->ptr_next;
        free(temp);
        temp = next;
    }
    list->head_ptr = NULL;
    list->tail_ptr = NULL;
    list->length = 0;
}

void test_operations() {
    linked_list_vector* vector;
    initialise_vector(&vector);

    // Create and add linked lists
    initialise_and_add_list(vector, "List1", 5);
    initialise_and_add_list(vector, "List2", 3);

    for (int i = 0; i < vector->size; i++) {
        printf("%s: ", vector->lists[i]->name);
        print_list(vector->lists[i]);
    }

    // Insert elements
    insert_element(vector->lists[0], 2, 99);
    insert_element(vector->lists[1], 1, 42);

    // Modify values
    modify_value(vector->lists[0], 3, 88);
    modify_value(vector->lists[1], 0, 77);

    for (int i = 0; i < vector->size; i++) {
        printf("%s: ", vector->lists[i]->name);
        print_list(vector->lists[i]);
    }
    
    // Read values
    printf("Value at index 2 in List1: %d\n", read_node(vector->lists[0], 2));
    printf("Value at index 1 in List2: %d\n", read_node(vector->lists[1], 1));

    sort_list(vector->lists[0]);
    sort_list(vector->lists[1]);

    for (int i = 0; i < vector->size; i++) {
        printf("%s: ", vector->lists[i]->name);
        print_list(vector->lists[i]);
    }



    // Delete a node
    delete_node(vector->lists[0], 2);
    printf("List1 after deleting index 2: ");
    print_list(vector->lists[0]);

    // Delete entire list
    delete_list(vector->lists[1], vector);
    printf("List2 deleted.\n");

    // Cleanup
    delete_list(vector->lists[0], vector);
    free(vector->lists);
    free(vector);
    printf("Memory freed and program terminated.\n");
}


//Coded by Parrva Chirag Shah (B24CS1053)

