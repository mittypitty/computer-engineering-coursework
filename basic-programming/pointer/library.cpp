#include <iostream>
using namespace std;

void bubblesort(int** prt, int rows, int cols) 
{
    for (int z = 0 ; z < rows ; z++) 
    {
        for (int i = 0 ; i < cols - 1 ; i++) 
        {
            for (int j = 0 ; j < cols - i - 1 ; j++) 
            {
                if (prt[z][j] > prt[z][j + 1]) 
                {
                    swap(prt[z][j], prt[z][j + 1]);
                }
            }
        }
    }
}

int main() 
{
    int k, m, n, pickedlibrary;
    cin >> k >> m >> n;

    int** library = new int*[k * m];

    for (int i = 0; i < k * m; i++) 
    {
        library[i] = new int[n];
        for (int j = 0; j < n; j++) 
        {
            cin >> library[i][j];
        }
    }

    cin >> pickedlibrary;

    bubblesort(library, k * m, n);

    for (int i = ((pickedlibrary - 1) * m); i < (pickedlibrary * m); i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cout << library[i][j] << " ";
        }
        cout << endl;
    }

    // Deallocate memory
    for (int i = 0; i < k * m; i++) 
    {
        delete[] library[i];
    }
    
    delete[] library;

    return 0;
}