// This file just acts like an RTL interface file and contains the function prototype for the dot product function, as well as some type definitions and constants

#ifndef DOT_PRODUCT_H // Include guard to prevent multiple inclusions of this header file, aka load once
#define DOT_PRODUCT_H // Name is just given arbitrarily, it can be any unique name

#include <cstdint>


#define ELEMENTS 4

using namespace std; // allows us to write cout << "hello";

typedef int8_t data_T; // Define a type alias for char, which will be used for the elements of the arrays
typedef int16_t result_T; // Define a type alias for short, which will be used for the result of the dot product

// We must pass a pointer to result because we made the function  void and will not return a value, so we need to pass a reference to where the result should be stored
// Alternatively, we could have made the function return a value of type result_T, but in this case we are using a pointer to store the result instead
void HW_dot_product(data_T A[ELEMENTS], data_T B[ELEMENTS], result_T *result); // Function prototype for the dot product function, which takes two arrays and a reference to store the result

#endif // DOT_PRODUCT_H