#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Return an estimated value of pi using n random Monte-Carlo draws
float estimate_pi(long n) 
{
    float r,x,y;
    long pi = 0;
    for(int i=0;i<n;i++)
    {
        x = (float) rand() / RAND_MAX;
        y = (float) rand() / RAND_MAX;
        r = sqrt(x*x+y*y);
        // If r < 1, the draw is within the circle's quadrant
        if (r < 1)
            pi += 1;
    }
    return (float) 4.*pi/n;
}

int main(int argc, char * argv[])
{
    srand(time(NULL));
    if (argc < 2)
    {
        printf("Please input number of sample points\n");
        exit(-1);
    }
    float n;
    sscanf(argv[1], "%e", &n);
    printf("Pi estimate: %7.6f\n", estimate_pi((long) n));
}
