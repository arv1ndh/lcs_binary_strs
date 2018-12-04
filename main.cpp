#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <vector>
#include <set>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define binArrSize 20

void binstring(char* bString, int n, int val){
    long int rmd = val;
    for(int i = n - 1; i >= 0; i--){
        if (rmd >= pow(2, i)) {
            bString[n - i - 1] = '1';
            rmd = rmd - pow(2, i);
        }
        else
            bString[n - i - 1] = '0';
    }
    bString[n] = '\0'; /// to end the string array
}


void setDpMtx(int dpMtx[binArrSize + 1][binArrSize + 1], const int n, char* xBinary, char* yBinary){
    for(int i = 0; i <= n; i++){
        dpMtx[i][0] = 0;
        dpMtx[0][i] = 0;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){            
            if(xBinary[i-1] == yBinary[j-1])
                dpMtx[i][j] = dpMtx[i-1][j-1] + 1;
            else
                dpMtx[i][j] = max(dpMtx[i-1][j], dpMtx[i][j-1]);
        }
    }
}

class dfs{
    public:
        int lcsLen;
        std::set<std::vector<char>> lcsSet;
        dfs();
        void setDfs(int x, int y, std::vector<char> lcsPath,
            const int dpMtx[binArrSize + 1][binArrSize + 1],
            const char* xBinary, const char* yBinary);
        void addLcsSet(std::vector<char> lcsPath);
};

dfs::dfs(){}

void dfs::addLcsSet(std::vector<char> lcsPath){
    lcsSet.insert(lcsPath);
}

void dfs::setDfs(int x, int y, std::vector<char> lcsPath, const int dpMtx[binArrSize + 1][binArrSize + 1],
        const char* xBinary, const char* yBinary)
{ //, std::vector<std::string> lcsTraceback 
    if(dpMtx[x][y] == 0){
        addLcsSet(lcsPath);
    }
    else if((dpMtx[x-1][y-1] == dpMtx[x][y] - 1) && (xBinary[x-1] == yBinary[y-1])){
        lcsPath[dpMtx[x][y] - 1] = xBinary[x - 1];
        setDfs(x-1, y-1, lcsPath, dpMtx, xBinary, yBinary);
    }
    else{
        if(dpMtx[x-1][y] == dpMtx[x][y]){
            setDfs(x-1, y, lcsPath, dpMtx, xBinary, yBinary);
        }
        if(dpMtx[x][y-1] == dpMtx[x][y]){
            setDfs(x, y - 1, lcsPath, dpMtx, xBinary, yBinary);
        }
    }
}

int main()
{
    int n;
    long int x;
    long int y;
    printf("Enter value of n in range [3:20] : ");
    scanf("%d", &n);
    assert(n >= 3 && n <= 20);

    printf("Enter value of x in range [0:16383] : ");
    scanf("%ld", &x);
    assert(x >= 0 && x <= (pow(2, n)-1));

    printf("Enter value of y in range [0:16383] : ");
    scanf("%ld", &y);
    assert(y >= 0 && y <= (pow(2,n)-1));

    // Convert to binary //
    char xBinary[binArrSize + 1];
    char yBinary[binArrSize + 1];
    binstring(xBinary, n, x);
    binstring(yBinary, n, y); // have to pass a pointer array in, cannot create an array within the function and return it, because the pointer got destroyed when exit the function
    // printf("binary string x is %s \n", xBinary);
    // printf("binary string y is %s \n", yBinary);


    // LCS //
    int dpMtx[binArrSize + 1][binArrSize + 1];
    int lcsLen;
    std::set<std::vector<char>> lcsSet;
    setDpMtx(dpMtx, n, xBinary, yBinary);
    lcsLen = dpMtx[n][n];

    // print table //
    // for(int j = 0; j <= n; j++){
    //     for(int i = 0; i <= n; i++){
    //         printf("%d\t", dpMtx[i][j]);
    //     }
    //     printf("\n");
    // }
    
    std::vector<char> lcsPath(lcsLen);

    dfs _dfs; 
    _dfs.setDfs(n, n, lcsPath, dpMtx, xBinary, yBinary);
    
    printf("** STRINGLEN %d: %d length-%d LCS's from X=(%d)=%s and Y=(%d)=%s\n",
            n, _dfs.lcsSet.size(), lcsLen, x, xBinary, y, yBinary);
    

    int lcsCnt = 1;
    for(std::set<std::vector<char>>::iterator s_it=_dfs.lcsSet.begin(); s_it!=_dfs.lcsSet.end(); ++s_it){
        printf("lcs  %d: ", lcsCnt);
        for(std::vector<char>::const_iterator v_it = s_it->begin() ; v_it != s_it->end(); ++v_it)
            printf("%c ", *v_it);
        printf("\n");
        lcsCnt++;
    }

    return 0;
}
