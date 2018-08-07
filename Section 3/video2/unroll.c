#include "stdlib.h"
#include "time.h"
#define MAX 5e7
int main() {
    srand(0);
    int i,j;
    float *x = malloc(MAX*sizeof(float));
    for(j=0;j<MAX;j++) {
        for(i=0;i<4;i++) {
            x[j] += rand();
        }
    }
    return 0;
}
