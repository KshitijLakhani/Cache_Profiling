/* -----------
 * DESCRIPTION
 * -----------
 *
 * Template code for basic matrix multiplication. This code contains the
 * function "populate_array" that will initialized matrices with random values
 * and a minimal "main" routine for selecting between normal matrix
 * multiplication and blocked matrix multiplication.
 *
 * Standard C++ statically sized arrays are used here for simplicity. Feel free
 * to use something more convenient like std::vector to avoid the need to
 * recompile between different array sizes.
 *
 * ---------
 * EXECUTION
 * ---------
 *
 * If the output file is called a.out, then the command
 *
 * ./a.out
 *
 * will execute normal matrix multiplication. If an integer argument is given,
 * such as
 *
 * ./a.out 8
 *
 * then the main routine will execute blocked matrix multiplication with a block
 * size of 8.
 *
 * -----------
 * COMPILATION
 * -----------
 *
 * Compile this code using the following command:
 *
 * g++ -std=c++1y -O2 mm_template.cpp
 *
 */

#include<iostream>
#include<random>
#include<time.h>
#include<sstream>

// Declare global array size.
const int ARRAY_SIZE = 1024;

// Basic function to populate a 2D iterator with uniformly distributed real
// numbers between -1.0 and 1.0.
template <class T>
void populate_array( T &x )
{
    // Initialize a random engine
    std::random_device rdev;
    std::default_random_engine u{rdev()};
    std::uniform_real_distribution<double> d(-1.0,1.0);

    // Randomize all entries
    for (auto &i : x) {
        for (auto &j : i) {
            j = d(u);
        }
    }
}

// Naive Matrix Multiplication
template <class T>
void multiply( T &c, T &a, T &b)
{
    for(int i = 0; i < ARRAY_SIZE; ++i)
        for(int j = 0; j < ARRAY_SIZE; ++j)
            for(int k = 0; k < ARRAY_SIZE; ++k)
            {
                c[i][j] += a[i][k] * b[k][j];
            }

}


// Block Matrix Multiplication
template <class T>
void block_multiply(int B, T &c, T &a, T &b)
{
for (int count1=0; count1 < ARRAY_SIZE; count1 = count1 + B)
{
for (int count2=0; count2 < ARRAY_SIZE; count2 = count2 + B)
{
for (int count3=0; count3 < ARRAY_SIZE; count3 = count3 + 1)
{
for (int count4=count1; count4 < std::min(count1+B,ARRAY_SIZE); count4=count4 +1)
{
int temp = 0;
for (int count5=count2; count5 < std::min(count2+B,ARRAY_SIZE); count5=count5 +1)
{
temp = temp + a[count3][count5]*b[count5][count4];
}
c[count3][count4] = c[count3][count4] + temp;
}
}
}
}
}
// Heap Initialize Arrays
static double a[ARRAY_SIZE][ARRAY_SIZE];
static double b[ARRAY_SIZE][ARRAY_SIZE];
static double c[ARRAY_SIZE][ARRAY_SIZE];

int main(int argc, char *argv[])
{
    // Parse command line options for block size.
    // NOTE: No input sanitization is done. This may error horribly.
    int block = 0;
    if (argc > 1) {
        block = std::stoi(argv[1]);
        std::cout  << "Using Block Multiplication with Block size: "
                   << block
                   << std::endl;
    }

    // Populate the input arrays
    populate_array(a);
    populate_array(b);

    // Time how long matrix multiplication takes
    clock_t t0 = clock();
    if (block == 0) {
        multiply(c,a,b);
    } else {
        block_multiply(block,c,a,b);
    }

    // Print out multiplication time
    int time_ms = (clock()-t0) / (CLOCKS_PER_SEC / 1000);
    std::cout   << "CPU Time: "
                << time_ms << " ms"
                << std::endl;

    return 0;
}
