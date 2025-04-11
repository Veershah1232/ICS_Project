#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_VAR_LENGTH 1024
#define MAX_CHAR_VALUE 1024

struct treeNode{
    char type[20]; //stores the node type like assignment,declaration,etc
    char value[50]; //stores the value of the node
    struct treeNode* left; //point to the left branch in the tree
    struct treeNode* right; //point to the right branch in the tree
    struct treeNode* next; //next statement in the sequence
} treeNode;
//function to create a node for the tree
struct treeNode* createNode(char type[], char value[], struct treeNode* left, struct treeNode* right, struct treeNode* next) {
    struct treeNode* newNode = (struct treeNode*)malloc(sizeof(treeNode));
    if (newNode == NULL) {
        fprintf(stderr,"Memory Allocation Failed\n");
        exit(1);
    }
    strncpy(newNode->type,type,20);
    if (value) {
        strncpy(newNode->value,value,50);
    }
    else {
        newNode->value[0] = '\0';
    }
    newNode->left = left;
    newNode->right = right;
    newNode->next = next;

    return newNode;
}

typedef enum {
    PROGRAM,           // 0: Root node of the entire program
    STATEMENT_LIST,    // 1: A list of statements
    STATEMENT,         // 2: A single statement
    VAR_DEC,           // 3: Variable declaration
    ASSIGNMENT,        // 4: Variable assignment
    SHOW_STATEMENT,    // 5: Print/output statement
    ASK_STATEMENT,     // 6: Input/request from user
    LL_OPERATIONS,     // 7: Linked list operations
    IF_STATEMENT,      // 8: Conditional if-statement
    WHILE_LOOP,        // 9: While loop
    FOR_LOOP,          // 10: For loop
    NEXT_STATEMENT,    // 11: Loop continue statement
    LEAVE_STATEMENT,   // 12: Loop break statement
    BLOCK,             // 13: Block of statements (e.g., inside functions or control structures)
    FUNCTION_DEC,      // 14: Function declaration
    FUNCTION_CALL,     // 15: Function call
    RETURN_STATEMENT,  // 16: Return statement from function
    EXP,               // 17: Expression (arithmetic, boolean, etc.)
    PARAMETER,         // 18: Single function parameter
    PARAMETERS,        // 19: List of parameters
    ARGUMENTS          // 20: List of arguments passed to a function
} NodeType;

struct treeNode* gotonode(struct treeNode* root, struct treeNode* ptr, int depth){
    ptr = root;
    ptr = ptr->left;
    for (int i=0; i<depth-1; i++){
        ptr = ptr->next;
    }  
    return ptr; 
}

void executeTree(struct treeNode* root){

    NodeType type;
    struct treeNode* ptr = root;
    int current_depth=0;

    while (ptr != NULL) {
        if (strcmp(ptr->type, "PROGRAM") == 0) {
            // PROGRAM: Start of the program, go to statement list
            ptr = ptr->left;
        }
        else if (strcmp(ptr->type, "VAR_DEC") == 0) {
            if (strcmp(ptr->value, "IDENTIFIER")==0){
                if (strcmp(ptr->left, "exp")==0){
                    // check inside all the struct vectors if there is a variable name that matches
                    // return no 
                }
                else{
                    // write code for ll_get
                }
            }
            else{
                // ask how to handle statements
            }
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LIST_DEC") == 0) {
            // LIST_DEC: Declare a list with initial value from exp
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_DEC") == 0) {
            // LL_DEC: Declare a linked list
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "DICT_DEC") == 0) {
            // DICT_DEC: Declare a dictionary
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "SHOW") == 0) {
            // SHOW: Output string and values from exp_list
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "ASK") == 0) {
            // ASK: Input into variable(s) from user
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "ASSIGN") == 0) {
            // ASSIGN: Assign a value or perform linked list get
            // Handle assignment types (IDENTIFIER, INDEX, LL_GET)
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "IF") == 0) {
            // IF: Evaluate condition and execute block if true
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "IF-ELSE") == 0) {
            // IF-ELSE: Evaluate condition and execute correct block
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "WHILE") == 0) {
            // WHILE: Execute block while condition is true
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "FOR") == 0) {
            // FOR: Execute loop using loop info and block
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "NEXT") == 0) {
            // NEXT: Continue to next iteration of loop
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LEAVE") == 0) {
            // LEAVE: Break out of current loop
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "FUNC_DEC") == 0) {
            // FUNC_DEC: Store function definition for later calls
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "CALL") == 0) {
            // CALL: Call a function with arguments
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "RETURN") == 0) {
            // RETURN: Return a value from function
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SORT") == 0) {
            // LL_SORT: Sort a linked list
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SEARCH") == 0) {
            // LL_SEARCH: Search in linked list
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_INSERT") == 0) {
            // LL_INSERT: Insert into linked list
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SET") == 0) {
            // LL_SET: Set value at index in linked list
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_DEL") == 0) {
            // LL_DEL: Delete node from linked list
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "BLOCK") == 0) {
            // BLOCK: A set of statements, execute recursively
            executeTree(ptr->left); // block body
            ptr = ptr->next;
        }
        else {
            // Unknown node type or expression handling
            // Handle EXP, PARAMETER, ARGUMENTS, etc., if needed
            ptr = ptr->next;
        }
    }
    return 0;
}

    


