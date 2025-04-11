#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct node_C_C{
    char *key; //address of key
    char *value; //address of value
    struct node_C_C *next; //address of next node
}node_C_C;

typedef struct{
    char name[50];
    int len; //len of dictionary as of now
    node_C_C *start; //stores the address of the first location of the dictionary
}dictionary_C_C;

void increase_len(dictionary_C_C *dict, int len);

dictionary_C_C* create_dictionary_C_C(int len, char name[50]);

int insert_C_C(dictionary_C_C *dict, char *key, char *value);

char* getvalue_C_C(dictionary_C_C *dict, char *key);

char* getkey_C_C(dictionary_C_C *dict, char *key);

void free_dict_C_C(dictionary_C_C *dict);

void printing_C_C(dictionary_C_C *dict);

int delete_C_C(dictionary_C_C *dict, char *key);

void test_dict_C_C();
#endif