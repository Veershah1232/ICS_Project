%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   

typedef struct treeNode{
    char type[20]; //stores the node type like assignment,declaration,etc
    char value[50]; //stores the value of the node
    struct treeNode* left; //point to the left branch in the tree
    struct treeNode* right; //point to the right branch in the tree
    struct treeNode* next; //next statement in the sequence
} treeNode;
//function to create a node for the tree
treeNode* createNode(char type[], char value[], treeNode* left, treeNode* right, treeNode* next) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
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
treeNode* root = NULL; //the head node of the tree

// Fancy print function
void printTree(treeNode* node, int indent, int isLast) {
    if (!node) return;

    for (int i = 0; i < indent - 4; i++) printf(" ");
    if (indent > 0) printf("%s── ", isLast ? "└" : "├");

    printf("[%s", node->type);
    if (strlen(node->value)) printf(": %s", node->value);
    printf("]\n");

    if (node->left || node->right || node->next) {
        if (node->left) printTree(node->left, indent + 4, 0);
        if (node->right) printTree(node->right, indent + 4, node->next ? 0 : 1);
        if (node->next) printTree(node->next, indent + 4, 1);
    }
}

// Error handler
int yyerror(const char* msg) {
    fprintf(stderr, "Syntax Error: %s\n", msg);
    return 0;
}

// Lexer declaration
int yylex();

%}

//union allows us to store different data types in the same memory location but only use one at a time
%union {
    char* str;           // for strings like identifiers, string literals, etc.
    int int_val;         // if you use integer literals
    float float_val;     // if you use float literals
    char char_val;       // if you use char literals
    struct treeNode* Node; // for AST nodes
}

//defining all the tokens used by the lexer
%token IF THEN ELSE RETURN CREATE AS OF SHOW ASK LOOP FROM TO WHILE NEXT LEAVE LET GENERATE CALL AND OR 
%token INSERT SET GET SEARCH SORT DELETE
%token PLUS MINUS MULT DIV PERCENT ASSIGN EQ NEQ GT LT GTE LTE 
%token LBRACE RBRACE LPAREN RPAREN EOL COMMA AMPERSAND LSQUARE RSQUARE

%type <Node> program statement_list statement var_dec assignment show_statement ask_statement ll_operations
%type <Node> if_statement while_loop for_loop next_statement  leave_statement block function_dec function_call return_statement
%type <Node> exp parameter parameters arguments

%token <str> IDENTIFIER STRING
%token <int_val> INTEGER
%token <float_val> FLOAT
%token <char_val> CHAR
%token <str> INT_TYPE CHAR_TYPE FLOAT_TYPE LIST_TYPE POINTER LINKEDLIST DICTIONARY NULL_TYPE BOOLEAN

%left    '+' '-'
%left    '*' '/'
%right   '='
%nonassoc  '<' '>' 

%debug

%%

program:
    statement_list { root = $$; }
    ;

statement_list:
    statement optional_eol statement_list { $1->next = $3; $$ = $1; }
  | statement optional_eol               { $$ = $1; }
;

optional_eol:
    EOL
  | /* empty */
;


statement:
    var_dec EOL                { $$ = $1; }
  | assignment EOL             { $$ = $1; }
  | show_statement EOL         { $$ = $1; }
  | ask_statement EOL          { $$ = $1; }
  | return_statement EOL       { $$ = $1; }
  | next_statement EOL         { $$ = $1; } 
  | leave_statement EOL        { $$ = $1; }
  | ll_operations EOL          { $$ = $1; }

  // These don't require EOL after since they end in a block
  | if_statement           { $$ = $1; }
  | while_loop             { $$ = $1; }
  | for_loop               { $$ = $1; }
  | function_call          { $$ = $1; }
  | function_dec           { $$ = $1; }
;


var_dec: CREATE IDENTIFIER AS INT_TYPE                  {$$ = createNode("VAR_DEC",$2,createNode("TYPE",$4,NULL,NULL,NULL),NULL,NULL);}
       | CREATE IDENTIFIER AS CHAR_TYPE                 {$$ = createNode("VAR_DEC",$2,createNode("TYPE",$4,NULL,NULL,NULL),NULL,NULL);}
       | CREATE IDENTIFIER AS FLOAT_TYPE                {$$ = createNode("VAR_DEC",$2,createNode("TYPE",$4,NULL,NULL,NULL),NULL,NULL);} 
       | CREATE IDENTIFIER AS LIST_TYPE LPAREN exp RPAREN     {$$ = createNode("LIST_DEC",$2,createNode("TYPE",$4,NULL,NULL,NULL),$6,NULL);} 
       | CREATE IDENTIFIER AS POINTER                   {$$ = createNode("VAR_DEC",$2,createNode("TYPE",$4,NULL,NULL,NULL),NULL,NULL);} 
       | CREATE IDENTIFIER AS LINKEDLIST LPAREN exp RPAREN    {$$ = createNode("LL_DEC",$2,createNode("TYPE",$4,NULL,NULL,NULL),$6,NULL);} 
       | CREATE IDENTIFIER AS DICTIONARY OF INT_TYPE    {$$ = createNode("DICT_DEC",$2,createNode("TYPE",$6,NULL,NULL,NULL),NULL,NULL);}
       | CREATE IDENTIFIER AS DICTIONARY OF CHAR_TYPE   {$$ = createNode("DICT_DEC",$2,createNode("TYPE",$6,NULL,NULL,NULL),NULL,NULL);}
       ;

