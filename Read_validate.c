#include "inverted_search.h"   // Contains structure definitions & function prototypes

/*---------------------------------------------------------
 *  Function: read_validate
 *  Purpose : Validate all input files & insert into list
 *---------------------------------------------------------*/
int read_validate(int argc, char **argv, FileList **file_list)
{
    // Loop through all command-line arguments (skipping program name)
    for (int i = 1; i < argc; i++)
    {
        char *filename = argv[i];   // Take current filename

        printf(CYAN "\nValidating %s\n" RESET, filename);

        int result = validate_file(filename);  // Check if file is valid

        // If file is invalid (wrong extension / cannot open)
        if (result == FAILURE)
        {
            printf(RED "Skipping file %s due to validation error\n" RESET, filename);
            continue;   // Move to next file
        }
        // If file is empty
        else if (result == FILE_EMPTY)
        {
            printf(YELLOW "!! File is Empty. Skipping empty file %s\n" RESET, filename);
            printf(RED "FAILURE\n" RESET);
            continue;
        }

        // If validation passed → Insert file into list
        if (insert_file(file_list, filename) == FAILURE)
        {
            printf(YELLOW "File %s is already in the list. Skipping duplicate...\n" RESET, filename);
        }
        else
        {
            printf(GREEN "Done\n" RESET);
        }
    }

    return SUCCESS;   // Always return success after processing all files
}

/*---------------------------------------------------------
 *  Function: validate_file
 *  Purpose : Check extension, existence, empty file
 *---------------------------------------------------------*/
int validate_file(const char *filename)
{
    char *ext = strrchr(filename, '.');   // Get pointer to file extension

    // Check if extension exists AND is ".txt"
    if (!ext || strcmp(ext, ".txt") != 0)
    {
        printf(RED "Error: Invalid file extension for %s. Expected .txt\n" RESET, filename);
        return FAILURE;   // Invalid extension
    }

    FILE *fptr = fopen(filename, "r");    // Try opening file in read mode
    if (!fptr)
    {
        perror(RED "Error: Cannot open file" RESET);   // Print system error message
        return FAILURE;   // File does not exist
    }

    // Check file size (to verify empty file)
    fseek(fptr, 0, SEEK_END);   // Move to end of file
    long size = ftell(fptr);    // Get current position = file size

    if (size == 0)
    {
        fclose(fptr);
        return FILE_EMPTY;      // File exists but empty
    }

    fclose(fptr);
    return SUCCESS;             // File exists, readable, and non-empty
}

/*---------------------------------------------------------
 *  Function: insert_file
 *  Purpose : Insert validated file into linked list
 *---------------------------------------------------------*/
int insert_file(FileList **head, const char *filename)
{
    FileList *temp = *head;

    // Check if file already exists in list (duplicate prevention)
    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            return FAILURE;   // Duplicate found
        }
        temp = temp->link;
    }

    // Create new node for file
    FileList *newNode = (FileList *)malloc(sizeof(FileList));
    if (!newNode)
    {
        printf(RED "Error: Memory allocation failed\n" RESET);
        return FAILURE;   // Memory failure
    }

    strcpy(newNode->filename, filename);   // Store filename
    newNode->link = NULL;                  // Last node for now

    // Insert node in list
    if (*head == NULL)
    {
        *head = newNode;   // First file in list
    }
    else
    {
        temp = *head;
        while (temp->link != NULL)   // Go to last node
        {
            temp = temp->link;
        }
        temp->link = newNode;        // Add at end
    }

    printf(GREEN "%s added to the list successfully!\n" RESET, filename);
    return SUCCESS;   // Successfully inserted
}
