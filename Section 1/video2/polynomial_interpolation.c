#include "math.h"
#include "stdio.h"
#include "stdlib.h"

// The number of points in the original dataset
#define BASE_RES 10

// The order of the polynomial we are interpolating to
#define ORDER 2


// This struct will contain the output of the interpolation process
typedef struct result
{
    float *xs;
    float *ys;
} result;

float interp(float *xs, float *ys, float x, int order)
{
    float y=0,tmp;
    for(int i=0;i<order;i++)
    {
        tmp=ys[i];
        for(int j=0;j<order;j++)
        {
            if(i==j) continue;
            tmp *= (x-xs[j])/(xs[i]-xs[j]);
        }
        y+=tmp;
    }
    return y;
}

result interpolate(float *xs, float *ys, int n, int order)
{
    float delta;
    result res;
    res.xs = malloc(10*(n-1)*sizeof(float));
    res.ys = malloc(10*(n-1)*sizeof(float));
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<10;j++)
        {
            delta = xs[i+1]-xs[i];
            res.xs[10*i+j] = xs[i]+0.1*((float) j)*delta;
            if(i < n-order) { 
                res.ys[10*i+j] = interp(xs+i, ys+i, res.xs[10*i+j], order);
            }
            else {
                res.ys[10*i+j] = interp(xs+n-order, ys+n-order, res.xs[10*i+j], order);
            }
        }
    }
    return res;
}

int main()
{
    // generate our input data (a simple sine curve)
    float xs[BASE_RES];
    float ys[BASE_RES];
    for(int i=0;i<BASE_RES;i++)
    {
        xs[i] = 4.*M_PI*((float) i)/BASE_RES;
        ys[i] = sin(xs[i]);
    }
    result res = interpolate(xs, ys, BASE_RES, ORDER+1);
    // interpolate to 10x higher resolution
    for(int i=0;i<10*(BASE_RES-1);i++)
    {
        printf("%e %e\n", res.xs[i], res.ys[i]);
    }
    return 0;
}
