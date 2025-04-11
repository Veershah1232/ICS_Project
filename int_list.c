#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_LENGTH 50

// Structure to represent a dynamic list
typedef struct{
    char name[MAX_LENGTH]; // Name of the list
    char dtype; // Data type (for future use, e.g., 'i' for int)
    int size; // Size of the list
    int *ptr; // Pointer to dynamically allocated array
} List;

// Function to initialize a List with a given size
List* intlist_init(int arr_size) {
    List* lst_ptr = (List*)malloc(sizeof(List));
    lst_ptr->size = arr_size;
    lst_ptr->ptr = (int*)malloc(arr_size * sizeof(int));
    return lst_ptr;
}

// Function to initialize all elements of an array with a given value
int* intlist_initialize(int *ptr, int arr_size, int val) {
    for (int i = 0; i < arr_size; i++) {
        ptr[i] = val;
    }
    return ptr;
}

// Function to create a clone of an array
int* intlist_clone(int *ptr, int arr_size) {
    int* new_ptr = (int*)malloc(arr_size * sizeof(int)); 
    for (int i = 0; i < arr_size; i++) {
        new_ptr[i] = ptr[i];
    }
    return new_ptr;
}

// Function to get the index of the first occurrence of a value
int intlist_getfirst(int *ptr, int arr_size, int val) {
    for (int i = 0; i < arr_size; i++) {
        if (ptr[i] == val) {
            return i;
        }
    }
    return -1; // Return -1 if value is not found
}

// Function to get the index of the last occurrence of a value
int intlist_getlast(int *ptr, int arr_size, int val) {
    for (int i = arr_size - 1; i >= 0; i--) {
        if (ptr[i] == val) {
            return i;
        }
    }
    return -1; // Return -1 if value is not found
}

// Function to insert an element at a given index
void intlist_insert(List *lst, int index, int val) {
    if (index < 0 || index > lst->size) return; // Check for valid index
    lst->size++;
    lst->ptr = (int*)realloc(lst->ptr, lst->size * sizeof(int));
    for (int i = lst->size - 1; i > index; i--) {
        lst->ptr[i] = lst->ptr[i - 1];
    }
    lst->ptr[index] = val;
}

// Function to delete an element at a given index
void intlist_delete(List *lst, int index) {
    if (index < 0 || index >= lst->size) return; // Check for valid index
    for (int i = index; i < lst->size - 1; i++) {
        lst->ptr[i] = lst->ptr[i + 1];
    }
    lst->size--;
    lst->ptr = (int*)realloc(lst->ptr, lst->size * sizeof(int));
}

// Function to sort an array using Bubble Sort
void intlist_bubbleSort(int *ptr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (ptr[j] > ptr[j + 1]) {
                int temp = ptr[j];
                ptr[j] = ptr[j + 1];
                ptr[j + 1] = temp;
            }
        }
    }
}

// Merge function for Merge Sort
void intlist_merge(int *arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    i = j = 0; k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Function to sort an array using Merge Sort
void intlist_mergeSort(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to calculate the sum of elements in an array
int intlist_sum(int *ptr, int size) {
    int total = 0;
    for (int i = 0; i < size; i++) total += ptr[i];
    return total;
}

// Function to find the minimum element in an array
int intlist_min(int *ptr, int size) {
    int minimum = ptr[0];
    for (int i = 0; i < size; i++) {
        if (ptr[i] < minimum) minimum = ptr[i];
    }
    return minimum;
}

// Function to find the maximum element in an array
int intlist_max(int *ptr, int size) {
    int maximum = ptr[0];
    for (int i = 0; i < size; i++) {
        if (ptr[i] > maximum) maximum = ptr[i];
    }
    return maximum;
}

// Function to calculate the average of an array
float intlist_average(int *ptr, int size) {
    return (float)sum(ptr, size) / size;
}

// Function to remove duplicate elements from the list
void intlist_removeDuplicates(List *lst) {
    for(int i=0; i<lst->size; i++){
        for (int j=i+1; j<lst->size; j++){
            if ((lst->ptr)[j]==(lst->ptr)[i]){
                for (int k=j; k< lst->size-1; k++){
                    (lst->ptr)[k] = (lst->ptr)[k+1];
                }
                j--;
                lst->size--;
            }
        }
    }
    lst->ptr = (int*)realloc(lst->ptr, lst->size*sizeof(int));
    
}

// Function to display elements of an array
void intlist_display(int *ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
}

// int main() {
//     // Test the implemented functionalities
//     List* myList = init(5);
//     initialize(myList->ptr, 5, 1);
//     myList->ptr[2] = 3;
//     myList->ptr[3] = 5;
//     myList->ptr[4] = 3;
//     removeDuplicates(myList);
//     display(myList->ptr, myList->size);
    
//     free(myList->ptr);
//     free(myList);
//     return 0;
// }
