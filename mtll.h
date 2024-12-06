#ifndef MTLL_H
#define MTLL_H
#include <stdbool.h>
#include <stddef.h>

struct Node {
    // Pointer to generic data which allows  to different types
    void *data;
    // Pointer to next node in the linked list
    struct Node *next;
};

enum Types{
    // For an integer
    INT,
    // For a floating point
    FLOAT,
    // For a char
    CHAR,
    // For a string
    STRING,
    REFERENCE 
} ;

struct mtll {
    // Types of data stored in the linked list
    enum Types type;
    // Pointer to the head of the linked list
    struct Node *head;
};

// Creating a new multi type linked list 
extern struct mtll *mtll_create();
// Free the memory allocated for a multi-type linked list
extern void mtll_free(struct mtll *);
// View the contents of a multi-type linked list
extern void mtll_view(struct mtll *);
// This prints the contents of the linked list
extern void mtll_print(struct mtll *);
// Inserts a new element into the linked list
extern void mtll_inse(struct mtll *, void *);
// Add elements from a string representation into the linked list
extern void add_elements_from_string(struct mtll *, const char *);
// Shows the contents of a multi-type linked list at a particular index
extern void mtll_view_by_index(struct mtll **, size_t , size_t, bool, size_t);
// Shows the types of the values of the multi-type linked list
extern void mtll_view_types(struct mtll **, size_t , size_t);
// Views all the lists in the linked list
extern void mtll_view_all(struct mtll **, size_t , bool , size_t);
// Removes a list at the given index
extern size_t mtll_remove_list(struct mtll **, size_t, size_t, size_t);
// Dynamically inserts an element into the list
extern bool mtll_insert(struct mtll *, int , const char *);
// Dynamically removes an element from the list
extern bool mtll_delete(struct mtll *, int);
// Returns the length of a list
extern size_t mtll_length(const struct mtll *);
// Checking if its a decimal
extern bool is_decimal(const char *);
// Checking if its a integer
extern bool is_valid_integer(const char *);

#endif