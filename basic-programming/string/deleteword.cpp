#include <iostream>
#include <cstring> 
using namespace std;

int number, sentenceLength, wordLength, found;

int calculateLength(char* str)  
{ 
    const char* newStr = str; 
    int length = 0; 

    while (*newStr != '\0')  
    {   
        length++; 
        newStr++; 
    } 

    return length; 
}

void deleteWord(char* sentence, char* nonsense)  
{ 
    wordLength = calculateLength(nonsense); 
    sentenceLength = calculateLength(sentence); 
    int a = wordLength;
    int tafazol = sentenceLength - wordLength;
    found = 1; 
     
    for (int i = 0; i <= tafazol; i++)  
    { 
        found = 1;  
        for (int j = 0; j < a; j++)  
        { 
            if (sentence[i + j] != nonsense[j])  
            { 
                found = 0; 
                break; 
            } 
        } 
        if (found == 1)  
        { 
            
            for (int s = i; s <= tafazol; s++)  
            { 
                sentence[s] = sentence[s + a +1];
            }
            sentenceLength = tafazol;
            i--; 
        }
    } 
    sentence[sentenceLength] = '\0'; 
} 

int main() 
{ 
    char* sentence; 
    sentence = new char[1000]; 
 
    cin.getline(sentence, 1000); 
    cin >> number; 
 
    for (int i = 1; i <= number; i++) 
    { 
        char* nonsense; 
        nonsense = new char[1000]; 
        cin >> nonsense; 
     
        deleteWord(sentence, nonsense); 
    } 
 
    cout << sentence << endl; 
    delete[] sentence;  
    return 0; 
}

