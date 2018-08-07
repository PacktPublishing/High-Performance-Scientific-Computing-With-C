#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <curand_kernel.h>


// Calculate an estimated value of pi using n random Monte-Carlo draws
__global__ void estimate_pi(int seed, int per_thread, curandState *state, unsigned int *result) 
{
    int id = threadIdx.x + blockIdx.x * blockDim.x;
    curand_init((seed << 20) + id, 0, 0, &state[id]);
    float r,x,y;
    int i;
    for(i=0;i<per_thread;i++)
    {
        x = curand_uniform(&state[id]);
        y = curand_uniform(&state[id]);
        r = sqrtf(x*x+y*y);
        result[id] += (r < 1) ? 1 : 0;
    }
}

// Sum all the results together.
void serial_reduce(int n, unsigned int *in, unsigned long *out)
{
    int i;
    *out = 0;
    for(i=0;i<n;i++)
    {
        *out += in[i];
    }
}


int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        printf("Please input number of sample points \n");
        exit(-1);
    }
    float n;
    int threads=512; 
    int blocks=2048;
    sscanf(argv[1], "%e", &n);
    n=n-(n%threads*blocks); //get a nice number of points to run on our GPU
    if (n < threads*blocks) n=threads*blocks; // run at least enough points to use the GPU
    int per_thread = n/(threads*blocks);
    unsigned int *pi; 
    printf("%d %d %d\n", blocks, threads, per_thread);
    cudaMallocManaged(&pi, threads*blocks*sizeof(int));
    
    curandState_t* state;
    cudaMalloc(&state, threads*blocks*sizeof(curandState_t));
    estimate_pi<<<blocks, threads>>>(time(NULL), per_thread, state, pi);

    unsigned long *sum_pi; 
    cudaMallocManaged(&sum_pi, sizeof(long));

    cudaDeviceSynchronize();
    serial_reduce(threads*blocks, pi, sum_pi);
    printf("Pi estimate: %7.6f\n", (float) 4.*(*sum_pi)/n);
    cudaFree(state);
    return 0;
}
