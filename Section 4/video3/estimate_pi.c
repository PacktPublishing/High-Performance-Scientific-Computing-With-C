#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Return an estimated value of pi using n random Monte-Carlo draws
int estimate_pi(long n) 
{
    float r,x,y;
    int pi = 0;
    for(int i=0;i<n;i++)
    {
        x = (float) rand() / RAND_MAX;
        y = (float) rand() / RAND_MAX;
        r = sqrt(x*x+y*y);
        // If r < 1, the draw is within the circle's quadrant
        if (r < 1)
            pi += 1;
    }
    return pi;
}

int main(int argc, char * argv[])
{
    int rank, size;
    clock_t t;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0)
    {
        t = clock();
    }

    srand(rank+(time(NULL) << 20));
    if (argc < 2)
    {
        printf("Please input number of sample points\n");
        exit(-1);
    }
    float n;
    sscanf(argv[1], "%e", &n);

    n = n - ((int) n % size); //Make sure we are running with equal work per node
    int global_pi;
    int local_pi = estimate_pi((long) n/size);
    MPI_Reduce(&local_pi, &global_pi, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0)
    {
        printf("Pi estimate: %7.6f\n", (float) 4.*global_pi/n);
        printf("Runtime: %7.6f sec\n", (float) (clock()-t)/CLOCKS_PER_SEC);
    }

    MPI_Finalize();
    return 0;
}
