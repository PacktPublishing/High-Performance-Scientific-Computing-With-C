#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3

#define SWAP(x,y,T) do {T swap = x; x = y; y = swap;} while (0)

void gauss_jordan(int n, float a[][n])
{
    int i,j,k,irow,icol,l,ll;
    int ipiv[n], indxr[n], indxc[n];
    float big,dum,pinv;
    memset(ipiv, 0, sizeof(int)*n); // zero out pivot vector
    for(i=0; i<n; i++) // loop over rows
    {
        big = 0.;
        for(j=0; j<n; j++) // loop over columns
            if(ipiv[j] != 1)
                for(k=0;k<n;k++) // check to see if we swap
                    if((ipiv[k] == 0) && (abs(a[j][k]) >= big))
                    {
                        big = abs(a[j][k]);
                        irow=j;
                        icol=k;
                    }
        ++(ipiv[icol]);
        if(irow != icol) 
            for(l=0;l<n;l++)
                SWAP(a[irow][l],a[icol][l],float);
        indxr[i] = irow;
        indxc[i] = icol;
        if(a[icol][icol] == 0) // Check for singularity
        {
            printf("Singular Matrix!  Cannot invert!\n");
            return;
        }
        pinv =1./a[icol][icol];
        a[icol][icol] = 1.; // identity matrix
        for(l=0;l<n;l++)
            a[icol][l] *= pinv;
        for(ll=0;ll<n;ll++)
            if(ll != icol)
            {
                dum=a[ll][icol];
                a[ll][icol]=0.;
                for(l=0;l<n;l++)
                    a[ll][l] -= a[icol][l]*dum;
            }
    }
    for(l=n-1;l>=0;l--)
        if(indxr[l] != indxc[l])
            for(k=0;k<n;k++)
                SWAP(a[k][indxr[l]],a[k][indxc[l]],float);
}

int main(int argc, char * argv[])
{
    /*srand(time(NULL));*/
    float mat[N][N]; 
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            mat[i][j] = (float) rand() / RAND_MAX;
    printf("Original Matrix:\n");
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            printf("%3.2f ", mat[i][j]);
        printf("\n");
    }
    gauss_jordan(N, mat);
    printf("Inverse Matrix:\n");
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            printf("%3.2f ", mat[i][j]);
        printf("\n");
    }
}