show_statement: SHOW LPAREN STRING RPAREN                   {$$ = createNode("SHOW",$3,NULL,NULL,NULL);}

              | SHOW LPAREN STRING COMMA exp RPAREN  {$$ = createNode("SHOW",$3,$5,NULL,NULL);} 
              ;                                               

ask_statement: ASK LPAREN STRING COMMA AMPERSAND IDENTIFIER RPAREN    {$$ = createNode("ASK",$3,createNode("VAR",$6,NULL,NULL,NULL),NULL,NULL);}
             ;   

assignment:
    IDENTIFIER ASSIGN exp                      { $$ = createNode("ASSIGN", $1, $3, NULL, NULL); }
    | IDENTIFIER LSQUARE exp RSQUARE ASSIGN exp  { 
        treeNode* indexNode = createNode("INDEX", $1, $3, NULL, NULL);
        $$ = createNode("ASSIGN", NULL, indexNode, $6, NULL);
    } 
    | IDENTIFIER ASSIGN IDENTIFIER LPAREN GET COMMA exp RPAREN {
        treeNode* getNode = createNode("LL_GET", $3, $7, NULL, NULL); 
        $$ = createNode("ASSIGN", $1, getNode, NULL, NULL); 
    }

  ;
 

exp
  : IDENTIFIER                                 { $$ = createNode("VAR", $1, NULL, NULL, NULL); }
  | IDENTIFIER LSQUARE exp RSQUARE             { $$ = createNode("INDEX", $1, $3, NULL, NULL); }
  | AMPERSAND IDENTIFIER                       { $$ = createNode("ADDRESS", $2, NULL, NULL, NULL); }  
  | MULT IDENTIFIER                            { $$ = createNode("DEREFERENCE", $2, NULL, NULL, NULL); }  
  | INTEGER                                    { char buf[20]; sprintf(buf, "%d", $1); $$ = createNode("INT", buf, NULL, NULL, NULL); }
  | CHAR                                       { char buf[5]; sprintf(buf, "%c", $1); $$ = createNode("CHAR", buf, NULL, NULL, NULL); }
  | FLOAT                                      { char buf[50]; sprintf(buf, "%f", $1); $$ = createNode("FLOAT", buf, NULL, NULL, NULL); }
  | STRING                                     { $$ = createNode("STR", $1, NULL, NULL, NULL); }
  | exp PLUS exp                               { $$ = createNode("ADD", NULL, $1, $3, NULL); }
  | exp MINUS exp                              { $$ = createNode("SUB", NULL, $1, $3, NULL); }
  | exp MULT exp                               { $$ = createNode("MULT", NULL, $1, $3, NULL); }
  | exp DIV exp                                { $$ = createNode("DIV", NULL, $1, $3, NULL); }
  | exp PERCENT exp                            { $$ = createNode("MOD", NULL, $1, $3, NULL); }
  | exp LT exp                                 { $$ = createNode("LT", NULL, $1, $3, NULL); }
  | exp LTE exp                                { $$ = createNode("LTE", NULL, $1, $3, NULL); }
  | exp GT exp                                 { $$ = createNode("GT", NULL, $1, $3, NULL); }
  | exp GTE exp                                { $$ = createNode("GTE", NULL, $1, $3, NULL); }
  | exp EQ exp                                 { $$ = createNode("EQ", NULL, $1, $3, NULL); }
  | exp NEQ exp                                { $$ = createNode("NEQ", NULL, $1, $3, NULL); }
  | exp AND exp                                { $$ = createNode("AND", NULL, $1, $3, NULL); }
  | exp OR exp                                 { $$ = createNode("OR", NULL, $1, $3, NULL); }
  ;

ll_operations: IDENTIFIER LPAREN SORT RPAREN                        {$$ = createNode("LL_SORT", $1, NULL, NULL, NULL);}
             | IDENTIFIER LPAREN SEARCH COMMA exp RPAREN            {$$ = createNode("LL_SEARCH", $1, $5, NULL, NULL);}
             | IDENTIFIER LPAREN INSERT COMMA exp COMMA exp RPAREN  {$$ = createNode("LL_INSERT", $1, $5, $7, NULL);}
             | IDENTIFIER LPAREN SET COMMA exp COMMA exp RPAREN     {$$ = createNode("LL_SET", $1, $5, $7, NULL); }
             | IDENTIFIER LPAREN DELETE COMMA exp RPAREN            {$$ = createNode("LL_DEL",$1,$5,NULL,NULL);}
