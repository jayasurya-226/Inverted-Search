#include "inverted_search.h"   // Include header for inverted search functions and structures

/* --------------------  Remove file from FileList -------------------- */
void remove_file_from_list(FileList **head, const char *filename)   // Remove a file from FileList
{
    if (!head || !*head) return;   // If list is empty, return

    FileList *curr = *head, *prev = NULL;   // Initialize pointers for traversal

    while (curr)   // Traverse through list
    {
        if (strcmp(curr->filename, filename) == 0)   // If matching filename found
        {
            if (prev == NULL)       // If file is the first node
                *head = curr->link; // Update head
            else
                prev->link = curr->link; // Link previous to next

            free(curr);             // Free removed node
            return;                 // Exit after deletion
        }
        prev = curr;                // Move prev forward
        curr = curr->link;          // Move curr forward
    }
}

/* --------------------Check file exists in FileList -------------------- */
int is_file_in_filelist(FileList *head, const char *filename)  // Check if filename already exists
{
    while (head)                    // Traverse FileList
    {
        if (strcmp(head->filename, filename) == 0) // Compare filenames
            return 1;               // Return 1 if found
        head = head->link;          // Move to next
    }
    return 0;                       // Return 0 if not found
}

/* -------------------- Core Insert: Insert word into Hash Table -------------------- */
void insert_word(hash_t *hash_table, const char *word, const char *filename)   // Insert a word into database
{
    int index;                      // Hash index variable

    if (isalpha(word[0]))           // If word starts with alphabet
        index = tolower(word[0]) - 'a'; // Map a-z to 0–25
    else if (isdigit(word[0]))      // If starts with number
        index = 26;                 // Use index 26 for digits
    else
        index = 27;                 // Use index 27 for special chars

    main_node *mtemp = hash_table[index].link; // Pointer to list at hash index
    main_node *mprev = NULL;        // Previous pointer for traversal

    /* Check if main node (word) exists */
    while (mtemp)                   // Traverse main nodes
    {
        if (strcmp(mtemp->word, word) == 0)   // If word already exists
        {
            sub_node *stemp = mtemp->sublink; // Pointer to subnode list
            sub_node *sprev = NULL;           // Previous subnode

            /* Check if this file already exists */
            while (stemp)           // Traverse subnodes
            {
                if (strcmp(stemp->file_name, filename) == 0) // File exists
                {
                    stemp->word_count++;     // Increment word count
                    return;                  // Done
                }
                sprev = stemp;               // Move sprev
                stemp = stemp->link;         // Move stemp
            }

            /* Create new subnode for this file */
            sub_node *new_sub = malloc(sizeof(sub_node)); // Allocate memory
            new_sub->word_count = 1;       // First occurrence
            strcpy(new_sub->file_name, filename); // Copy filename
            new_sub->link = NULL;          // End of subnode list

            if (sprev)
                sprev->link = new_sub;     // Append to end
            else
                mtemp->sublink = new_sub;  // First subnode

            mtemp->file_count++;           // Update file count
            return;                        // Done updating
        }
        mprev = mtemp;                     // Move previous
        mtemp = mtemp->link;               // Move current
    }

    /* Create new main node because word not found */
    main_node *new_main = malloc(sizeof(main_node));   // Allocate main node
    strcpy(new_main->word, word);        // Copy word
    new_main->file_count = 1;            // First file count
    new_main->link = NULL;               // End of list

    /* First subnode */
    sub_node *new_sub = malloc(sizeof(sub_node)); // Create subnode
    new_sub->word_count = 1;            // First count
    strcpy(new_sub->file_name, filename); // Copy filename
    new_sub->link = NULL;               // End of sublist

    new_main->sublink = new_sub;        // Link subnode to main node

    /* Attach to hash table */
    if (mprev == NULL)
        hash_table[index].link = new_main;  // First node in index
    else
        mprev->link = new_main;             // Append to list
}

/* -------------------- update_database -------------------- */
int update_database(hash_t *hash_table, FileList **file_list)   // Function to update DB with new file
{
    char fname[100];              // Store filename

    printf(YELLOW "Enter the filename to update: " RESET); // Prompt user
    scanf("%99s", fname);         // Read filename

    /* Check for .txt extension */
    int len = strlen(fname);      // Length of filename
    if (len < 4 || strcmp(fname + len - 4, ".txt") != 0) // Validate extension
    {
        printf(RED "Error: Invalid file extension for %s. Expected .txt\n" RESET, fname);
        return FAILURE;           // Return failure
    }

    /* If file doesn't exist, create empty file */
    FILE *fp = fopen(fname, "r"); // Try opening file
    if (!fp)                      // If file doesn't exist
    {
        printf(MAGENTA "File not found. Creating new file...\n" RESET);
        fp = fopen(fname, "w");   // Create new file
        if (!fp)                  // If still cannot open
        {
            printf(RED "Cannot create file.\n" RESET);
            return FAILURE;       // Failure
        }
        fclose(fp);               // Close created file
    }
    else
    {
        fclose(fp);               // Close existing file
    }

    /* Validate file (non-empty, proper content) */
    int res = validate_file(fname); // Validate file contents
    if (res == FILE_EMPTY)          // If empty
    {
        printf(RED "File is empty. Add data first.\n" RESET);
        return FAILURE;             // Cannot update
    }
    else if (res == FAILURE)        // Invalid file
    {
        printf(RED "Invalid file.\n" RESET);
        return FAILURE;
    }

    /* Insert into file list */
    if (insert_file(file_list, fname) == FAILURE)  // Try adding file
    {
        printf(RED "File already exists in list.\n" RESET); // Duplicate file
        return FAILURE;             // Stop
    }

    /* Temporary node to process only this file */
    FileList *temp = malloc(sizeof(FileList)); // Allocate temp node
    strcpy(temp->filename, fname);             // Copy filename
    temp->link = NULL;                         // No next node

    /* Update only this file */
    if (create_Database(hash_table, temp) == SUCCESS)   // Create DB entry
    {
        printf(GREEN "Database updated successfully.\n" RESET);
        free(temp);             // Free temporary node
        return SUCCESS;         // Return success
    }
    else
    {
        printf(RED "Database update failed.\n" RESET); // Error message
        remove_file_from_list(file_list, fname);       // Rollback: remove file
        free(temp);                                    // Free temp node
        return FAILURE;                                 // Return failure
    }
}
