#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[50];
    char value;
    int scope;
} character;

int char_capacity = 1;
int char_size = 0;
character *char_loc = NULL;

// Function to initialize storage
void init_char_storage() {
    char_loc = (character*)malloc(char_capacity * sizeof(character));
    if (char_loc == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Function to resize storage when needed
void increase_char_capacity() {
    char_capacity *= 2;
    character* temp = (character*)realloc(char_loc, char_capacity * sizeof(character));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    char_loc = temp;
}

// Function to add a new character variable
void add_char_variable(char *name, char value, int scope) {
   // Check if a variable with the same name and scope exists
    /* for (int i = 0; i < size; i++) {
        if (strcmp(int_loc[i].name, name) == 0 && int_loc[i].scope == scope) {
            printf("Error: Variable %s already exists in scope %d!\n", name, scope);
            return;
        }
    }*/
    if (char_size == char_capacity) {
        increase_char_capacity();
    }
    strcpy(char_loc[char_size].name, name);
    char_loc[char_size].value = value;
    char_loc[char_size].scope = scope;
    char_size++;
}
character* get_char_variable(char *name) { // only for one
    /*character* get_char_variable(char *name, int scope) {
    character* latest = NULL;
    for (int i = 0; i < char_size; i++) {
        if (strcmp(char_loc[i].name, name) == 0 && char_loc[i].scope <= scope) {
            if (latest == NULL || char_loc[i].scope > latest->scope) {
                latest = &char_loc[i];  // Keep track of latest scope match
            }
        }
    }
    return latest;
}
*/
    for (int i = 0; i < char_size; i++) {
        if (strcmp(char_loc[i].name, name) == 0) {
            return &char_loc[i];
        }
    }
    return NULL;
}
// Function to update the value of an existing character variable
void update_char_variable(char *name, char new_value) {
    for (int i = 0; i < char_size; i++) {
        if (strcmp(char_loc[i].name, name) == 0) {
            char_loc[i].value = new_value;
            printf("Updated %s to %c\n", name, new_value);
            return;
        }
    }
    printf("Character variable %s not found.\n", name);
}

// Function to print a character variable
void print_char_variable(char *name) {
    for (int i = 0; i < char_size; i++) {
        if (strcmp(char_loc[i].name, name) == 0) {
            printf("Variable %s = %c\n", name, char_loc[i].value);
            return;
        }
    }
    printf("Character variable %s not found.\n", name);
}

// Relational Operators for Characters
int char_equals(char a, char b) { return a == b; }
int char_not_equals(char a, char b) { return a != b; }
int char_greater_than(char a, char b) { return a > b; }
int char_less_than(char a, char b) { return a < b; }
int char_greater_equals(char a, char b) { return a >= b; }
int char_less_equals(char a, char b) { return a <= b; }

// Additional Character Functions
char to_uppercase(char c) { return toupper(c); }
char to_lowercase(char c) { return tolower(c); }
int is_digit(char c) { return isdigit(c); }
int is_letter(char c) { return isalpha(c); }
int is_whitespace(char c) { return isspace(c); }
//more functions
int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}
int is_consonant(char c) {
    return is_letter(c) && !is_vowel(c);
}
int is_punctuation(char c) {
    return ispunct(c);
}
char toggle_case(char c) {
    if (isupper(c)) return tolower(c);
    if (islower(c)) return toupper(c);
    return c;
}
int char_to_int(char c) {
    return is_digit(c) ? c - '0' : -1;  // Returns -1 if not a digit
}
char int_to_char(int n) {
    return (n >= 0 && n <= 9) ? '0' + n : '\0';  // Returns null character if out of range
}
int get_ascii_value(char c) {
    return (int)c;
}


// Function to delete a specific character variable
void delete_char_variable(char *name) {
    int new_size = 0;
    for (int i = 0; i < char_size; i++) {
        if (strcmp(char_loc[i].name, name) != 0) {
            char_loc[new_size] = char_loc[i];
            new_size++;
        }
    }
    if (new_size == char_size) {
        printf("Character variable %s not found.\n", name);
    } else {
        char_size = new_size;
        printf("Deleted character variable %s.\n", name);
    }
}

// Function to free all allocated memory for characters
void free_char_memory() {
    free(char_loc);
    char_loc = NULL;
    char_size = 0;
    char_capacity = 1;
    printf("All character memory has been freed.\n");
}
void free_variable_by_scope(int scope) {
    int new_size = 0;
    for (int i = 0; i < char_size; i++) {
        if (char_loc[i].scope != scope) {
            char_loc[new_size] = char_loc[i];
            new_size++;
        }
    }
    char_size = new_size;
    printf("Freed variables with scope %d.\n", scope);
}
// Function to display stored character variables
void display_char_variables() {
    if (char_size == 0) {
        printf("No character variables stored.\n");
        return;
    }
    for (int i = 0; i < char_size; i++) {
        printf("Name: %s, Value: %c, Scope: %d\n", char_loc[i].name, char_loc[i].value, char_loc[i].scope);
    }
}
void read_char_variable(char *name, int scope) {
    char value;
    printf("Enter value for %s: ", name);
    scanf(" %c", &value); // Space before %c to consume any trailing newline
    add_char_variable(name, value, scope);
}

// Main function to test character storage
int main() {
    init_char_storage();  // Initialize storage

    add_char_variable("ch1", 'A', 1);
    add_char_variable("ch2", 'b', 2);
    add_char_variable("ch3", '9', 1);

    display_char_variables();

    // Testing relational operators
    printf("ch1 == ch2: %d\n", char_equals(get_char_variable("ch1")->value, get_char_variable("ch2")->value));
    printf("ch1 > ch2: %d\n", char_greater_than(get_char_variable("ch1")->value, get_char_variable("ch2")->value));

    // Testing additional functions
    printf("Uppercase of ch2: %c\n", to_uppercase(get_char_variable("ch2")->value));
    printf("Lowercase of ch1: %c\n", to_lowercase(get_char_variable("ch1")->value));
    printf("Is ch3 a digit? %d\n", is_digit(get_char_variable("ch3")->value));

    printf("\nDeleting 'ch2'...\n");
    delete_char_variable("ch2");
    display_char_variables();

    printf("\nFreeing variables with scope 1...\n");
    free_variable_by_scope(1);
    display_char_variables();

    printf("\nFreeing all memory...\n");
    free_char_memory();

    return 0;
}