;  


if_statement: IF LPAREN exp RPAREN THEN block               {$$ = createNode("IF",NULL,$3,$6,NULL);}
            | IF LPAREN exp RPAREN THEN block ELSE block    {$$ = createNode("IF-ELSE",NULL,$3,$6,$8);}
            ;

block: LBRACE statement_list RBRACE {$$ = createNode("BLOCK",NULL,$2,NULL,NULL);}
     ;

while_loop: WHILE LPAREN exp RPAREN block {$$ = createNode("WHILE",NULL,$3,$5,NULL);}
;

for_loop: LOOP IDENTIFIER FROM exp TO exp block {$$ = createNode("FOR", NULL, createNode("VAR", $2, NULL, NULL, NULL), createNode("RANGE", NULL, $4, $6, NULL), $7);}
;

next_statement: NEXT {$$ = createNode("NEXT",NULL,NULL,NULL,NULL);}
;

leave_statement: LEAVE {$$ = createNode("LEAVE",NULL,NULL,NULL,NULL);}
;

parameter: IDENTIFIER AS INT_TYPE       { $$ = createNode("PARAMETER", $1, createNode("TYPE", $3, NULL, NULL, NULL), NULL, NULL); }
         | IDENTIFIER AS CHAR_TYPE      { $$ = createNode("PARAMETER", $1, createNode("TYPE", $3, NULL, NULL, NULL), NULL, NULL); }
         | IDENTIFIER AS FLOAT_TYPE     { $$ = createNode("PARAMETER", $1, createNode("TYPE", $3, NULL, NULL, NULL), NULL, NULL); }
         | IDENTIFIER AS LIST_TYPE      { $$ = createNode("PARAMETER", $1, createNode("TYPE", $3, NULL, NULL, NULL), NULL, NULL); }
         | IDENTIFIER AS POINTER        { $$ = createNode("PARAMETER", $1, createNode("TYPE", $3, NULL, NULL, NULL), NULL, NULL); }
         | IDENTIFIER AS LINKEDLIST     { $$ = createNode("PARAMETER", $1, createNode("TYPE", $3, NULL, NULL, NULL), NULL, NULL); }
         | IDENTIFIER AS DICTIONARY     { $$ = createNode("PARAMETER", $1, createNode("TYPE", $3, NULL, NULL, NULL), NULL, NULL); }
         ;


parameters:
    /* empty */                                   { $$ = NULL; }
  | parameter                                     { $$ = $1; }
  | parameter COMMA parameters                    { $1->next = $3; $$= $1;}
  ; 
    
function_dec:
    LET IDENTIFIER LPAREN parameters RPAREN GENERATE INT_TYPE block
        {
            $$ = createNode("FUNC_DEC", $2,
                    createNode("FUNC_DATA", NULL, $4,
                        createNode("RET_TYPE", $7, NULL, NULL, NULL),
                    NULL),
                $8, NULL);
        }
  | LET IDENTIFIER LPAREN parameters RPAREN GENERATE CHAR_TYPE block
        {
            $$ = createNode("FUNC_DEC", $2,
                    createNode("FUNC_DATA", NULL, $4,
                        createNode("RET_TYPE", $7, NULL, NULL, NULL),
                    NULL),
                $8, NULL);
        }
  | LET IDENTIFIER LPAREN parameters RPAREN GENERATE FLOAT_TYPE block
        {
            $$ = createNode("FUNC_DEC", $2,
                    createNode("FUNC_DATA", NULL, $4,
                        createNode("RET_TYPE", $7, NULL, NULL, NULL),
                    NULL),
                $8, NULL);
        }
  | LET IDENTIFIER LPAREN parameters RPAREN GENERATE POINTER block
        {
            $$ = createNode("FUNC_DEC", $2,
                    createNode("FUNC_DATA", NULL, $4,
                        createNode("RET_TYPE", $7, NULL, NULL, NULL),
                    NULL),
                $8, NULL);
        }
;


return_statement: RETURN exp {$$ = createNode("RETURN",NULL,$2,NULL,NULL);}
;

function_call: CALL IDENTIFIER LPAREN arguments RPAREN {$$ = createNode("CALL",$2,$4,NULL,NULL);}
             | CALL IDENTIFIER LPAREN RPAREN           {$$ = createNode("CALL",$2,NULL,NULL,NULL);}
             ;

arguments: exp                  {$$ = $1;}
         | exp COMMA arguments  {$1->next=$3; $$=$1;}
         ;

%%

int main() {
    yydebug = 0; 
    printf("Parsing from redirected input...\n");
    yyparse();
    printf("\n--- AST Tree ---\n");
    printTree(root, 0, 1);
    return 0;
}

