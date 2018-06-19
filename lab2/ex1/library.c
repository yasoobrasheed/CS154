/*
 * Exercise 1 - code to modify!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Takes two NULL-terminated strings as arguments and
 * determines the sum of their lengths.
 */
int multiStrlen(char *first, char *second) {
    char *p, *q;

    p = first;
    while (*p != '\0') {
        *p++;
    }
    q = second;
    while (*q != '\0') {
        *q++;
    }

    return (p-first)+(q-second);
}

/*
 * Sorts two lists of characters in two steps:
 * 1) Allocate a result array and copy the two strings over
 * 2) For each character, if there is a larger character
 * later in the string, perform a swap
 */
char *twoFingerSort(char *first, char *second)
{
    int i, j;
    int length = multiStrlen(first, second) + 1;
    char *result = (char*)malloc(length);
    char *p, *q, temp;

    q = result;
    p = first;
    while ((*q++ = *p++) != '\0') ;
    p = second;
    while ((*q++ = *p++) != '\0') ;
    *q = '\0';

    for (i = 0; i < length; i++) {
        for (j = i; j < length; j++) {
            if (result[i] < result[j]) {
                temp = result[i];
                result[i] = result[j];
                result[j] = temp;
            }
        }
    }
    
    return result;
}
