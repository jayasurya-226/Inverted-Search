/*
 * Function : display_file_list
 * Purpose  : Print linked list of input files (FileList).
 * Note     : Uses 'link' member as defined in header.
 */
#include "inverted_search.h"                   // Include header file for structures and color codes
void display_file_list(FileList *head)          // Function definition accepting head of FileList
{
    printf(CYAN "\n======================= FILE LIST =======================\n" RESET);
    // Print the title header in cyan color

    if (head == NULL)                           // Check if the file list is empty
    {
        printf(RED "No files available.\n" RESET);
        // Print message indicating no files
        return;                                 // Exit function if list is empty
    }

    while (head != NULL)                        // Loop until end of linked list
    {
        printf(GREEN "%s" RESET, head->filename);
        // Print current filename in green

        if (head->link != NULL)                 // If next node exists
            printf(YELLOW " -> " RESET);        // Print arrow separator

        head = head->link;                      // Move to the next node
    }

    printf(YELLOW " -> " RESET RED "NULL\n" RESET);
    // Print NULL to show end of the linked list
    
}
