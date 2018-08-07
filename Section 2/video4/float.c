#include <float.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// This union will let us store a float and also access it as if it were an integer
typedef union Float_t {
    float f;
    uint32_t i;
} Float_t;

void print_float(char *label, Float_t number)
{
    int mantissa = number.i & ((1<<23) - 1); // Shear off the first 24 bits for the mantissa
    int exponent = (number.i >> 23) & 0xFF; // Shear off the last 8 bits for the exponent
    int eval = exponent -127; // Normalize the exponent
    if (exponent == 0) eval = -126;
    printf(label);
    printf(":\t%8e\t0x%08x\t%7d\t\t%3d (%3d)\n", number.f, number.i, mantissa, exponent, eval);
}

int main(int argc, char * argv[])
{
    Float_t min, max, subn; 
    min.f = FLT_MIN;
    max.f = FLT_MAX;
    subn.i = 1;
    printf("Number:\t\tFloat\t\tBinary\t\tMantissa\tExponent\n");
    print_float("FLT_MIN", min);
    print_float("FLT_MAX", max);
    print_float("Subnormal", subn);
    max.f *= 2;
    print_float("Overflow", max);
    subn.f /= 2;
    print_float("Underflow", subn);
}
