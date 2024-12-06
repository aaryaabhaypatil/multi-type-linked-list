#include "mtll.c"

// Maximum size of input allowed
#define MAX 129

// Enum defining the differnet commands used for handling the multi-type linked list
enum Commands {
    NEW,
    VIEW,
    TYPE,
    VIEW_ALL,
    REMOVE,
    INVALID,
    INVALID_INPUT,
    INVALID_NEW,
    INVALID_TYPE,
    INVALID_REMOVE,
    INVALID_VIEW
};

bool isRemoved = false;
int current_list = 0;
// Storing the total number of lists even after removal becuase we need to loop through the original in VIEW ALL
size_t number = 0;


// Handled the commands in this function
void handle_command(enum Commands cmd, char *arg, struct mtll **lists, size_t *num_lists) {
    switch (cmd) {
        case NEW: {
            // Checks if the argument is NULL
            if (arg == NULL || strcmp(arg, "-1") == 0) {
                printf("INVALID COMMAND: NEW\n");
                break;
            }
            // Converting the argument to size_t which tells us the numberof new elements to ass in the list
            size_t num_elements = atoi(arg);
            if (num_elements == 0) {
                printf("INVALID COMMAND: NEW\n");
                return;
            }
            // Creata a new list
            struct mtll *new_list = mtll_create();
            // Checking for memeory allocation failure
            if (new_list == NULL) {
                printf("Failed to create new list. Exiting program.\n");
                exit(1);
            }
            // Initialising new variable for user input 
            char *element = NULL;
            size_t element_size = MAX;
            ssize_t read = 0;
            for (int i = 0; i < num_elements; ++i) {
                // Reading input from stdin using getline() 
                read = getline(&element, &element_size, stdin);
                // Checking for (CTRL+D)
                if (read == -1) {
                    free(new_list);
                    //Freeing memory for other allocated lists
                    for (size_t j = 0; j < number; j++){
                        mtll_free(lists[j]);
                    }
                    // Freeing the memory allocated for input element
                    free(element);
                    exit(EXIT_SUCCESS);
                }
                // Removing newline
                size_t len = strlen(element);
                if (len > 0 && element[len - 1] == '\n') {
                    element[len - 1] = '\0';
                }
                // Checking if the input exceeds maximum size
                if (len > MAX - 1) {
                    element[MAX] = '\0';
                }

                // Process the input and insert into the list
                if (strlen(element) > 0) {
                    mtll_inse(new_list, element);
                } else {
                    mtll_inse(new_list, "");
                }
            }
            // Add the new list to the array of lists
            lists[number] = new_list;
            printf("List %d: ", current_list);
            mtll_view(new_list);
            // Incrementing the count of lists and update current list index
            *num_lists += 1;
            number = *num_lists;
            current_list += 1;
            // Increment number of lists if a list has been removed
            if(isRemoved){
                number += 1;
            }
            break;
        }
        case VIEW: {
            // Checking for invalid argument after VIEW
            if (arg == NULL || strcmp(arg, "-1") == 0) {
                printf("INVALID COMMAND: VIEW\n");
                break;
            }
            // Converting the argument to the corresponding list index
            size_t index = atoi(arg);
            // calling the fucntion to view the list at the given index
            mtll_view_by_index(lists, *num_lists, index, isRemoved, number);
            break;
        }
        case TYPE: {
            // Check if the argument is NULL
            if (arg == NULL) {
                printf("INVALID COMMAND: TYPE\n");
                break;
            }
            // Converting the argument to the corresponding list index
            size_t index = atoi(arg);
            // View the types of elements in the list at the given index
            mtll_view_types(lists, *num_lists, index);
            break;
        }
        case VIEW_ALL: {
            // function to view all lists
            mtll_view_all(lists, *num_lists, isRemoved, number);
            break;
        }
        case REMOVE: {
            // checks if args is null
            if (arg == NULL || strcmp(arg, "-1") == 0) {
                printf("INVALID COMMAND: REMOVE\n");
                break;
            }
            // Converting the argument to the corresponding list index to remove 
            size_t index_to_remove = atoi(arg);
            // Check if the index to remove is valid
            if(index_to_remove < 0){
                printf("INVALID COMMAND: REMOVE\n");
                break;
            } else if(number == 0){
                printf("INVALID COMMAND: REMOVE\n");
                break;
            }
            else if(lists[index_to_remove] == NULL){
                printf("INVALID COMMAND: REMOVE\n");
                break;
            }
            else {
                isRemoved = true;
                *num_lists = mtll_remove_list(lists, *num_lists, index_to_remove, number);
                printf("List %zu has been removed.\n", index_to_remove);
                printf("\n");
                mtll_view_all(lists, *num_lists, isRemoved, number);
                break;
            }
        }
        case INVALID_INPUT: {
            printf("INVALID COMMAND: INPUT\n");
            break;
        }
        case INVALID_NEW:{
            printf("INVALID COMMAND: NEW\n");
            break;
        }
        case INVALID_TYPE:{
            printf("INVALID COMMAND: TYPE\n");
            break;
        }
        case INVALID_REMOVE:{
            printf("INVALID COMMAND: REMOVE\n");
            break;
        }
        case INVALID_VIEW:{
            printf("INVALID COMMAND: VIEW\n");
            break;
        }
        case INVALID:
            printf("INVALID COMMAND: INPUT\n");
            break;
    }
}


