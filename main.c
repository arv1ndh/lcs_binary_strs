#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

char* binstring(int t_bits, long int number) {
    char *b_string = malloc(t_bits+1);
    int i = 0;
    while(number) {
        b_string[t_bits-i-1] = (int)(number&1) + '0';
        number = number>>1;
        i++;
    }
    for(;i<t_bits;i++)
        b_string[t_bits-i-1] = '0';
    b_string[i] = '\0';
    printf("BIN STRING IS %s\n", b_string);
    return b_string;
}

void lcs_bin(char *b_x, char *b_y, int n)
{
    int opt[n+1][n+1];
    int i,j;
    for(i=0;i<n+1;i++)
        opt[i][0] = 0;
    for(j=0;j<n+1;j++)
        opt[0][j] = 0;
    for(i=1;i<n+1;i++)
        for(j=1;j<n+1;j++)
        {
            if (b_x[i] == b_y[j])
                opt[i][j] = opt[i-1][j-1] + 1;
            else
                opt[i][j] = (opt[i][j-1] > opt[i-1][j])?opt[i][j-1]:opt[i-1][j];
        }
    for(i=0;i<n+1;i++)
    {
        for(j=0;j<n+1;j++)
            printf("%d  ",opt[i][j]);
        printf("\n");
    }
    printf("The lcs is %d\n",opt[n][n]);
}

int main()
{
    int n;
    long int x;
    long int y;
    printf("Enter n value: ");
    scanf("%d", &n);
    assert(n >= 3 && n <= 20);
    printf("Enter x value: ");
    scanf("%ld", &x);
    assert(x >= 0 && x <= (pow(2, n)-1));
    printf("Enter y value: ");
    scanf("%ld", &y);
    assert(y >= 0 && y <= (pow(2,n)-1));
    //char bin_x[n+1], bin_y[n+1];
    char *bin_x, *bin_y;
    bin_x = binstring(n,x);
    bin_y = binstring(n,y);
    lcs_bin(bin_x, bin_y, n);
    free(bin_x);
    free(bin_y);
    return 0;
}
