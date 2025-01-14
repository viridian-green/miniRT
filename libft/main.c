#include "libft.h"
#include <stdio.h>

int main(void) {
    // Test cases
    char const *s1 = "Hello, world!";
    unsigned int start1 = 7;
    size_t len1 = 5;

    char const *s2 = "This is a test";
    unsigned int start2 = 2;
    size_t len2 = 7;

    // Test ft_substr function with test cases
    char *substr1 = ft_substr(s1, start1, len1);
    char *substr2 = ft_substr(s2, start2, len2);

    // Print results
    if (substr1) {
        printf("Substring 1: %s\n", substr1);
        free(substr1); // Free memory allocated by ft_substr
    } else {
        printf("Substring 1 is NULL\n");
    }

    if (substr2) {
        printf("Substring 2: %s\n", substr2);
        free(substr2); // Free memory allocated by ft_substr
    } else {
        printf("Substring 2 is NULL\n");
    }

    return 0;
}