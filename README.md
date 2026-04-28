# 4-Element Dot Product HLS Accelerator

![C++](https://img.shields.io/badge/C%2B%2B-Testbench%20%2B%20Golden%20Model-blue)
![HLS](https://img.shields.io/badge/HLS-Hardware%20Acceleration-purple)
![Vitis HLS](https://img.shields.io/badge/Vitis%20HLS-C%2B%2B%20to%20RTL-orange)
![Fixed Width Types](https://img.shields.io/badge/Fixed--Width%20Types-int8__t%20%2B%20int16__t-lightgrey)
![Verification](https://img.shields.io/badge/Verification-Software%20Golden%20Model-green)

## Overview

This project implements a 4-element dot product accelerator in C++ for High-Level Synthesis, HLS. The hardware function computes the dot product of two 4-element signed 8-bit input vectors and stores the result through an output pointer.

The project includes:

- HLS hardware function
- Shared header file with fixed-width types and constants
- C++ software golden model
- Randomized C++ testbench
- Hardware-vs-software result comparison

The goal of this project is to practice writing synthesizable C++ for HLS and verifying the hardware-style function against a software reference model before generating RTL.

## Dot Product Operation

The design computes:

```text
result = A[0] * B[0] + A[1] * B[1] + A[2] * B[2] + A[3] * B[3]
```

For this project:

```text
ELEMENTS = 4
```

Each input element uses an 8-bit signed type:

```cpp
typedef int8_t data_T;
```

The output result uses a 16-bit signed type:

```cpp
typedef int16_t result_T;
```

## Hardware Function

The hardware-targeted function is defined in `dot_product.cpp`:

```cpp
void HW_dot_product(data_T A[ELEMENTS], data_T B[ELEMENTS], result_T *result) {
    *result = 0;

    for (int i = 0; i < ELEMENTS; i++) {
        #pragma HLS UNROLL
        *result += A[i] * B[i];
    }
}
```

The function uses a `void` return type and writes the result through a pointer. This maps naturally to hardware-style output behavior, where results are often written to an output port or memory-mapped location instead of being returned like normal software.

## HLS Optimization

The loop is fully unrolled using:

```cpp
#pragma HLS UNROLL
```

This tells the HLS tool to replicate hardware for the loop body instead of executing the four multiply-accumulate operations sequentially.

For a 4-element dot product, full unrolling can create parallel multipliers and an adder structure, improving throughput at the cost of additional hardware resources.

## Header File

The shared header file `dot_product.h` defines the project constants, data types, and function prototype.

```cpp
#define ELEMENTS 4

typedef int8_t  data_T;
typedef int16_t result_T;

void HW_dot_product(data_T A[ELEMENTS], data_T B[ELEMENTS], result_T *result);
```

This keeps the hardware implementation and testbench consistent.

## Testbench

The C++ testbench generates randomized input vectors, computes the expected result using a software golden model, calls the HLS hardware function, and compares the outputs.

The software golden model uses the same dot product equation:

```cpp
void SW_dot_product(data_T A[ELEMENTS], data_T B[ELEMENTS], result_T *result) {
    *result = 0;

    for (int i = 0; i < ELEMENTS; i++) {
        *result += A[i] * B[i];
    }
}
```

The testbench runs:

```cpp
#define RANDOMIZED_TEST_CASES 10
```

For each randomized test case, it:

1. Generates four random signed 8-bit values for `A`
2. Generates four random signed 8-bit values for `B`
3. Computes the software golden result
4. Computes the hardware function result
5. Checks that both results match

## Example Testbench Output

The testbench prints each input vector and both dot product results.

Example output format:

```text
RUNNING NEW RANDOM TESTBENCH

A[0] = ...
B[0] = ...

Software Dot Product For Case 0: ...
Hardware Dot Product For Case 0: ... (matches software result)
TEST PASSED: 1/10 tests passed so far
```

## How to Compile and Run with g++

Before running HLS, the design can be compiled as a normal C++ program for functional testing.

```bash
g++ dot_product.cpp dot_product_testbench.cpp -o dot_product_test
./dot_product_test
```

This verifies that the hardware-style C++ function matches the software golden model.

## How to Use in Vitis HLS

Typical Vitis HLS flow:

1. Create a new Vitis HLS project.
2. Add `dot_product.cpp` as the design source.
3. Add `dot_product.h` as the header.
4. Add `dot_product_testbench.cpp` as the testbench.
5. Set the top function to:

```text
HW_dot_product
```

6. Run C simulation.
7. Run C synthesis.
8. Inspect latency, initiation interval, and resource usage.
9. Optionally run C/RTL co-simulation.


## Skills Demonstrated

- C++ hardware modeling for HLS
- Fixed-width integer design
- HLS top-function structure
- Pointer-based output modeling
- Loop unrolling with HLS pragmas
- Software golden model verification
- Randomized C++ testbench generation
- Hardware/software result comparison
- Basic accelerator design workflow

## Project Summary

This project demonstrates a 4-element dot product accelerator written in synthesizable C++ for HLS. The design uses signed 8-bit input vectors, a hardware-style output pointer, and a fully unrolled multiply-accumulate loop. A randomized C++ testbench compares the HLS hardware function against a software golden model to verify functional correctness before synthesis.
