#include <iostream>
using namespace std;

int z;

struct complex 
{
    int re;
    int img;
}number1 , number2, number3;

int add(int x, int y)
{
    z = x + y;
    return z;
}
int mines(int x, int y)
{
    z = x - y;
    return z;
}

int main()
{
  int real1, real2;
  char sign1, sign2, sign3;
  char i;
  char x1, x2;
  int img1, img2;

  cin >> real1 >> sign1 >> i >> x1 >> img1;
  cin >> real2 >> sign2 >> i >> x2 >> img2;
  cin >> sign3;
  number1.re = real1;
  number2.re = real2;

  number1.img = img1;
  number2.img = img2;

  if(sign3 == '+')
  {
     number3.re = add(number1.re, number2.re);
    
    if(sign1 == '-')
    number1.img = number1.img * (-1);
    
    if(sign2 == '-')
    number2.img = number2.img * (-1);
    
    number3.img = add(number1.img, number2.img);

    // conditions

    if(number3.re == 0 && number3.img == 0) 
    cout << 0; 

    else if(number3.img == 0) 
    cout << number3.re; 
    
    else if(number3.re == 0 && number3.img > 0) 
    cout << number3.img << i; 
    
    else if(number3.re == 0 && number3.img < 0) 
    cout << "-" << (-1) * number3.img << i; 
    
    else if(number3.img > 0) 
    cout << number3.re << "+" << number3.img << i; 
    
    else if(number3.img < 0) 
    cout << number3.re << "-" << (-1) * number3.img << i;

  }

  if(sign3 == '-')
  {
    number3.re = mines(number1.re, number2.re);

    if(sign1 == '-')
    number1.img = number1.img * (-1);
    
    if(sign2 == '-')
    number2.img = number2.img * (-1);

    number3.img = mines(number1.img, number2.img);

     // conditions
    
    if(number3.re == 0 && number3.img == 0) 
    cout << 0; 

    else if(number3.img == 0) 
    cout << number3.re; 
    
    else if(number3.re == 0 && number3.img > 0) 
    cout << number3.img << i; 
    
    else if(number3.re == 0 && number3.img < 0) 
    cout << "-" << (-1) * number3.img << i; 
    
    else if(number3.img > 0) 
    cout << number3.re << "+" << number3.img << i; 
    
    else if(number3.img < 0) 
    cout << number3.re << "-" << (-1) * number3.img << i;

  }
  
  if(sign3 == '*')
  {
     if(sign1 == '-')
    number1.img = number1.img * (-1);
    
    if(sign2 == '-')
    number2.img = number2.img * (-1);

    number3.re = (number1.re * number2.re) - (number1.img * number2.img);
    number3.img = (number1.re * number2.img) + (number2.re * number1.img);
    
     // conditions
    
    if(number3.re == 0 && number3.img == 0) 
    cout << 0; 

    else if(number3.img == 0) 
    cout << number3.re; 
    
    else if(number3.re == 0 && number3.img > 0) 
    cout << number3.img << i; 
    
    else if(number3.re == 0 && number3.img < 0) 
    cout << "-" << (-1) * number3.img << i; 
    
    else if(number3.img > 0) 
    cout << number3.re << "+" << number3.img << i; 
    
    else if(number3.img < 0) 
    cout << number3.re << "-" << (-1) * number3.img << i;
    
  }
  
  return 0; 
} 