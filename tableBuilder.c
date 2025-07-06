#include "tblbld.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BOX_RIGHT_UPPER_CORNER "┐"
#define BOX_LEFT_UPPER_CORNER "┌"
#define BOX_RIGHT_LOWER_CORNER "┘"
#define BOX_LEFT_LOWER_CORNER "└"
#define BOX_RIGHT_FORK "┤"
#define BOX_LEFT_FORK "├"
#define BOX_UPPER_FORK "┬"
#define BOX_LOWER_FORK "┴"
#define BOX_MIDDLE_FORK "┼"
#define LINE_HORIZONTAL "─"
#define LINE_VERTICAL "│"

void repeatStr(char *dest, int count, const char *str, int maxLen);

Table initTable(int length, int width, char *element) {
    Table table;
    table.Width = length;
    table.Height = width;

    // Allocate rows
    table.Rows = malloc(sizeof(Row) * length);
    if (!table.Rows) return table;

    for (int i = 0; i < length; ++i) {
        // Allocate columns for each row
        table.Rows[i].Columns = malloc(sizeof(Column) * width);
        if (!table.Rows[i].Columns) {
            // Handle partial allocation failure
            for (int j = 0; j < i; ++j) {
                free(table.Rows[j].Columns);
            }
            free(table.Rows);
            table.Rows = nullptr;
            return table;
        }

        for (int j = 0; j < width; ++j) {
            table.Rows[i].Columns[j].Value = element;
        }
    }

    return table;
}

void setTableElement(Table *table, int row, int column, char *element) {
    if (table->Height <= column || table->Width <= row) return;
    table->Rows[row].Columns[column].Value = element;
}

void freeTable(Table *table) {
    if (!table || !table->Rows) return;

    for (int i = 0; i < table->Width; ++i) {
        free(table->Rows[i].Columns);
    }

    free(table->Rows);
    table->Rows = nullptr;
}

char* buildTable(Table *table) {
    int columnLengths[table->Width];
    int i, j;
    for (i = 0; i < table->Width; ++i)
        columnLengths[i] = 0;

    // Define which type is the element
    char *value = malloc(MAXSTRINGLEN);
    for (i = 0; i < table->Height; ++i) {
        for (j = 0; j < table->Width; ++j) {
            // Current table element
            char *tableElement = table->Rows[i].Columns[j].Value;

            snprintf(value, MAXSTRINGLEN, "%s", tableElement);
            int len = (int)strlen(value);
            if (len > columnLengths[j])
                columnLengths[j] = len;
        }
    }
    free(value);

    char *result = malloc(MAXTABLESTRING);
    if (!result) return nullptr;

    int offset = 0, k = 0;
    char lineBuf[MAXSTRINGLEN]; // enough for repeated LINE_HORIZONTAL

    // Upper borders
    offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s", BOX_LEFT_UPPER_CORNER);
    for (i = 0; i < table->Width; ++i) {
        repeatStr(lineBuf, columnLengths[i], LINE_HORIZONTAL,128);
        if (i == table->Width - 1) {
            offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s%s\n", lineBuf, BOX_RIGHT_UPPER_CORNER);
        } else {
            offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s%s", lineBuf, BOX_UPPER_FORK);
        }
    }

    // Table rows and middle borders
    for (i = 0; i < table->Height; ++i) {
        // Write row values
        offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s", LINE_VERTICAL);
        for (j = 0; j < table->Width; ++j) {
            char *tableElement = (char *)table->Rows[i].Columns[j].Value;
            if (j == table->Width - 1) {
                offset += snprintf(result + offset, MAXTABLESTRING - offset, "%*s%s\n", columnLengths[j], tableElement, LINE_VERTICAL);
            } else {
                offset += snprintf(result + offset, MAXTABLESTRING - offset, "%*s%s", columnLengths[j], tableElement, LINE_VERTICAL);
            }
        }

        // Middle borders (skip after last row)
        if (i != table->Height - 1) {
            offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s", BOX_LEFT_FORK);
            for (k = 0; k < table->Width; ++k) {
                repeatStr(lineBuf, columnLengths[i], LINE_HORIZONTAL,128);
                if (k == table->Width - 1) {
                    offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s%s\n", lineBuf, BOX_RIGHT_FORK);
                } else {
                    offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s%s", lineBuf, BOX_MIDDLE_FORK);
                }
            }
        }
    }

    // Bottom borders
    offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s", BOX_LEFT_LOWER_CORNER);
    for (i = 0; i < table->Width; ++i) {
        repeatStr(lineBuf, columnLengths[i], LINE_HORIZONTAL,128);
        if (i == table->Width - 1) {
            offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s%s", lineBuf, BOX_RIGHT_LOWER_CORNER);
        } else {
            offset += snprintf(result + offset, MAXTABLESTRING - offset, "%s%s", lineBuf, BOX_LOWER_FORK);
        }
    }

    return result;
}

// Help functions

void repeatStr(char *dest, int count, const char *str, int maxLen) {
    int len = (int)strlen(str);
    int total = 0;

    for (int i = 0; i < count && total + len < maxLen - 1; ++i) {
        memcpy(dest + total, str, len);
        total += len;
    }

    dest[total] = '\0';
}