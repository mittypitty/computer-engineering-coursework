#include <iostream>  
#include <cstring>
using namespace std;  
  
int main()  
{  
    //const int max = 2000;  
    char entryline[2000];  
    int passcode, tool;  
    char javab[2000];  

    cin.getline(entryline, 2000);  
    tool = 0;  
  
    for (int i = 0; entryline[tool] != '\0'; i++)   
    {  
        tool = tool + 1;  
    }  
  
    for (int i = 0 ; i < tool ; i++)   
    {  
        if ((entryline[i] < 'a' || entryline[i] > 'z') && (entryline[i] < 'A' || entryline[i] > 'Z') && (entryline[i] != ' '))
        {  
            cout << "ERROR!" << endl;  
            return 0;  
        }  
    }  

    
  
  
    passcode = entryline[3] - 'A';  
    passcode = (-1)*passcode;  
  
    for(int j = 0 ; entryline[j] != '\0' ; j++)  
    {  
        if(entryline[j] == ' ') 
        javab[j] = ' ';  
  
        else if(entryline[j] >= 'A' && entryline[j] <= 'Z')  
        {  
           if((entryline[j] + passcode) > 'Z' )  
           {  
                javab[j] = 'A' + ((entryline[j] + passcode) - 'Z' - 1);  
           }  
           else if((entryline[j] + passcode) < 'A')  
           {  
                javab[j] = 'Z'+ 1 - ('A' - (entryline[j]+passcode));  
           }  
           else 
           javab[j] = entryline[j] + passcode;  
        }  
  
        else if(entryline[j] >= 'a' && entryline[j] <= 'z')  
        {  
            if((entryline[j] + passcode) > 'z' )  
            {  
                javab[j] = 'a' + ((entryline[j] + passcode) - 'z' - 1);  
            }  
            else if((entryline[j] + passcode) < 'a')  
            {  
                javab[j] = 'z' + 1 - ('a' - (entryline[j] + passcode));  
            }  
           else 
           javab[j] = entryline[j] + passcode;  
        }  
    }  
    
    int javabLEN = strlen(entryline);
    for(int j = 0 ; j < javabLEN ; j++)  
    {  
    cout << javab[j];  
    }  
    cout << endl;
  
     
    return 0;  
}
