#include <iostream>
using namespace std;

int n, i, j;
void fun(int** prt)
{
    for(i = 0 ; i < n ; i = i + 1)
    {
        for(j = 0 ; j < n - 1 ; j = j + 1)
        {
            if(prt[i][j] != prt[i][j + 1])
            {
                cout << "NO";
                return;
            }
        }
    }
    for(j = 0 , i = 0 ; i < n - 1 ; i = i + 1)
    {
        if(prt[i][j] != prt[i + 1][j])
            {
                cout << "NO";
                return;
            }
    }

    cout << "YES";
}

int main()
{


    cin >> n ;
    
    int** firstmatrix;
    firstmatrix = new int*[n];

    for(i = 0 ; i < n ; i = i + 1)
    {
    firstmatrix[i] = new int[n];
        for(j = 0 ; j < n ; j = j + 1)
        {
            cin >> firstmatrix[i][j];
        }
    }
    for(i = 0 ; i < n ; i = i + 1)
    {
        for(j = 0 ; j < n ; j = j + 1)
        {
            cout << firstmatrix[n - 1 - j][i] << " ";
        }
        cout << endl;
    }
    cout << "----------" << endl;
    int** secondmatrix;
    secondmatrix = new int*[n];

    for(i = 0 ; i < n ; i = i + 1)
    {
    secondmatrix[i] = new int[n];
        for(j = 0 ; j < n ; j = j + 1)
        {
            secondmatrix[i][j] = firstmatrix[n - 1 - j][i] + firstmatrix[i][j];
            cout << secondmatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------" << endl;

    fun(secondmatrix);
}