#include "inverted_search.h"                               // Include header file

int display_database(hash_t *hash_table)                   // Function to display database
{
    printf(CYAN "\n=================================================================================================\n" RESET);
    // Print top border
    printf(CYAN "                Displaying Inverted Search Database     \n" RESET);
    // Print title
    printf(CYAN "=================================================================================================\n\n" RESET);
    // Print bottom border of header

    int empty = 1;                                          // Flag to detect if database is empty

    for (int i = 0; i < 28; i++)                            // Loop through all 28 hash indices
    {
        main_node *main_temp = hash_table[i].link;          // Pointer to main nodes at current index

        while (main_temp != NULL)                           // Traverse main linked list
        {
            empty = 0;                                      // Mark database as non-empty

            printf(YELLOW "[%2d] " RESET, i);               // Print index number

            printf(GREEN "[%-10s]" RESET "  ", main_temp->word);
            // Print main word in formatted green block

            printf(CYAN "%d file(s):  " RESET, main_temp->file_count);
            // Print number of files containing the word

            sub_node *sub_temp = main_temp->sublink;        // Pointer to subnode list

            while (sub_temp != NULL)                        // Traverse subnodes
            {
                printf(MAGENTA "File: %-12s" RESET " -> " GREEN "%d time(s)" RESET,
                    sub_temp->file_name, sub_temp->word_count);
                // Print file name and count

                sub_temp = sub_temp->link;                  // Move to next subnode

                if (sub_temp != NULL)                       // Add spacing if more files follow
                    printf("   ");
            }

            printf("\n");                                   // New line after each main word block
            main_temp = main_temp->link;                    // Move to next main node
        }
    }

    if (empty)                                              // If no words printed
    {
        printf(RED "\nDatabase is EMPTY. Create database first!\n" RESET);
        // Print empty message
    }

    printf(CYAN "\n=================================================================================================\n" RESET);
    // Bottom border
    printf(CYAN "                        End of Database Display            \n" RESET);
    // End title
    printf(CYAN "=================================================================================================\n" RESET);
    // Final border

    return SUCCESS;                                        // Return success status
}
