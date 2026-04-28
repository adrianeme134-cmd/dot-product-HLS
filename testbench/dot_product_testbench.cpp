#include <iostream>
#include "dot_product.h"
#include <random>

#define RANDOMIZED_TEST_CASES 10

// we must build both dot_product.cpp and dot_product_test.cpp together when compiling, since dot_product_test.cpp calls the function defined in dot_product.cpp, so we need to make sure to include both files in the compilation command, for example:
// g++ dot_product.cpp dot_product_test.cpp -o dot_product_test
// else we get errors

// software golden model of our 4 element dot product
void SW_dot_product(data_T A[ELEMENTS], data_T B[ELEMENTS], result_T *result) {

    *result = 0; // make sure to initialize the result to 0 before accumulating the products

    for (int i = 0; i < ELEMENTS; i++) {
        *result += A[i] * B[i]; // Will add and accumulate the products of corresponding elements from A and B
    }

}

int i = 0;
int tests_passed = 0;

int main() {

    cout << "RUNNING NEW RANDOM TESTBENCH" << endl;

    uniform_int_distribution<int> u(-128,127); // Generate random integers between -128 and 127, which are the limits of the char data type, since we defined data_T as char, we want to make sure to generate values within that range to avoid overflow issues when multiplying two chars together, since the result of multiplying two chars can exceed the range of a char, but since we defined result_T as short, which has a larger range than char, we can safely store the result of the multiplication without overflow issues
    default_random_engine e; // Create a random number generator engine, which will be used to generate random numbers for our testbench

    data_T A[ELEMENTS]; 
    data_T B[ELEMENTS]; 

    while(i < RANDOMIZED_TEST_CASES) { // Generate and test 10 random test cases
        
        for( int j = 0; j < ELEMENTS; j++) {
            A[j] = u(e); // assign random values to array A elements
            B[j] = u(e); // assign random values to array B elements
            cout << "A[" << j << "] = " << (int)A[j] << ", B[" << j << "] = " << (int)B[j] << endl; // Print the values of A and B for this test case, we need to cast to int when printing since data_T is defined as char, and if we print it directly it will print the ASCII character instead of the integer value, so we cast to int to see the actual integer value of the char for better readability in our testbench output
        }

        

        result_T SW_result; // Variable to store the result of the dot product
        result_T HW_result; // Variable to store the result of the hardware dot product

        // our functiuon takes in pointers to store the result, so we need to pass the address of the result variable when calling the function
        SW_dot_product(A, B, &SW_result); // Call the software dot product function golden model

        cout << "Software Dot Product For Case " << i << ": " << SW_result << endl; // Print the result of the software dot product


        HW_dot_product(A, B, &HW_result); // Call the hardware dot product function

        if(SW_result == HW_result) {
            cout << "Hardware Dot Product For Case " << i << ": " << HW_result << " (matches software result)" << endl; // Print the result of the hardware dot product
            tests_passed++; // Increment the count of passed tests if the hardware result matches the software result
            cout << "TEST PASSED: " << tests_passed << "/" << 10 << " tests passed so far" << endl; // Print the number of tests passed so far
        } else {
            cout << "Hardware Dot Product For Case " << i << ": " << HW_result << " (does NOT match software result)" << endl; // Print the result of the hardware dot product   
        }
        
        i++; // increment the test case counter

    }
    
    return 0;
}