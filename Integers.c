#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int value;
    int scope;
} integer;

// int capacity = 1;  // Initial storage capacity
// int size = 0;  // Number of currently stored variables
// integer *int_loc = NULL; // Pointer to dynamically allocated array

// Function to initialize storage
integer* int_init_storage(integer *int_loc, int capacity) {
    int_loc = (integer*)malloc(capacity*sizeof(integer));
    if (int_loc==NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return int_loc;
}

// Function to resize storage when needed
integer* int_increase_capacity(integer *int_loc, int capacity) {
    capacity *= 2;
    integer* temp = (integer*)realloc(int_loc, capacity * sizeof(integer));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    int_loc = temp;
}

// Function to add a new integer variable
integer* int_add_variable(char *name, int value, int scope, integer *int_loc, int size, int capacity) {
     // Check if a variable with the same name and scope exists
    /* for (int i = 0; i < size; i++) {
        if (strcmp(int_loc[i].name, name) == 0 && int_loc[i].scope == scope) {
            printf("Error: Variable %s already exists in scope %d!\n", name, scope);
            return;
        }
    }*/
    if (size == capacity) {
        int_increase_capacity(int_loc, capacity);
    }
    strcpy(int_loc[size].name, name);
    int_loc[size].value = value;
    int_loc[size].scope = scope;
    size++;
}
integer* int_get_variable(char *name, integer *int_loc, int size) {//only for one
   /*integer* get_variable(char *name, int scope) {
    integer* latest = NULL;
    for (int i = 0; i < size; i++) {
        if (strcmp(int_loc[i].name, name) == 0 && int_loc[i].scope <= scope) {
            if (latest == NULL || int_loc[i].scope > latest->scope) {
                latest = &int_loc[i];  // Keep track of latest scope match
            }
        }
    }
    return latest;
}
*/
    for (int i = 0; i < size; i++) {
        if (strcmp(int_loc[i].name, name) == 0) {
            return &int_loc[i];
        }
    }
    return NULL;
}
//arithmetic
int int_add(int a, int b) { return a + b; }
int int_subtract(int a, int b) { return a - b; }
int int_multiply(int a, int b) { return a * b; }
int int_divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0;
    }
    return a / b;
}
int int_modulus(int a, int b) { return a % b; }
int int_power(int a, int b) 
{ 
    int pow=1;
    for(int i=1;i<=b;i++)
    {
        pow=pow*a;
    }
    return pow;
}
int int_absolute(int a) { return abs(a); }
//logical
int int_logical_and(int a, int b) { return a && b; }
int int_logical_or(int a, int b) { return a || b; }
int int_logical_not(int a) { return !a; }
//relational
int int_equals(int a, int b) { return a == b; }
int int_not_equals(int a, int b) { return a != b; }
int int_greater_than(int a, int b) { return a > b; }
int int_less_than(int a, int b) { return a < b; }
int int_greater_equals(int a, int b) { return a >= b; }
int int_less_equals(int a, int b) { return a <= b; }
//more functions
int int_factorial(int n) {
    if (n < 0) return -1; // Undefined for negative numbers
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}
int int_gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int int_lcm(int a, int b) {
    return (a * b) / gcd(a, b); // LCM * GCD = a * b
}
int int_is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
int int_is_perfect_square(int n) {
    int i = 0;
    while (i * i <= n) {
        if (i * i == n) return 1;
        i++;
    }
    return 0;
}
int int_reverse_integer(int n) {
    int reversed = 0;
    while (n != 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return reversed;
}
int int_count_digits(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n != 0) {
        count++;
        n /= 10;
    }
    return count;
}
int int_sum_of_digits(int n) {
    int sum = 0;
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// Function to read an integer value from the user
integer* int_read_variable(char *name, int scope, integer *int_loc, int size, int capacity) {
    int value;
    printf("Enter value for %s: ", name);
    scanf("%d", &value);
    int_add_variable(name, value, scope, int_loc, size, capacity);
}

// Function to print the value of a specific variable
void int_print_variable(char *name, integer *int_loc, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(int_loc[i].name, name) == 0) {
            printf("Variable %s = %d\n", name, int_loc[i].value);
            return;
        }
    }
    printf("Variable %s not found.\n", name);
}