int main(int argc, char** argv) {
    // Buffer for user input
    char input[128] ={'\0'};
    // Buffer for command string       
    char command_str[128] = {'\0'}; 
    // Buffer for argument 
    char arg[128]= "";       
    // Array of lists   
    struct mtll *lists[100]= {NULL}; 
    // Number of lists
    size_t num_lists = 0;
    char command[20] = ""; 
    char value[80] = "";
    int list_id = 0;
    int index = 0;
    char index_str[50] = "";
    char list_id_str[50] = "";
    

    while (fgets(input, sizeof(input), stdin) != NULL) {
        // Ensuring the input is 128 character
        if (input[127] != '\0') {
            printf("more than 128 characters\n");
        }
        input[strcspn(input, "\n")] = '\0';
        // Declare enum variable to store command type
        enum Commands cmd;
        // printf("%s\n", input);
        if (strcmp(input, "\n") == 0) {
            printf("Input is a newline character.\n");
        }
        if (sscanf(input, "%s %s %s %[^\n]", command, list_id_str, index_str, value) == 4) {
            if (strcmp(command, "INSERT") == 0) {
                // Check if list_id_str and index_str are valid integers
                if (!is_valid_integer(list_id_str) || !is_valid_integer(index_str)) {
                    printf("INVALID COMMAND: INSERT\n");    
                } else{
                    int list_id = atoi(list_id_str);
                    int index = atoi(index_str);
                    // Proceed with insertion
                    if (num_lists == 0) {
                        printf("No lists available to insert into\n");
                    } else {
                        mtll_insert(lists[list_id], index, value);
                        printf("List %d: ", list_id);
                        mtll_view(lists[list_id]);
                    }
                }
            } else if(strcmp(command, "DELETE") == 0){
                printf("INVALID COMMAND: DELETE\n");
            }
        }
        else if (sscanf(input, "%s %s %s", command, list_id_str, index_str) == 3){        
            if(strcmp(command, "INSERT") == 0){
                printf("INVALID COMMAND: INSERT\n");
            }
            if(strcmp(list_id_str, "too") == 0){
                // printf("%s\n", command);
                if(strcmp(command, "NEW") == 0){
                    printf("INVALID COMMAND: NEW\n"); 
                } else if (strcmp(command, "VIEW") == 0){
                    printf("INVALID COMMAND: VIEW\n"); 
                } else if (strcmp(command, "REMOVE") == 0){
                    printf("INVALID COMMAND: REMOVE\n"); 
                } 
               
            }
            else if (!is_valid_integer(list_id_str) || !is_valid_integer(index_str)) {
                printf("INVALID COMMAND: DELETE\n");                    
            } else{
                list_id = atoi(list_id_str);
                index = atoi(index_str);
                if (mtll_delete(lists[list_id], index)) {
                    mtll_free(lists[list_id]); 
                    printf("List %d: ", list_id);
                    mtll_view(lists[list_id]);
                } else{
                    printf("List %d: ", list_id);
                    mtll_view(lists[list_id]);
                }
            }            
        }
        else if (sscanf(input, "%s %s", command_str, arg) == 2) {
            if (isspace(input[0])) {
                cmd = INVALID_INPUT;
            } 
            else if (strcmp(command_str, "NEW") == 0) {
                cmd = NEW;  
            } else if (strcmp(command_str, "VIEW") == 0) {
                if (strcmp(arg, "ALL") == 0) {
                    cmd = VIEW_ALL;
                } else {
                    cmd = VIEW;
                }
            } else if (strcmp(command_str, "TYPE") == 0) {
                cmd = TYPE;
            } 
            else if (strcmp(command_str, "REMOVE") == 0) {
                cmd = REMOVE;
            } 
            else {
                cmd = INVALID;
            }
            // Handle the commands
            handle_command(cmd, arg, lists, &num_lists);
        } else if (sscanf(input, "%s", command_str) == 1){
            if(strcmp(command_str, "NEW") == 0) {
                cmd = INVALID_NEW;
            } else if(strcmp(command_str, "TYPE") == 0){
                cmd = INVALID_TYPE;
            } else if(strcmp(command_str, "REMOVE") == 0){
                cmd = INVALID_REMOVE;
            } else if(strcmp(command_str, "VIEW") == 0){
                cmd = INVALID_VIEW;
            }  else{
                cmd = INVALID_INPUT;
            }
            handle_command(cmd, "", lists, &num_lists);
            continue;
        }
        else {
            cmd = INVALID;
            handle_command(cmd, "", lists, &num_lists);
            continue;
        }
    } 
    if (feof(stdin)) {
        if(isRemoved){
            for (size_t j = 0; j < number; j++){
                mtll_free(lists[j]);
            }
        } else {
            for (size_t j = 0; j < num_lists; j++){
                mtll_free(lists[j]);
            }
        }
        exit(0);
    } else {
        printf("Error reading input.\n");
    }
}



