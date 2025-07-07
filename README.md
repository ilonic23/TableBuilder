# Table Builder
A simple library to build tables in C.
Example usage:
```c
#include <stdio.h>
#include "tblbld.h"

int main(void) {
    Table table = initTable(8,8, "13"); // Create a table with 8 rows and 8 columns and fill each element wit "13"
    setTableElement(&table, 0, 0, "Hello, World!"); // Set a table's element at position 0,0 to Hello, World!
    printf("%s\n", buildTable(&table)); // Build and print out the table
    freeTable(&table); // Don't forget to free the memory when finished using
    return 0;
}
```
Output:
```
┌─────────────┬──┬──┬──┬──┬──┬──┬──┐
│Hello, World!│13│13│13│13│13│13│13│
├─────────────┼──┼──┼──┼──┼──┼──┼──┤
│           13│13│13│13│13│13│13│13│
├─────────────┼──┼──┼──┼──┼──┼──┼──┤
│           13│13│13│13│13│13│13│13│
├─────────────┼──┼──┼──┼──┼──┼──┼──┤
│           13│13│13│13│13│13│13│13│
├─────────────┼──┼──┼──┼──┼──┼──┼──┤
│           13│13│13│13│13│13│13│13│
├─────────────┼──┼──┼──┼──┼──┼──┼──┤
│           13│13│13│13│13│13│13│13│
├─────────────┼──┼──┼──┼──┼──┼──┼──┤
│           13│13│13│13│13│13│13│13│
├─────────────┼──┼──┼──┼──┼──┼──┼──┤
│           13│13│13│13│13│13│13│13│
└─────────────┴──┴──┴──┴──┴──┴──┴──┘
```

# Headers description:
## tblbld.h
The main header of the library that allows to create, build and edit a table.
### Functions:
- initTable(int width, int height, char *element) - Returns a table structure width by height elements and fills each element with the given argument.
- setTableElement(Table *table, int row, int column, element) - Edit an element at a specific position.
- buildTable(Table *table) - returns the string representation of the table which allows to print it.
- freeTable(Table *table) - frees the memory of the table.

### Limitations:
- MAXSTRINGLEN - 1000. Used to define the max length of a string buffer used by the buildTable function.
Basically divide this by 3 to know the real limitations because each UTF-8 character takes 3 bytes.
- MAXTABLESTRING - 100000. Used to limit the table string length ( in bytes ).


Made with love by Ilonic <3