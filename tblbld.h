#ifndef TABLEBUILDER_LIBRARY_H
#define TABLEBUILDER_LIBRARY_H
// Max length of a string that contains the formatted table
#define MAXTABLESTRING 100000
#define MAXSTRINGLEN 1000

// Defines a column
typedef struct {
    char *Value;
} Column;

// Defines a row
typedef struct {
    Column *Columns;
} Row;

// Defines a table
typedef struct {
    unsigned int Width;
    unsigned int Height;
    Row *Rows;
} Table;

//Declares a table.
//width - table's width
//height - table's height
//*element - the string to fill the table with
Table initTable(int width, int height, char *element);
//Frees the memory used by a table
//*table - pointer to the table
void freeTable(Table *table);
//Builds a string that contains a table
//*table - pointer to the table to build
char* buildTable(Table *table);
//Sets a table's element at a specific position to a new value
//*table - pointer to the table to edit
//row - row where the table will be edited
//column - column where the table will be edited
//*element - the new element
void setTableElement(Table *table, int row, int column, char *element);


#endif //TABLEBUILDER_LIBRARY_H
