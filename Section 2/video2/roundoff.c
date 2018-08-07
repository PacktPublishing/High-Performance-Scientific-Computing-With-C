#include <stdio.h>

int main()
{
    float a;
    float b;
    a = 1e13;
    b = 1e13;
    printf("%e %e\n", (a-b)+1234567, a-(b-1234567));
}
