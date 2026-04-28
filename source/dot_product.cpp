// This file acts like a module file in RTL and contains the implementation of the dot product function
#include "dot_product.h"

// void return type models hardware behavior as we can have as many pointers as we want to store results, 
// Function will take array of char elements in, and will take in an address.

// Hardware model that will be turned into RTL, 
void HW_dot_product(data_T A[ELEMENTS], data_T B[ELEMENTS], result_T *result) {

    *result = 0; // make sure to initialize the result to 0 before accumulating the products

    for (int i = 0; i < ELEMENTS; i++) {
        #pragma HLS UNROLL
        *result += A[i] * B[i]; // Will add and accumulate the products of corresponding elements from A and B
    }

}