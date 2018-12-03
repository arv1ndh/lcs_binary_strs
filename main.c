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

int** lcs_bin(char *b_x, char *b_y, int n)
{
    int i,j;
    int **opt = (int**)malloc((n+1)*sizeof(int*));
    for(i=0;i<n+1;i++)
        opt[i] = (int*)malloc((n+1)*sizeof(int));
    for(i=0;i<n+1;i++)
        opt[i][0] = 0;
    for(j=0;j<n+1;j++)
        opt[0][j] = 0;
    for(i=1;i<n+1;i++)
        for(j=1;j<n+1;j++)
        {
            if (b_x[i-1] == b_y[j-1])
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
    //printf("The lcs is %d\n",opt[n][n]);
    return opt;
}

char* lcs_strings(char *b_x, char *b_y, int** opt_array, int n)
{
    int i,j;
    i = j = n;
    int len = opt_array[n][n];
    int k = 0;
    char *final_st = (char*)malloc(len+1);
    while (i > 0 && j > 0)
    {
        if (b_x[i-1] == b_y[j-1])
        {
            final_st[len-k-1] = b_x[i-1];
            //printf("Chars--%c", final_st[len-k-1]);
            k++;
            i--;
            j--;
            continue;
        }
        if (opt_array[i][j-1] >= opt_array[i-1][j])
            j--;
        else
            i--;
    }
    final_st[len] = '\0';
    return final_st;
}

int main()
{
    int n,i;
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
    char *bin_x, *bin_y;
    int **opt;
    bin_x = binstring(n,x);
    bin_y = binstring(n,y);
    opt = lcs_bin(bin_x, bin_y, n);
    printf("VALUE IS --> %s\n",lcs_strings(bin_x, bin_y, opt, n));
    for(i=0;i<n+1;i++)
        free(opt[i]);
    free(opt);
    free(bin_x);
    free(bin_y);
    return 0;
}
