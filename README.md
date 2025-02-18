# Custom String Library in C

This project defines a custom string manipulation library in C, which allows you to create, modify, and manage strings stored in dynamically allocated memory. The custom string structure stores both the length of the string and the string content itself, enabling efficient string operations like copying, concatenating, and comparing.

## Features

- **Custom String Representation**: Strings are stored with their length as a `long int` followed by the string content.
- **Dynamic Memory Management**: The library uses `malloc` and `realloc` for dynamic memory allocation, ensuring efficient memory usage.
- **Basic String Operations**: Functions for setting, getting, copying, concatenating, comparing strings, and calculating string length.

## Functions

### `strLen`
```c
int strLen(char *str);
```
Calculates the length of a C string (excluding the null terminator).

### `msSetString`
```c
void *msSetString(char str[]);
```
Creates a custom string structure. The memory allocated contains the string length followed by the string content.

### `msGetString`
```c
char *msGetString(void *ptr);
```
Retrieves the string from a custom string structure.

### `msCopy`
```c
int msCopy(void **msStrPtr, void *msString);
```
Copies the content of one custom string to another, reallocating memory as needed.

### `msConcatenate`
```c
int msConcatenate(void **ptrMsString1, void *msString2);
```
Concatenates two custom strings by resizing the first string's memory and copying the second string.

### `msLength`
```c
int msLength(void *msString);
```
Returns the length of a custom string.

### `msCompare`
```c
int msCompare(void *msString1, void *msString2);
```
Compares two custom strings for equality by checking both the length and the characters.

### `msCompareString`
```c
int msCompareString(void *msString, char string[]);
```
Compares a custom string with a regular C string (i.e., `char[]`).

### `msError`
```c
void msError(char string[]);
```
Handles memory allocation errors by printing an error message and exiting the program.

## Example Usage

```c
#include "custom_string.h"

int main() {
    char str1[] = "Hello";
    void *msStr1 = msSetString(str1); // Create a custom string
    
    char str2[] = " World!";
    void *msStr2 = msSetString(str2); // Create another custom string
    
    msConcatenate(&msStr1, msStr2); // Concatenate the strings
    
    char *result = msGetString(msStr1); // Retrieve the concatenated string
    printf("%s\n", result); // Output: "Hello World!"
    
    free(result); // Don't forget to free the allocated memory!
    return 0;
}
```

## Memory Management

- The library dynamically allocates memory using `malloc` and `realloc`. Ensure to free the allocated memory after you're done using it to prevent memory leaks.
  
## Compilation

To compile the code, use the following command:

```bash
gcc -o custom_string main.c
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
