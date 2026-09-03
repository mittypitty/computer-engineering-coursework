#include <iostream> 
#include <cstring> 
using namespace std; 
 
void swap(char*&s, char*&t) 
{ 
    char* temp = s; 
    s = t; 
    t = temp; 
} 
 
void bubblesort(char** string, int size) 
{ 
    for(int i = 0 ; i < size - 1 ; i++) 
    { 
        for(int j = 0 ; j < size - i - 1 ; j++) 
        { 
            if(strcmp(string[j + 1], string[j]) < 0) 
            swap(string[j], string[j + 1]); 
        } 
    } 
} 
 
int main() 
{ 
    const int name = 20; 
    const int harf = 15; 
    char** daftar = new char *[name]; 
    int number; 
 
    number = 0; 
    for(int i = 0 ; i < name ; i++) 
    { 
        daftar[i] = new char[name]; 
        cin >> daftar[i]; 
 
        if(daftar[i][0] == '0') 
        break; 
 
        number = number + 1; 
    } 
 
    bubblesort(daftar, number); 
 
    for (int i = 0 ; i < number - 1 ; i++) 
    { 
        for (int j = 0 ; j < number - i - 1 ; j++) 
        { 
            if (daftar[j + 1][0] >= 'a' && daftar[j + 1][0] <= 'z') 
            { 
                if (daftar[j][0] >= 'A' && daftar[j][0] <= 'Z') 
                { 
                    // A - a = 32 
                    if (daftar[j + 1][0] - daftar[j][0] < 32) 
                    swap(daftar[j], daftar[j + 1]); 
                } 
            } 
        } 
    } 
 
    for(int i = 0 ; i < number ; i++) 
    { 
        cout << daftar[i] << endl; 
    } 
 
    return 0; 
}
