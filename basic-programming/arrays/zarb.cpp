#include <iostream>  
using namespace std ; 
 
int main() 
{ 
    int m, n; 
    int s, r; 
    
    cin >> m >> n; 
    cin >> s >> r; 
 
    int firstmatris[25][25]; 
    int secondmatris[25][25]; 
    int lastmatris[25][25]; 
 
    int i, j, k; 
     
 
    for(i = 0 ; i < m ; i = i + 1) 
    { 
        for(j = 0 ; j < n ; j = j + 1) 
        { 
            cin >> firstmatris[i][j]; 
        } 
    } 
 
    for(i = 0 ; i < s ; i = i + 1) 
    { 
        for(j = 0 ; j < r ; j = j + 1) 
        { 
            cin >> secondmatris[i][j]; 
        } 
    } 
     
     
    for(i = 0 ; i < m ; i = i + 1) 
    { 
        for(j = 0 ; j < r ; j = j + 1) 
        { 
            lastmatris[i][j]=0; 
            for(k = 0 ; k < n ; k = k + 1) 
            { 
                lastmatris[i][j] +=  (firstmatris[i][k] * secondmatris[k][j]); 
            } 
 
        } 
    }   
        for(j = 0 ; j < r ; j = j + 1) 
        { 
            for(i = 0 ; i < m ; i = i + 1) 
            { 
                cout << lastmatris[i][j] <<' '; 
            } 
           cout << endl; 
        } 
     
 
    return 0; 
}
