# Multi Type Linked-List
This project implements a dynamic, multi-type linked list data structure in C, allowing users to manage and interact with lists of various data types, such as integers, floats, characters, and strings. The program supports basic linked list operations, dynamic modifications, and the ability to manage nested lists.

## Features
- Multi-Type Lists: Create lists containing int, float, char, and string types.
- Basic Commands:
    - NEW <number of elements>: Create a new list and initialize it with values.
    - VIEW <list index>: View the contents of a list at a given index.
    - TYPE <list index>: View the types of each element in a list.
    - VIEW ALL: View all created lists.
    - REMOVE <list index>: Remove a list by its index.
- Dynamic List Management:
    - INSERT <list index> <index> <value>: Insert a value at a specified position in the list.
    - DELETE <list index> <index>: Delete a value at a specified position in the list.
- Nested Lists:
    - Support for inserting and managing lists within lists, with proper handling and reference tracking.
    - VIEW-NESTED <list index>: View nested lists and their sub-lists in a structured format.
- Memory Management: Dynamically allocated memory with proper cleanup to prevent memory leaks.

