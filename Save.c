#include "inverted_search.h"                     // Include header file for inverted search structures

/* ------------------ COLOR MACROS ------------------ */
#define RED     "\033[1;31m"                     // Red color code
#define GREEN   "\033[1;32m"                     // Green color code
#define YELLOW  "\033[1;33m"                     // Yellow color code
#define BLUE    "\033[1;34m"                     // Blue color code
#define CYAN    "\033[1;36m"                     // Cyan color code
#define RESET   "\033[0m"                        // Reset color formatting
/* --------------------------------------------------- */

void load_last_saved_file(char *filename)
{
    FILE *fp = fopen("saved_file.txt", "r");     // Open saved file name record in read mode

    if (fp != NULL)                              // If file exists
    {
        if (fgets(filename, 100, fp) != NULL)    // Read filename from file
        {
            filename[strcspn(filename, "\n")] = '\0';  // Remove newline from end
        }
        fclose(fp);                              // Close file

        printf(GREEN "Loaded last used save file: %s\n" RESET, filename);
                                                   // Print loaded file message
    }
    else                                         // If file doesn't exist
    {
        strcpy(filename, "backup.txt");          // Use default filename
        printf(YELLOW "No previous save file found. Using default: backup.txt\n" RESET);
                                                   // Inform user about default selection
    }
}

int save_Database(hash_t *hash_table, const char *filename)
{
    if (filename == NULL || strlen(filename) == 0)   // Validate filename
    {
        printf(RED "Invalid filename\n" RESET);      // Print error
        return FAILURE;                              // Return failure
    }

    const char *ext = strrchr(filename, '.');        // Extract file extension
    if (ext == NULL || strcmp(ext, ".txt") != 0)     // Ensure extension is .txt
    {
        printf(RED "Error: Only .txt files allowed (given: %s)\n" RESET, filename);
                                                      // Print invalid extension error
        return FAILURE;                               // Return failure
    }

    FILE *fp = fopen(filename, "w");                 // Open file in write mode
    if (fp == NULL)                                  // Check if open failed
    {
        printf(RED "Error: Could not open '%s' for writing\n" RESET, filename);
                                                      // Print error
        return FAILURE;                               // Return failure
    }

    printf(BLUE "Saving Database to '%s'...\n" RESET, filename);
                                                      // Inform user saving has begun

    for (int i = 0; i < 28; i++)                      // Loop through all hash indices
    {
        main_node *mnode = hash_table[i].link;        // Pointer to main nodes at index

        while (mnode != NULL)                        // Traverse main node list
        {
            sub_node *snode = mnode->sublink;         // Pointer to subnode list

            fprintf(fp, "#");                         // Start of data record

            fprintf(fp, "%d;%s;%d;",                  // Write index, word, file count
                    i, mnode->word, mnode->file_count);

            while (snode != NULL)                    // Traverse subnodes
            {
                fprintf(fp, "%s;%d;",                // Write file name and count
                        snode->file_name, snode->word_count);
                snode = snode->link;                 // Move to next subnode
            }

            fprintf(fp, "#\n");                      // End of record

            mnode = mnode->link;                     // Move to next main node
        }
    }

    fclose(fp);                                      // Close output file

    return SUCCESS;                                  // Indicate save success
}

void save_last_saved_file(const char *filename)
{
    FILE *fp = fopen("saved_file.txt", "w");         // Open last saved file record in write mode

    if (fp != NULL)                                  // Check if successfully opened
    {
        fprintf(fp, "%s\n", filename);               // Write filename to file
        fclose(fp);                                  // Close file
        printf(CYAN "Last used save file updated.\n" RESET);
                                                      // Inform user file updated
    }
    else                                             // If file couldn't open
    {
        printf(RED "Could not save last-used filename\n" RESET);
                                                      // Print error
    }
}
