#include <time.h>
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#define N (2 << 18)


//Store the FFT of f in F, for n points
void fft(float complex *F, float complex *f, int n, int stride)
{
    if(n == 1) 
    {
        F[0] = f[0];
    }
    else
    {
        // Split the array and recursively process every 2*stride elements
        fft(F, f, n/2, 2*stride);
        fft(F+n/2, f+stride, n/2, 2*stride);
        float complex t;
        #pragma omp for private(t)
        for(int i=0;i<n/2;i++)
        {
            t = F[i];
            F[i] = t + cexp(2.*M_PI*I*i/n)*F[i+n/2];
            F[i+n/2] = t - cexp(2.*M_PI*I*i/n)*F[i+n/2];
        }
    }
}

// Generate a delta function inital value
void delta(float complex *input)
{
    for(int i=0;i<N;i++)
    {
        input[i] = 0.;
    }
    input[0] = 1.;
}

// Generate a sine function inital value
void sine(float complex *input)
{
    for(int i=0;i<N;i++)
    {
        input[i] = csin(8.*(( float)i)*M_PI/N);
    }
}

// Generate a sinc function initial value
void sinc(float complex *input)
{
    for(int i=0;i<N;i++)
    {
        input[i] = csin(10.*(( float)i)*M_PI/N)/(10.*(( float)i)*M_PI/N);
    }
    input[0] = 1;
}

int main(int argc, char * argv[])
{
    float complex *x = malloc(N*sizeof(float complex));
    float complex *ft_x = malloc(N*sizeof(float complex));
    sinc(x);
    #pragma omp parallel num_threads(2)
    fft(ft_x, x, N, 1);
}
