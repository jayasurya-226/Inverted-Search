#include "inverted_search.h"                           // Include header file for inverted search structures

void search_word(hash_t *hash_table)                   // Function to search a word in the database
{
    char search[50];                                   // Buffer to store user input word
    int index;                                         // Variable to store hash index

    printf(CYAN "Enter the word you want to search: " RESET); // Prompt user to enter the word
    scanf("%49s", search);                             // Read word safely (max 49 chars)

    // Compute hash index based on first character of the word
    if (isalpha(search[0]))                            // If first character is alphabet
        index = tolower(search[0]) - 'a';              // Map 'a'-'z' to 0-25
    else if (isdigit(search[0]))                       // If first character is a digit
        index = 26;                                    // Index 26 reserved for digits
    else                                               // Any other character
        index = 27;                                    // Index 27 reserved for special characters

    main_node *mtemp = hash_table[index].link;         // Get pointer to main node list at computed index

    while (mtemp != NULL)                              // Traverse the main node linked list
    {
        if (strcmp(mtemp->word, search) == 0)          // If the word matches the search term
        {
            printf(GREEN "\nWord '%s' is present in %d file/s\n\n" RESET, // Print word and number of files
                mtemp->word, mtemp->file_count);

            /* ------------ Colored Tabular Output ------------ */
            printf(CYAN "+----------------------+-------------+\n" RESET);     // Table top border
            printf(CYAN "| " RESET YELLOW "File Name" RESET CYAN "           | " RESET YELLOW "Count" RESET CYAN "       |\n" RESET); // Table header
            printf(CYAN "+----------------------+-------------+\n" RESET);     // Table header bottom border

            sub_node *stemp = mtemp->sublink;          // Pointer to subnode list for files

            while (stemp != NULL)                      // Traverse subnodes
            {
                printf(CYAN "| " RESET MAGENTA "%-20s" RESET CYAN " | " RESET GREEN "%-11d" RESET CYAN " |\n", // Print file name in magenta, count in green
                    stemp->file_name, stemp->word_count);

                stemp = stemp->link;                   // Move to next subnode
            }

            printf(CYAN "+----------------------+-------------+\n" RESET);     // Table bottom border

            return;                                    // Exit function after printing result
        }

        mtemp = mtemp->link;                           // Move to next main node if word not found yet
    }

    printf(RED "Word '%s' not found in database.\n" RESET, search); // Print message if word does not exist
}
