#include <stdio.h>
#include <stdlib.h>




int main(int argc, char * argv[])
{
    float x=0;
    #pragma omp parallel for reduction(+:x)
    for(int i=0;i<100;i++)
    {
        x += i;
    }
    printf("%e\n", x);
}
