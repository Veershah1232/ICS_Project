#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Include for string functions

#define MAX_LENGTH 50 // Maximum length for variable names

// Structure to represent a boolean variable
struct boolean {
    char name[MAX_LENGTH]; // Name of the variable
    int value; // Boolean value (0 or 1)
    int scope; // Scope of the variable
};

// int capacity = 1;  // Initial storage capacity
// int size = 0;  // Number of currently stored variables
// struct boolean *bool_loc = NULL; // Pointer to dynamically allocated array

// Function to initialize storage
void bool_init_storage(struct boolean *bool_loc, int capacity) {
    bool_loc = (struct boolean*)malloc(capacity * sizeof(struct boolean));
    if (bool_loc == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Function to double the storage capacity
void bool_increase_capacity(struct boolean *bool_loc, int capacity) {
    capacity *= 2;
    struct boolean* temp = (struct boolean*)realloc(bool_loc, capacity * sizeof(struct boolean));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    bool_loc = temp;
}

// Function to add a new boolean variable
void bool_add_variable(char *name, int value, int scope, struct boolean *bool_loc, int size, int capacity) {
    // Ensure value is either 0 or 1
    if (value != 0 && value != 1) {
        printf("Error: Boolean values must be 0 or 1.\n");
        return;
    }

    // Check if a variable with the same name and scope exists
    for (int i = 0; i < size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0 && bool_loc[i].scope == scope) {
            printf("Error: Variable %s already exists in scope %d!\n", name, scope);
            return;
        }
    }

    // Increase capacity if needed
    if (size == capacity) {
        bool_increase_capacity(bool_loc, capacity);
    }

    // Add new variable
    strcpy(bool_loc[size].name, name);
    bool_loc[size].value = value;
    bool_loc[size].scope = scope;
    size++;
}

// Function to get a variable by name
struct boolean* get_variable(char *name, struct boolean *bool_loc, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0) {
            return &bool_loc[i];
        }
    }
    return NULL;
}

// Logical operations for boolean values
bool or(bool a, bool b) { return (a || b); }
bool and(bool a, bool b) { return (a && b); }
bool not(bool a) { return (!a); }
bool nor(bool a, bool b) { return (!(a || b)); }
bool nand(bool a, bool b) { return !(a && b); }
bool xor(bool a, bool b) { return (((!a) && b) || ((!b) && a)); }
bool xnor(bool a, bool b) { return !xor(a, b); }

// Function to read a boolean value from the user
void bool_read_variable(char *name, int scope, struct boolean *bool_loc, int size, int capacity) {
    int value;
    printf("Enter boolean value (0 or 1) for %s: ", name);
    scanf("%d", &value);

    // Validate input
    if (value != 0 && value != 1) {
        printf("Invalid input. Only 0 or 1 are allowed.\n");
        return;
    }

    bool_add_variable(name, value, scope, bool_loc, size, capacity);
}

// Function to print the value of a specific variable
void bool_print_variable(char *name, struct boolean *bool_loc, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0) {
            printf("Variable %s = %d\n", name, bool_loc[i].value);
            return;
        }
    }
    printf("Variable %s not found.\n", name);
}

// Function to update the value of an existing variable
void bool_update_variable(char *name, int new_value, struct boolean *bool_loc, int size) {
    if (new_value != 0 && new_value != 1) {
        printf("Error: Boolean values must be 0 or 1.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0) {
            bool_loc[i].value = new_value;
            printf("Updated %s to %d\n", name, new_value);
            return;
        }
    }
    printf("Variable %s not found.\n", name);
}

// Function to delete a specific variable by name
void bool_delete_variable(char *name, struct boolean *bool_loc, int size) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(bool_loc[i].name, name) != 0) {
            bool_loc[new_size] = bool_loc[i];
            new_size++;
        }
    }
    if (new_size == size) {
        printf("Variable %s not found.\n", name);
    } else {
        size = new_size;
        printf("Deleted variable %s.\n", name);
    }
}

// Function to free memory allocated for variables of a specific scope
void bool_free_variables(int scope, int size, struct boolean *bool_loc) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (bool_loc[i].scope != scope) {
            bool_loc[new_size] = bool_loc[i];
            new_size++;
        }
    }
    size = new_size;
    printf("Variables with scope %d have been removed.\n", scope);
}

// Function to free all allocated memory
void bool_free_all_memory(struct boolean *bool_loc, int size, int capacity) {
    free(bool_loc);
    bool_loc = NULL;
    size = 0;
    capacity = 1;
    printf("All memory has been freed.\n");
}

// Function to display all stored variables
void bool_display_variables(int size, struct boolean *bool_loc) {
    if (size == 0) {
        printf("No variables stored.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Value: %d, Scope: %d\n", bool_loc[i].name, bool_loc[i].value, bool_loc[i].scope);
    }
}
