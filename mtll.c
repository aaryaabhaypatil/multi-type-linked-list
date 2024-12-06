#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

int malloc_calls = 0;

// Returns if the value if a decimal
bool is_decimal(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0';
}

// Returns if the value if its a valid integer
bool is_valid_integer(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0';
}

// Creates a new multi-type linked list by allocating memory for it dynamically.
struct mtll *mtll_create() {
    // Allocates memory for the new list
    struct mtll *new_list = (struct mtll *)malloc(sizeof(struct mtll));
    // checking if the allocation was successful
    if (new_list == NULL) {
        return NULL;
    }
    // Initialising the head pointer of the list to NULL
    new_list->head = NULL;
    // returns a pointer of the list to the new list
    return new_list;
}

// Returns a pointer to the newly created list on success, or NULL on failure
void mtll_free(struct mtll *list) {
    // checks if the input list pointer is NULL
    if (list == NULL) {
        return;
    }
    // Initialising a pointer to traverse the list starting from the head
    struct Node *current = list->head;
    // Looping through the list to free each node and its data
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp->data); 
        free(temp); 
    }
    // Freeing the memory allocated for the list structure itself
    free(list); 
    list = NULL;
    malloc_calls = malloc_calls - 1;
}

// prints the list to be printed
void mtll_print(struct mtll *list) {
    // Check if the input list pointer is NULL
    struct Node *current = list->head;
    // Looping through the list to print each element
    while (current != NULL) {
        if (current->next != NULL) {
            printf("%s ", (char *)current->data);
        } else {
            printf("%s", (char *)current->data);
        }
        
        if (current->next != NULL) {
            printf("-> ");
        }
        current = current->next;
    }
    printf("\n");
}

void mtll_inse(struct mtll *list, void *data) {
    if (list == NULL) {
        printf("Error: NULL list.\n");
        return;
    }
    if(data == NULL) {
        printf("Error: NULL data.\n");
        return;
    }
    // Allocating memory for the new node
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    malloc_calls += 1;
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->data = strdup((char *)data);
    malloc_calls += 1;
    if (new_node->data == NULL) {
        printf("Memory allocation failed.\n");
        free(new_node);
        return;
    }
    new_node->next = NULL;

    // If the list is empty making the new node the head of the list
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        // Traverse the list to find the last node
        struct Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}


void add_elements_from_string(struct mtll *list, const char *elements_str) {
    if (list == NULL || elements_str == NULL) {
        return;
    }
    char *token = strtok((char *)elements_str, " ");
    while (token != NULL) {
        // Allocating memory for the new element
        char *element = strdup(token);
        if (element == NULL) {
            return;
        }
        // Insert the element into the linked list
        mtll_inse(list, element);
        // Get the next token
        token = strtok(NULL, " ");
    }
}


void mtll_view(struct mtll *list){
    // current pointer to the head of the list
    struct Node *current = list->head;
    while(current != NULL){
        char *data = (char *)current->data;
        // Trying to interpret the data as int
        char *endptr;
        strtol(data, &endptr, 10);
        if (*endptr == '\0') {
             if (strcmp(data, "0") == 0 || strcmp(data, "-0") == 0) {
                printf("0");
            } else {
                printf("%s", data);
            }
        }
        else {
            // floating-point number
            strtod(data, &endptr);
            if (*endptr == '\0') {
                printf("%.2f", atof(data));
            }
            else {
                // single character
                if (strlen(data) == 1) {
                    printf("%c", *data);
                }
                else {
                    // string
                    printf("%s", data);
                }
            }
        }
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}


void mtll_view_by_index(struct mtll **lists, size_t num_lists, size_t index, bool isRemoved, size_t number) {
    if (index > number || lists[index] == NULL) {
        printf("INVALID COMMAND: VIEW\n");
    }  else {
        mtll_view(lists[index]);
    }
}

void mtll_view_types(struct mtll **lists, size_t num_lists, size_t index) {
    if (index >= num_lists) {
        return;
    }
    struct mtll *list = lists[index];
    struct Node *current = list->head;
    while (current != NULL) {
        char *data_str = (char *)current->data;
        char *endptr;
        strtol(data_str, &endptr, 10);
        if (*endptr == '\0') {
            printf("int");
        } else {
            strtod(data_str, &endptr); 
            if (*endptr == '\0') {
                printf("float");
            } else if (strlen(data_str) == 1 && isprint(*data_str)) {
                printf("char");
            } else {
                printf("string");
            }
        }
        if (current->next != NULL) {
            printf(" -> ");
        }
        // Move to the next node
        current = current->next;
    }
    printf("\n");
}

void mtll_view_all(struct mtll **lists, size_t num_lists, bool isRemoved, size_t number) {
    printf("Number of lists: %zu\n", num_lists);
    if(isRemoved) {
        for (size_t i = 0; i < number; ++i) {
            if (lists[i] != NULL) {
                printf("List %zu\n", i);
                continue;
            }
        }
    } else{
        for (size_t i = 0; i < num_lists; ++i) {
            if (lists[i] != NULL) {
                printf("List %zu\n", i);
                continue;
            }
        }
    }        
}
    

size_t mtll_remove_list(struct mtll **lists, size_t num_lists, size_t index, size_t number) {
    if(index < 0 || index >= number){
        printf("INVALID COMMAND: REMOVE\n");
        return num_lists;
    }
    if (lists[index] == NULL){
        printf("INVALID COMMAND: REMOVE\n");
        return num_lists;
    }
    mtll_free(lists[index]);
    lists[index] = NULL;
    return num_lists - 1;
}


size_t mtll_length(const struct mtll *list) {
    size_t length = 0;
    struct Node *current = list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}



bool mtll_insert(struct mtll *list, int index, const char *value) {
    int positive_index = index >= 0 ? index : mtll_length(list) + index + 1;
    if (positive_index < 0) {
        printf("INVALID COMMAND: INSERT\n");
        return false;
    }
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return false;
    }
    new_node->data = strdup(value);
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        return true;
    }

    if (positive_index == 0) {
        new_node->next = list->head;
        list->head = new_node;
        return true;
    }

    struct Node *current = list->head;
    int i = 0;
    while (current->next != NULL && i < positive_index - 1) {
        current = current->next;
        i++;
    }

    if (i != positive_index - 1) {
        printf("INVALID COMMAND: INSERT\n");
        free(new_node->data);
        free(new_node);
        return false;
    }
    new_node->next = current->next;
    current->next = new_node;
    return true;



}


bool mtll_delete(struct mtll *list, int index) {
    // Checking if the list or its head is invalid
    if (!list || !list->head) {
        printf("Invalid list.\n");
        return false;
    }
    // Get the length of the list
    size_t length = mtll_length(list);
    // Adjust negative index
    if (index < 0) {
        index = length + index;
    }
    // Check if the index is out of range
    if (index < 0 || index >= length) {
        printf("INVALID COMMAND: DELETE\n");
        return false;
    }
    if (index == 0) {
        struct Node *temp = list->head;
        list->head = list->head->next;
        free(temp->data);
        malloc_calls -= 1;
        free(temp);
        malloc_calls -= 1;
        return (mtll_length(list) == 0); 
    }
    struct Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    struct Node *temp = current->next;
    current->next = temp->next;
    free(temp->data);
    malloc_calls -= 1;
    free(temp);
    malloc_calls -= 1;
    return false; 
}