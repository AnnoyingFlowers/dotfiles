// #include <stdio.h>
// #include <string.h>

// int main() {
//     char arr1[] = "Hello World!";
//     char arr2[] = "Hello World!";
//     char arr3[] = "Hello World?";

//     printf("%d, ", memcmp(arr1, arr2, strlen(arr1)));
//     printf("%d, ", memcmp(arr1, arr3, strlen(arr1)));
//     printf("%d, ", memcmp(arr1, arr3, 5));
//     printf("%d, ", memcmp(arr1, "", 0));
//     printf("%d, ", memcmp(arr1, arr3, strlen(arr1) + 1));
printf("%d, ", memcmp("Hello", "Hell", 5));

//     return 0;
// }