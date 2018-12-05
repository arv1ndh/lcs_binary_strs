#include <math.h>
#include <assert.h>
#include <string.h>
#include <iostream>
using namespace std;
#include <vector>
#include <set>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define ARRAYSIZE 21

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


void setDpMtx(int dpMtx[ARRAYSIZE][ARRAYSIZE], const int n, char* xBinary, char* yBinary){
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
        int mem_mtx[ARRAYSIZE][ARRAYSIZE];
        set<vector<char> > lcsSet;
        dfs();
        void setDfs(int x, int y, vector<char> lcsPath,
            const int dpMtx[ARRAYSIZE][ARRAYSIZE],
            const char* xBinary, const char* yBinary);
        void addLcsSet(vector<char> lcsPath);
};

dfs::dfs(){
    for(int i=0;i<ARRAYSIZE;i++)
        for(int j=0;j<ARRAYSIZE;j++)
            mem_mtx[i][j] = 0;
}

void dfs::addLcsSet(vector<char> lcsPath){
    if (lcsPath.size() > 0)
        lcsSet.insert(lcsPath);
}

void dfs::setDfs(int x, int y, vector<char> lcsPath, const int dpMtx[ARRAYSIZE][ARRAYSIZE],
        const char* xBinary, const char* yBinary)
{ 
    if (dfs::mem_mtx[x][y] == 1)
        return;
    if (dfs::mem_mtx[x][y] == 0)
        mem_mtx[x][y] = 1;
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
    cout<<"Enter value of n in range [3:20] : ";
    cin>>n;
    assert(n >= 3 && n <= 20);

    cout<<"Enter value of x in range [0:1048575] : ";
    cin>>x;
    assert(x >= 0 && x <= (pow(2, n)-1));

    cout<<"Enter value of y in range [0:1048575] : ";
    cin>>y;
    assert(y >= 0 && y <= (pow(2,n)-1));

    // Convert to binary //
    char xBinary[ARRAYSIZE];
    char yBinary[ARRAYSIZE];
    binstring(xBinary, n, x);
    binstring(yBinary, n, y); 

    // LCS //
    int dpMtx[ARRAYSIZE][ARRAYSIZE];
    int lcsLen;
    std::set<std::vector<char> > lcsSet;
    setDpMtx(dpMtx, n, xBinary, yBinary);
    lcsLen = dpMtx[n][n];

    // print table //
     for(int j = 0; j <= n; j++){
         for(int i = 0; i <= n; i++){
             printf("%d\t", dpMtx[i][j]);
         }
         printf("\n");
     }
    
    vector<char> lcsPath(lcsLen);

    dfs _dfs; 
    _dfs.setDfs(n, n, lcsPath, dpMtx, xBinary, yBinary);
    
    cout<<"STRINGLEN "<<n<<endl;
    cout<<"X: "<<x<<" Binary String: "<<xBinary<<endl;
    cout<<"Y: "<<y<<" Binary String: "<<yBinary<<endl;
    cout<<"LCS Length "<<lcsLen<<endl<<"No of Distinct LCS: "<<_dfs.lcsSet.size()<<endl;

    int lcsCnt = 1;
    for(set<vector<char> >::iterator s_it=_dfs.lcsSet.begin(); s_it!=_dfs.lcsSet.end(); ++s_it){
        cout<<"lcs "<<lcsCnt<<": ";
        for(vector<char>::const_iterator v_it = s_it->begin() ; v_it != s_it->end(); ++v_it)
            cout<<*v_it;
        cout<<endl;
        lcsCnt++;
    }

    return 0;
}
