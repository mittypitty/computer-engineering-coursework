#include <iostream> 
using namespace std; 
 
int binarysearch(int value, int array[], int size) 
{ 
    int first = 0, last = size - 1, i; 
 
    while(first <= last) 
    { 
        i = (first + last) / 2; 
 
        if(array[i] == value) 
        return i; 
 
        if(array[i] < value) 
        first = i + 1; 
         
        else 
        last = i - 1; 
    } 
 
    return -1; 
} 
 
void bubble(int array[], int size) 
{ 
  int i, j, temp; 
 
  for(i = 0 ; i < size - 1 ; i = i + 1) 
  { 
    for(j = 0 ; j < size - 1 - i ; j = j + 1) 
    {   
      if(array[j] > array[j+1]) 
      { 
         temp = array[j]; 
         array[j] = array[j+1]; 
         array[j+1] = temp; 
      }  
    } 
  }  
 
} 
 
int main() 
{ 
    int n =50; 
    //cin >> n;
      
    int list[n]; 
 
     
 
    for(int i = 0  ; i < n ; i = i + 1) 
    { 
        cin >> list[i]; 
    } 
     
    int number; 
     cin >> number; 
 
    bubble(list , n); 
    cout << binarysearch(number, list, n); 
 
    return 0; 
}
