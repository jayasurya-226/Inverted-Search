/*                                  Inverted Search System Documentation

1. Project Title : Inverted Search System

2. NAME : B.JAYASURYA

3. ROLL : 25017B_167

4. DATE :  23/11/2025

5. Project Overview

The Inverted Search System is a C-based file indexing and search application designed to efficiently search words across
multiple text files. It uses a hash table and linked lists to store words, track the files they appear in,
and count occurrences. Users can search for exact words or perform prefix-based searches.
Search results are presented in a tabular format with color coding, enhancing readability.

Key Features:

1. Supports multiple text files and validates them for correctness.

2. Creates an inverted index mapping words to files and occurrences.

3. Displays results in a tabular, color-coded format.

4. Supports prefix-based word suggestions.

5. Allows saving and loading the database for future use.

4. Technologies and Tools

Programming Language: C (ANSI C Standard)

Compiler: GCC (Linux/Windows)

Libraries: stdio.h, stdlib.h, string.h, ctype.h

Data Structures: Hash Table, Linked List

OS: Cross-platform (Windows/Linux)

5. Data Structures

5.1 FileList

Linked list storing input file names:

typedef struct FileList
{
    char filename[100];
    struct FileList *link;
} FileList;


Purpose:

Maintains a list of valid input files to process.

Prevents duplicate entries.

5.2 Sub Node

Stores file occurrence information for a word:

typedef struct sub_node
{
    char file_name[100];
    int word_count;
    struct sub_node *link;
} sub_node;


Purpose:

Tracks files where a word occurs.

Stores the number of occurrences of the word in each file.

5.3 Main Node

Stores individual words and their file references:

typedef struct main_node
{
    char word[50];
    int file_count;
    struct sub_node *sublink;
    struct main_node *link;
} main_node;


Purpose:

Holds the word.

file_count indicates how many files contain the word.

sublink points to the subnode list (files containing the word).

5.4 Hash Table
typedef struct hash_t
{
    struct main_node *link;
} hash_t;


Purpose:

Array of 28 nodes (0 - 25 for letters, 26 for digits, 27 for special characters).

Facilitates fast word lookup using the first character.

6. Project Modules and Functions

6.1 File Management
insert_file(FileList **head, const char *filename)

Adds a file to the linked list if it does not already exist.

display_file_list(FileList *head)

Prints all files currently in the file list with arrow separation.

validate_file(const char *filename)

Checks if a file exists, is readable, and is a .txt file.

6.2 Database Creation

create_Database(hash_t *hash_table, FileList *file_list)

Reads each file and processes every word.

Removes trailing punctuation from words.

Hashes the word to determine index in the hash table.

Adds the word to the main node list if not already present.

Updates subnodes to track file occurrences.

Prints messages about progress and success.

6.3 Display Database

display_database(hash_t *hash_table)

Traverses the hash table and prints all words with their file counts.

For each word, lists the files it appears in and the number of occurrences.

Uses color coding to differentiate words, files, and counts.

6.4 Searching

search_word(hash_t *hash_table)

Allows user to input a word.

Computes hash index based on first character.

Searches the main node list for the word.

Displays results in a tabular, colored format with file names and counts:

+----------------------+-------------+
| File Name            | Count       |
+----------------------+-------------+
| file1.txt            | 3           |
| file2.txt            | 1           |
+----------------------+-------------+

Displays selected word occurrences in a color-coded table.

Useful for autocomplete or partial search functionality.

6.5 Save and Load Database

save_Database(hash_t *hash_table, const char *filename)

Saves the current database into a .txt file.

Stores words, file names, and word counts for future loading.

load_last_saved_file(char *filename)

Loads the filename of the last saved database.

Defaults to backup.txt if no saved file exists.

save_last_saved_file(const char *filename)

Updates saved_file.txt with the last saved filename for future sessions.

7. Program Flow

Load last saved database.

Validate input files-> insert into FileList.

Create database -> insert words and file occurrences into hash table.

Display database (optional).

Search word -> tabular output with counts.

Prefix-based search -> suggest and select words.

Save database -> persist data in .txt file.

Exit program -> optionally update last used database file.

8. Sample Input / Output

Command-line Input:

./inverted_search file1.txt file2.txt file3.txt


Search Output Table:

Word 'Dhoni' is present in 2 file/s

+----------------------+-------------+
| File Name            | Count       |
+----------------------+-------------+
| file21.txt           | 1           |
| file3.txt            | 1           |
+----------------------+-------------+

9. Advantages

Efficient word lookup with hashing and linked lists.

Supports multiple files and maintains occurrence count.

Prefix-based search helps in autocomplete functionality.

Displays results in tabular, color-coded format.

Can save and load databases across sessions.

10. Limitations

Maximum of 100 matching words for prefix search.

Only supports .txt files.

File name limit: 100 characters.

Case-insensitive search but case-preserving display.

11. Future Enhancements

Support multi-word or phrase search.

Dynamic resizing of the hash table.

Sort output by word frequency or alphabetical order.

GUI-based interactive search.

Handle large datasets efficiently.

12. Project File Structure
inverted_search/
├── inverted_search.h      // Header file: structs, macros, function prototypes
├── main.c                 // Program entry point, menu and flow control
├── database.c             // Functions to create and display database
├── search.c               // Functions to search words and prefix search
├── file_ops.c             // File validation and linked list management
├── save_load.c            // Save/load database functions
├── saved_file.txt         // Stores last used database file
└── Project documentation

13. References

ANSI C Programming: K&R C, 2nd Edition

Data Structures in C (Linked Lists, Hash Tables)

ANSI Escape Sequences for terminal colors
*/