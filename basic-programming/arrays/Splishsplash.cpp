#include <iostream>
using namespace std;

int main()
{
char R;
char shatranj[8][8];
int countrokh = 0;
int i, j, k;

for (i = 0; i < 8; i = i + 1)
{
  for (j = 0; j < 8; j = j + 1) 
   {
     cin >> shatranj[i][j];

     if (shatranj[i][j] == 'R')
        countrokh = countrokh + 1;
   }
}

if (countrokh != 8) 
  cout << "INVALID";
int R_i=1 , R_j=1;
for (i = 0; i < 8; i = i + 1) 
{
  for (j = 0; j < 8; j = j + 1) 
  {
    if (shatranj[i][j] == 'R' && i>0) 
        R_i*=i;
    if (shatranj[i][j] == 'R' && j>0) 
        R_j*=j;
  }
}
// cout << R_i << R_j;
if(R_i==5040 && R_j==5040)
    cout <<"VALID";
else
    cout <<"INVALID";
    return 0;
}