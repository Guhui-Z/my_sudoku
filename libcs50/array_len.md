# CS50 Final Project

## CS50 Spring 2022

### array_len

An `array_len` consists of an array and an integer of the number of digits in the array.

### Usage

The *array_len* module, defined in `array_len.h` and implemented in `array_len.c`, exports the following functions:

```c
array_len_t *array_len_new(int max_size);
int array_len_get(array_len_t *array_len);
void array_len_insert(array_len_t *array_len, int digit);
void array_len_delete(array_len_t *array_len);
```

### Implementation

The *array_len* is represented as a `struct array_len` containing an array and an integer.

The `array_len_get` method returns a random digit in the array and decrement the integer size.

The `array_len_insert` method inserts a digit at the end of the array.

The `array_len_delete` method frees the array and then the struct itself.
