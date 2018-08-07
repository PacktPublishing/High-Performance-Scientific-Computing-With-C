#include "stdlib.h"
#include "time.h"
#define MAX 2e7
int main() {
    srand(time(NULL));
    int i,j;
    float *x = malloc(MAX*sizeof(float));
    for(j=0;j<MAX;j++) {
        i = rand() % 3;
        i = j % 3;
        switch(i) {
            case 0:
                x[j] = j+1;
                break;
            case 1:
                x[j] = j+2;
                break;
            case 2:
                x[j] = j+3;
                break;
        }
    }
    return 0;
}
