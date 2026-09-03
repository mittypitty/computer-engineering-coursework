#include <iostream> 
using namespace std; 
 
int main() 
{ 
long long int i; 

int j, m, n; 
int sum  = 0; 
 
 
cin >> n; 
long long int Sina[n]; 
for(i = 0 ; i < n ; i = i + 1) 
{ 
    cin >> Sina[i] ; 
} 
 
 
for(i = 0 ; i < n ; i = i + 1) 
{ 
    j = i + 1; 
 
 for(m = 1 ; m < (n - i) ; m = m + 1) 
 { 
 
 if( Sina[i] > Sina[j] ) 
 
 { 
    sum = sum + 1; 
 } 
 
     j = j + 1; 
 } 
 
} 
 cout << sum << endl; 
return 0; 
}
