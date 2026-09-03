#include <iostream> 
using namespace std;

int main()
{

int n;
cin >> n;

int matris[n][n];

int i, j;

for(i = 0 ; i < n ; i = i + 1)
{
    for(j = 0 ; j < n ; j = j + 1)
    {
        cin >> matris[i][j];
    }
}

for(i = 0 ; i < n ; i = i + 1)
{
    for(j = 0 ; j < n ; j = j + 1)
    {
        cout << matris[n - 1 - j][i] << " ";
    }
        cout << endl;
}

return 0;
}