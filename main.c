#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

void binstring(int t_bits, long int number) {
    char b_string[t_bits+1];
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
    binstring(n,x);
    return 0;
}
