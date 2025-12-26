#ifndef INVERTED_SEARCH_H          // Header guard start
#define INVERTED_SEARCH_H          // Prevent multiple inclusion

#define SUCCESS 1                  // Success status
#define FAILURE 0                  // Failure status
#define FILE_EMPTY -1             // File empty status code

#include <stdio.h>                // Standard I/O library
#include <stdlib.h>               // Memory allocation, exit, etc.
#include <string.h>               // String functions
#include <ctype.h>                // Character handling functions

/* COLOR CODES */
#define RED     "\033[1;31m"      // Red text color
#define GREEN   "\033[1;32m"      // Green text color
#define BLUE    "\033[1;34m"      // Blue text color
#define CYAN    "\033[1;36m"      // Cyan text color
#define MAGENTA "\033[1;35m"      // Magenta text color
#define YELLOW  "\033[1;33m"      // Yellow text color
#define RESET   "\033[0m"         // Reset color

/* Linked list for input files */
typedef struct FileList
{
    char filename[100];           // Store the filename
    struct FileList *link;        // Pointer to next file node
} FileList;

/* Subnode - stores filename + count */
typedef struct subnode
{
    int word_count;               // Occurrence count of word in file
    char file_name[20];           // Name of file containing the word
    struct subnode *link;         // Pointer to next subnode
} sub_node;

/* Main node - stores word + list of subnodes */
typedef struct main_node
{
    int file_count;               // Number of files containing the word
    char word[50];                // Word itself
    sub_node *sublink;            // Linked list of files and counts
    struct main_node *link;       // Pointer to next main node
} main_node;

/* Hashtable */
typedef struct hashtable
{
    int index;                    // Index number of hash table slot
    main_node *link;              // Pointer to main node in slot
} hash_t;

/* File validation */
int validate_file(const char *filename);                // Check if file is valid
int read_validate(int argc, char **argv, FileList **file_list);   // Validate all input files
int insert_file(FileList **head, const char *filename); // Insert a file into linked list
void display_file_list(FileList *head);                 // Display list of input files

/* Core Functions */
int create_Database(hash_t *hash_table, FileList *file_list); // Create database from files
int display_database(hash_t *hash_table);                     // Display inverted index
void search_word(hash_t *hash_table);                         // Search for a word in DB
int update_database(hash_t *hash_table, FileList **file_list); // Update DB with new file
int save_Database(hash_t *hash_table, const char *backup_filename); // Save DB to file

#endif                       // End of header guard
