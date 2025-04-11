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

void executeTree(struct treeNode* root) {

    NodeType type;
    struct treeNode* ptr = root;
    int current_depth = 0;

    while (ptr != NULL) {
        if (strcmp(ptr->type, "PROGRAM") == 0) {
            ptr = ptr->left;
        }
        else if (strcmp(ptr->type, "VAR_DEC") == 0) {
            if (strcmp(ptr->value, "IDENTIFIER") == 0) {
                if (strcmp(ptr->left, "exp") == 0) {
                    // check inside all the struct vectors if there is a variable name that matches
                    // return no 
                } else {
                    // write code for ll_get
                }
            } else {
                // ask how to handle statements
            }
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LIST_DEC") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_DEC") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "DICT_DEC") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "SHOW") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "ASK") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "ASSIGN") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "IF") == 0) {
            ptr = ptr->left;
            executeTree(ptr);
            gotonode(root, ptr, current_depth);
            ptr = ptr->right;
            executeTree(ptr);
            gotonode(root, ptr, current_depth);
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "IF-ELSE") == 0) {
            // evaluate condition, then either left or right block
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "WHILE") == 0) {
            // use gotonode to loop while evaluating condition and executing block
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "FOR") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LOOP_INFO") == 0) {
            // used inside for loop, contains VAR and RANGE
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "RANGE") == 0) {
            // define start and end of range
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "NEXT") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LEAVE") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "FUNC_DEC") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "FUNC_DATA") == 0) {
            // contains parameters and return type
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "RET_TYPE") == 0) {
            // type returned by function
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "CALL") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "RETURN") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SORT") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SEARCH") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_INSERT") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SET") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_DEL") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_GET") == 0) {
            // used inside expressions or assignments
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "RBLOCK") == 0) {
            executeTree(ptr->right);
            gotonode(root, ptr, current_depth);
        }
        else if (strcmp(ptr->type, "LBLOCK") == 0) {
            executeTree(ptr->left);
            gotonode(root, ptr, current_depth);
        }
        else if (strcmp(ptr->type, "EXP") == 0) {
            // root of expression subtree
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "PARAMETER") == 0) {
            // single function parameter (IDENTIFIER and DATATYPE)
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "PARAMETERS") == 0) {
            // list of parameters
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "ARGUMENTS") == 0) {
            // list of arguments passed in a call
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "VAR") == 0) {
            // use of a variable
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "INDEX") == 0) {
            // access via index (e.g., list[i], dict[key])
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "ADDRESS") == 0) {
            // &variable (pointer address)
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "DEREFERENCE") == 0) {
            // *pointer
            ptr = ptr->next;
        }

        // constants
        else if (strcmp(ptr->type, "INT") == 0 ||
                 strcmp(ptr->type, "CHAR") == 0 ||
                 strcmp(ptr->type, "FLOAT") == 0 ||
                 strcmp(ptr->type, "STR") == 0) {
            // literal constant values
            ptr = ptr->next;
        }

        // binary expressions
        else if (strcmp(ptr->type, "ADD") == 0 ||
                 strcmp(ptr->type, "SUB") == 0 ||
                 strcmp(ptr->type, "MULT") == 0 ||
                 strcmp(ptr->type, "DIV") == 0 ||
                 strcmp(ptr->type, "MOD") == 0 ||
                 strcmp(ptr->type, "LT") == 0 ||
                 strcmp(ptr->type, "LTE") == 0 ||
                 strcmp(ptr->type, "GT") == 0 ||
                 strcmp(ptr->type, "GTE") == 0 ||
                 strcmp(ptr->type, "EQ") == 0 ||
                 strcmp(ptr->type, "NEQ") == 0 ||
                 strcmp(ptr->type, "AND") == 0 ||
                 strcmp(ptr->type, "OR") == 0) {
            // evaluate left and right expressions
            ptr = ptr->next;
        }

        // data type markers
        else if (strcmp(ptr->type, "DATATYPE") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "TYPE_TOKEN") == 0) {
            // base type (int, float, char, string, list, ptr, etc.)
            ptr = ptr->next;
        }

        else {
            fprintf(stderr, "Unhandled node type: %s\n", ptr->type);
            ptr = ptr->next;
        }

        current_depth++;
    }
    return 0;
}
