#include "tblbld.h"
#include <stdio.h>

void hello(void) {
    printf("Hello, World!");
}

void buildTable(int x, int y) {
    char r[x];
    char c[y];
    int i;

    for (i = 0; i < x-1; ++i)
        r[i] = 'x';
    for (i = 0; i < y-1; ++i)
        c[i] = 'y';
    r[x-1] = '\0';
    c[y-1] = '\0';
    printf("%s\n%s\n", r, c);
}