// Function to update the value of an existing variable
integer* int_update_variable(char *name, int new_value, integer *int_loc, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(int_loc[i].name, name) == 0) {
            int_loc[i].value = new_value;
            printf("Updated %s to %d\n", name, new_value);
            return;
        }
    }
    printf("Variable %s not found.\n", name);
}

// Function to delete a specific variable by name
integer* int_delete_variable(char *name, integer *int_loc, int size) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(int_loc[i].name, name) != 0) {
            int_loc[new_size] = int_loc[i];
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
void int_free_variables(int scope, integer *int_loc, int size) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (int_loc[i].scope != scope) {
            int_loc[new_size] = int_loc[i];
            new_size++;
        }
    }
    size = new_size;
    printf("Variables with scope %d have been removed.\n", scope);
}

// Function to free all allocated memory
void int_free_all_memory(integer *int_loc, int size, int capacity) {
    free(int_loc);
    int_loc = NULL;
    size = 0;
    capacity = 1;
    printf("All memory has been freed.\n");
}

// Function to display stored variables
integer* int_display_variables(integer *int_loc, int size) {
    if (size == 0) {
        printf("No variables stored.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Value: %d, Scope: %d\n", int_loc[i].name, int_loc[i].value, int_loc[i].scope);
    }
}

// int main() {
//     init_storage();  // Initialize memory storage

//     add_variable("x", 10, 1);
//     add_variable("y", 20, 1);
//     add_variable("z", 30, 2);

//     display_variables();

//     printf("\nUpdating 'x'...\n");
//     update_variable("x", 50);
//     print_variable("x");

//     printf("\nReading a new variable...\n");
//     read_variable("w", 3);
//     display_variables();
//     printf("\nDeleting 'y'...\n");
//     delete_variable("y");
//     display_variables();
   
//     add_variable("x", 10, 1);
//     add_variable("y", 20, 1);
//     add_variable("z", 30, 2);//scope handling needed(accepts same variable name and scope)
    
//     display_variables();
    
//     integer *x = get_variable("x");
//     integer *y = get_variable("y");
//     if (x && y) {
//         //Arithmetic
//         printf("Addition: %d\n", add(x->value, y->value));
//         printf("Subtraction: %d\n", subtract(x->value, y->value));
//         printf("Multiplication: %d\n", multiply(x->value, y->value));
//         printf("Division: %d\n", divide(x->value, y->value));
//         printf("Modulus: %d\n", modulus(x->value, y->value));
//         printf("Power: %d\n", power(x->value, 2));
//         printf("Absolute of -5: %d\n", absolute(-5));
//         //Relational
//         printf("Equals: %d\n", equals(x->value, y->value));
//         printf("Not Equals: %d\n", not_equals(x->value, y->value));
//         printf("Greater Than: %d\n", greater_than(x->value, y->value));
//         printf("Less Than: %d\n", less_than(x->value, y->value));
//         printf("Greater or Equal: %d\n", greater_equals(x->value, y->value));
//         printf("Less or Equal: %d\n", less_equals(x->value, y->value));
//         //logical
//         printf("AND (1 and 0): %d\n", logical_and(1, 0));
//         printf("OR (1 or 0): %d\n", logical_or(1, 0));
//         printf("NOT (1): %d\n", logical_not(1));
//     }
//     printf("\nFreeing variables with scope 1...\n");
//     free_variables(1);
//     display_variables();

//     printf("\nFreeing all memory...\n");
//     free_all_memory();

//     return 0;
// }
// ~Ishita