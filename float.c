#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float value;
    int scope;
} decimal;

int capacity = 1;  // Initial storage capacity
int size = 0;  // Number of currently stored variables
decimal *dec_loc = NULL; // Pointer to dynamically allocated array

// Function to initialize storage
void init_storage() {
    dec_loc = (decimal*)malloc(capacity*sizeof(decimal));
    if (dec_loc==NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Function to resize storage when needed
void increase_capacity() {
    capacity *= 2;
    decimal* temp = (decimal*)realloc(dec_loc, capacity * sizeof(decimal));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    dec_loc = temp;
}

// Function to add a new decimal variable
void add_variable(char *name, float value, int scope) {
     // Check if a variable with the same name and scope exists
    for (int i = 0; i < size; i++) {
        if (strcmp(dec_loc[i].name, name) == 0 && dec_loc[i].scope == scope) {
            printf("Error: Variable %s already exists in scope %d!\n", name, scope);
            return;
        }
    }
    if (size == capacity) {
        increase_capacity();
    }
    strcpy(dec_loc[size].name, name);
    dec_loc[size].value = value;
    dec_loc[size].scope = scope;
    size++;
}
decimal* get_variable(char *name) {//only for one
   /*decimal* get_variable(char *name, int scope) {
    decimal* latest = NULL;
    for (int i = 0; i < size; i++) {
        if (strcmp(dec_loc[i].name, name) == 0 && dec_loc[i].scope <= scope) {
            if (latest == NULL || dec_loc[i].scope > latest->scope) {
                latest = &dec_loc[i];  // Keep track of latest scope match
            }
        }
    }
    return latest;
}
*/
    for (int i = 0; i < size; i++) {
        if (strcmp(dec_loc[i].name, name) == 0) {
            return &dec_loc[i];
        }
    }
    return NULL;
}
//arithmetic
float add(float a, float b) { return a + b; }
float subtract(float a, float b) { return a - b; }
float multiply(float a, float b) { return a * b; }
float divide(float a, float b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0;
    }
    return a / b;
}
//float modulus(float a, float b) { return a % b; }
float power(float a, float b) 
{ 
    float pow=1;
    for(int i=1;i<=b;i++)
    {
        pow=pow*a;
    }
    return pow;
}
float absolute(float a) { return abs(a); }

//relational
float equals(float a, float b) { return a == b; }
float not_equals(float a, float b) { return a != b; }
float greater_than(float a, float b) { return a > b; }
float less_than(float a, float b) { return a < b; }
float greater_equals(float a, float b) { return a >= b; }
float less_equals(float a, float b) { return a <= b; }
//more functions
// int is_perfect_square(int n) {
//     int i = 0;
//     while (i * i <= n) {
//         if (i * i == n) return 1;
//         i++;
//     }
//     return 0;
// }

// float count_digits(float n) {
//     if (n == 0) return 1;
//     int count = 0;
//     while (n != 0) {
//         count++;
//         n /= 10;
//     }
//     return count;
// }

// int sum_of_digits(int n) {
//     int sum = 0;
//     while (n != 0) {
//         sum += n % 10;
//         n /= 10;
//     }
//     return sum;
// }

// Function to read an decimal value from the user
void read_variable(char *name, int scope) {
    float value;
    printf("Enter value for %s: ", name);
    scanf("%f", &value);
    add_variable(name, value, scope);
}

// Function to print the value of a specific variable
void print_variable(char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dec_loc[i].name, name) == 0) {
            printf("Variable %s = %f\n", name, dec_loc[i].value);
            return;
        }
    }
    printf("Variable %s not found.\n", name);
}

// Function to update the value of an existing variable
void update_variable(char *name, float new_value) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dec_loc[i].name, name) == 0) {
            dec_loc[i].value = new_value;
            printf("Updated %s to %f\n", name, new_value);
            return;
        }
    }
    printf("Variable %s not found.\n", name);
}

// Function to delete a specific variable by name
void delete_variable(char *name) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(dec_loc[i].name, name) != 0) {
            dec_loc[new_size] = dec_loc[i];
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
void free_variables(int scope) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (dec_loc[i].scope != scope) {
            dec_loc[new_size] = dec_loc[i];
            new_size++;
        }
    }
    size = new_size;
    printf("Variables with scope %f have been removed.\n", scope);
}

// Function to free all allocated memory
void free_all_memory() {
    free(dec_loc);
    dec_loc = NULL;
    size = 0;
    capacity = 1;
    printf("All memory has been freed.\n");
}

// Function to display stored variables
void display_variables() {
    if (size == 0) {
        printf("No variables stored.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Value: %f, Scope: %d\n", dec_loc[i].name, dec_loc[i].value, dec_loc[i].scope);
    }
}

int main() {
    init_storage();  // Initialize memory storage

    add_variable("x", 10.5, 1);
    add_variable("y", 20.2, 1);
    add_variable("z", 30.452, 2);

    display_variables();

    printf("\nUpdating 'x'...\n");
    update_variable("x", 50.12312);
    print_variable("x");

    printf("\nReading a new variable...\n");
    read_variable("w", 3.34232);
    display_variables();
    printf("\nDeleting 'y'...\n");
    delete_variable("y");
    display_variables();
   
    add_variable("x", 10, 1);
    add_variable("y", 20, 1);
    add_variable("z", 30, 2); //scope handling needed(accepts same variable name and scope)
    
    display_variables();
    
    decimal *x = get_variable("x");
    decimal *y = get_variable("y");
    if (x && y) {
        //Arithmetic
        printf("Addition: %f\n", add(x->value, y->value));
        printf("Subtraction: %f\n", subtract(x->value, y->value));
        printf("Multiplication: %f\n", multiply(x->value, y->value));
        printf("Division: %f\n", divide(x->value, y->value));
        printf("Power: %f\n", power(x->value, 2));
        printf("Absolute of -5: %f\n", absolute(-5));
        //Relational
        printf("Equals: %d\n", equals(x->value, y->value));
        printf("Not Equals: %d\n", not_equals(x->value, y->value));
        printf("Greater Than: %d\n", greater_than(x->value, y->value));
        printf("Less Than: %d\n", less_than(x->value, y->value));
        printf("Greater or Equal: %d\n", greater_equals(x->value, y->value));
        printf("Less or Equal: %d\n", less_equals(x->value, y->value));
    }
    printf("\nFreeing variables with scope 1...\n");
    free_variables(1);
    display_variables();

    printf("\nFreeing all memory...\n");
    free_all_memory();

    return 0;
}
// ~Ishat