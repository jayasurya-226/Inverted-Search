#include "inverted_search.h"                 // Include header file for inverted search

int create_Database(hash_t *hash_table, FileList *file_list)
{
    if (file_list == NULL)                   // Check if file list is empty
    {
        printf(RED "No valid files found.\n" RESET); // Error message
        return FAILURE;                      // Return failure
    }

    FileList *temp = file_list;              // Pointer to traverse file list
    char word[50];                            // Buffer to store each word
    int index;                                // Variable to store hash index

    printf(CYAN "\nCreating DATABASE with given files...\n" RESET); // Start message

    while (temp != NULL)                     // Loop through each file in list
    {
        FILE *fp = fopen(temp->filename, "r"); // Open file for reading
        if (fp == NULL)                      // If file failed to open
        {
            printf(RED "Unable to open file: %s\n" RESET, temp->filename); // Error
            temp = temp->link;               // Move to next file
            continue;                        // Skip this file
        }

        printf(YELLOW "\nProcessing File: %s\n" RESET, temp->filename); // File name

        while (fscanf(fp, "%49s", word) != EOF) // Read every word from file
        {
            int len = strlen(word);          // Get word length

            for (int i = 0; i < len; i++)    // Loop to clean trailing punctuation
            {
                if (!isalnum(word[i]))       // If character is not alphanumeric
                {
                    word[i] = '\0';          // Terminate string here
                    break;                   // Stop cleaning
                }
            }

            if (strlen(word) == 0) continue; // Skip empty words

            if (isalpha(word[0]))            // If starting with an alphabet
                index = tolower(word[0]) - 'a'; // Hash index: 0–25
            else if (isdigit(word[0]))       // If starting with digit
                index = 26;                  // Bucket index 26 for digits
            else
                index = 27;                  // Bucket index 27 for symbols

            main_node *mtemp = hash_table[index].link; // Pointer to main node list
            main_node *mprev = NULL;         // Track previous main node
            int word_found = 0;              // Flag for existing word

            while (mtemp != NULL)            // Traverse main node list
            {
                if (strcmp(mtemp->word, word) == 0) // Compare with existing word
                {
                    word_found = 1;          // Mark as found
                    break;                   // Stop searching
                }
                mprev = mtemp;               // Update previous node
                mtemp = mtemp->link;         // Move to next node
            }

            if (!word_found)                 // If word not in table
            {
                main_node *mnew = malloc(sizeof(main_node)); // Allocate main node
                sub_node  *snew = malloc(sizeof(sub_node));  // Allocate subnode

                if (!mnew || !snew)          // Check memory allocation
                {
                    printf(RED "Memory allocation failed!\n" RESET);
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(mnew->word, word);    // Copy word to main node
                mnew->file_count = 1;        // First file occurrence
                mnew->link = NULL;           // No next main node yet

                strcpy(snew->file_name, temp->filename); // Store file name
                snew->word_count = 1;        // Word appeared once
                snew->link = NULL;           // No next subnode

                mnew->sublink = snew;        // Link subnode to main node

                if (mprev)                   // Insert main node in list
                    mprev->link = mnew;      // Attach after previous node
                else
                    hash_table[index].link = mnew; // Insert at start
            }
            else                               // Word exists, check subnodes
            {
                sub_node *stemp = mtemp->sublink; // Pointer to subnode
                sub_node *sprev = NULL;       // Track previous subnode
                int file_found = 0;           // Flag for file presence

                while (stemp != NULL)         // Traverse subnode list
                {
                    if (strcmp(stemp->file_name, temp->filename) == 0) // File match
                    {
                        file_found = 1;       // Mark file found
                        break;               // Done
                    }
                    sprev = stemp;            // Update previous subnode
                    stemp = stemp->link;      // Move to next subnode
                }

                if (file_found)               // If file already present
                {
                    stemp->word_count++;      // Increment word count
                }
                else                           // File not found, add subnode
                {
                    sub_node *snew = malloc(sizeof(sub_node)); // Allocate new subnode
                    if (!snew)
                    {
                        printf(RED "Memory allocation failed!\n" RESET);
                        fclose(fp);
                        return FAILURE;
                    }

                    strcpy(snew->file_name, temp->filename); // Store filename
                    snew->word_count = 1;     // First count
                    snew->link = NULL;        // End of sublist

                    if (sprev)
                        sprev->link = snew;   // Append subnode
                    else
                        mtemp->sublink = snew;// Attach directly (rare)

                    mtemp->file_count++;      // Increase file count
                }
            }
        }

        fclose(fp);                           // Close current file
        temp = temp->link;                    // Move to next file
    }

    printf(GREEN "\nDATABASE CREATED SUCCESSFULLY!\n" RESET); // Success message
    return SUCCESS;                           // Return success
}
