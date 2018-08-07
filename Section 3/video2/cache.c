#include "stdlib.h"
#include "time.h"
#define MAX 1e7
int main() {
    srand(time(NULL));
    int i,j;
    float *x = malloc(MAX*sizeof(float));
    for(j=0;j<MAX;j++) {
        i = (int) (MAX*(float) rand() / RAND_MAX);
        x[j] = j*j;
    }
    return 0;
}
