#include <iostream>
using namespace std;

int main()
{
    int k, i, j, x, z;
    cin >> k;

    int** sizeoftables;
    sizeoftables = new int*[k];

    for(i = 0 ; i < k ; i++)
    {
        sizeoftables[i] = new int[2];
        // sotoon ha 2 ta mishe , sotoon aval mishe andis satr and sotoon dovom mishe andis sotoon
    }
    
    int*** tables;
    tables = new int** [k];
    
    for(i = 0 ; i < k ; i++)
    {
        cin >> sizeoftables[i][0] >> sizeoftables[i][1];
        tables[i] = new int* [sizeoftables[i][0]];

        for(j = 0 ; j < sizeoftables[i][0] ; j++)
        {
            tables[i][j] = new int [sizeoftables[i][1]];
            for(z = 0 ; z < sizeoftables[i][1] ; z++)
            { 
                cin >> tables[i][j][z];
            }
        }
    }
     
    cin >> x;

    int* scoretable;
    scoretable = new int[k];

    for(i = 0 ; i < k ; i++)
    {
        scoretable[i] = 0;

        for(j = 0 ; j < sizeoftables[i][0] ; j++)
        {
            for(z = 0 ; z < sizeoftables[i][1] ; z++)
            {
                if(tables[i][j][z] == x)
                {
                   scoretable[i] = (scoretable[i] +(j + 1));
                }
            }
        }
    }        
    
    // now i should save the andis of tables based on their quantity

    int* andisoftable;
    andisoftable = new int[k];

    for(z = 0 ; z < k ; z++)
    {
        andisoftable[z] = z + 1;
    }
    for(i = 0 ; i < (k - 1) ; i++)
    {
        for(j = 0 ; j< (k - i - 1) ; j++)
        {
            if(scoretable[j] > scoretable[j + 1])
            {
                swap(scoretable[j], scoretable[j + 1]);
                swap(andisoftable[j], andisoftable[j + 1]);
            }
        }
    }
    

    for(i = 0 ; i < k ; i++)
    {
       cout << andisoftable[i] <<" ";
    }

    return 0;
}