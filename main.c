#include "inverted_search.h"    // Header file containing all declarations

int main(int argc, char **argv)
{
    FileList *file_list = NULL;        // Head pointer for file list
    hash_t hash_table[28];             // Hash table with 28 indices (a-z, digits, specials)
    int choice;                        // Menu choice input
    int db_created = 0;                // Flag: 0 = DB not created, 1 = created

    // Initialize hash table
    for (int i = 0; i < 28; i++)
    {
        hash_table[i].index = i;       // Store index value
        hash_table[i].link = NULL;     // Initially no main nodes linked
    }

    // Validate command line files and build initial file_list
    if (read_validate(argc, argv, &file_list) == FAILURE)
    {
        printf(RED "Exiting program...\n" RESET);
        return 0;                      // Exit if validation fails
    }

    printf(GREEN "\nFiles successfully validated.\n" RESET);
    display_file_list(file_list);      // Show validated file list

    // Main menu loop
    do
    {
        // Display menu options
        printf(YELLOW "==============================================\n" RESET);
        printf(CYAN   "        Select your choice among options      \n" RESET);
        printf(YELLOW "==============================================\n" RESET);

        printf(MAGENTA "1. Create DATABASE\n" RESET);
        printf(MAGENTA "2. Display Database\n" RESET);
        printf(MAGENTA "3. Update DATABASE\n" RESET);
        printf(MAGENTA "4. Search\n" RESET);
        printf(MAGENTA "5. Save Database\n" RESET);
        printf(MAGENTA "6. Exit\n" RESET);       // Exit option

        printf(YELLOW "==============================================\n" RESET);
        printf(CYAN "Enter your choice: " RESET);

        scanf("%d", &choice);          // Read user choice

        // Perform actions based on user choice
        switch (choice)
        {
            case 1:
                // Ensure DB is not created again
                if (db_created)
                {
                    printf(YELLOW "Database already created. Skipping...\n" RESET);
                }
                else
                {
                    printf(GREEN "\n--- Creating Database ---\n" RESET);

                    // Create database from file list
                    if (create_Database(hash_table, file_list) == SUCCESS)
                    {
                        db_created = 1;     // Mark DB as created
                    }
                }
                break;

            case 2:
                printf(GREEN "\n--- Display Database ---\n" RESET);
                display_database(hash_table);   // Print all words + file counts
                break;

            case 3:
                printf(GREEN "\n--- Update Database ---\n" RESET);
                update_database(hash_table, &file_list);    // Add new file + update DB
                break;

            case 4:
                printf(GREEN "\n--- Search Word ---\n" RESET);
                search_word(hash_table);       // Search for a word in database
                break;

            case 5:
                printf(GREEN "\n--- Saving Database ---\n" RESET);
                save_Database(hash_table, "backup.txt");   // Save DB into backup file
                printf(GREEN "Database saved successfully to backup.txt\n" RESET);
                break;

            case 6:
                printf(GREEN "\nExiting Database...\n" RESET);
                return 0;                      // Exit program

            default:
                printf(RED "Invalid choice. Try again.\n" RESET);
        }

        // Ask user if they want to continue
        char cont;
        printf(CYAN "\nDo you want to continue? " RESET);
        printf("Enter y/Y to continue and n/N to discontinue: ");

        getchar();                  // Clear buffer
        scanf("%c", &cont);         // Read continuation choice

        if (cont == 'n' || cont == 'N')   // Exit loop
            break;
if (!((cont == 'y') || (cont == 'Y')))
{
    printf(RED "\n X Invalid Choice!\n" RESET);
    printf(YELLOW " Please enter " GREEN "y/Y " YELLOW "to continue or " RED "n/N " YELLOW "to exit.\n\n" RESET);
    break;
}

    } while (1);   // Infinite loop until user stops

    return 0;      // End program
}
