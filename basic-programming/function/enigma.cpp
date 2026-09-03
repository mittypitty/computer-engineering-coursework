#include <iostream> 
using namespace std; 
 
long int AsciiCode (char c) 
{ 
     long int x = c; 
     return x; 
} 
 
int main() 
{ 
    char h1, h2, h3, h4, h5; 
    cin >> h1 >> h2 >> h3 >> h4 >> h5 ; 
 
    long int x1, x2, x3, x4, x5; 
    x1 = AsciiCode(h1); 
    x2 = AsciiCode(h2); 
    x3 = AsciiCode(h3); 
    x4 = AsciiCode(h4); 
    x5 = AsciiCode(h5); 
    char n1,n2,n3,n4,n5; 
    cin >> n1 >> n2 >> n3 >> n4 >> n5; 
 
    long long int y1, y2, y3, y4, y5; 
    y1 = AsciiCode(n1); 
    y2 = AsciiCode(n2); 
    y3 = AsciiCode(n3); 
    y4 = AsciiCode(n4); 
    y5 = AsciiCode(n5); 
 
 
    // rabete // 
    long long int r1, r2, r3, r4, r5; 
    r1 = y1 - x1; 
    r2 = y2 - x2; 
    r3 = y3 - x3; 
    r4 = y4 - x4; 
    r5 = y5 - x5; 
 
 
    long long int number, number2; 
    cin >> number; 
    number2 = number / 5; 
     
    for(int i = 1 ; i <= number2 ; i = i + 1) 
    { 
      long long int j1, j2, j3, j4, j5; 
      char f1, f2, f3, f4, f5; 
      cin >> f1 >> f2 >> f3 >> f4 >> f5 ; 
    
    j1 = AsciiCode(f1); 
    j2 = AsciiCode(f2); 
    j3 = AsciiCode(f3); 
    j4 = AsciiCode(f4); 
    j5 = AsciiCode(f5); 
     
    long long int p1, p2, p3, p4, p5; 
    p1 = j1 - r1; 
    p2 = j2 - r2; 
    p3 = j3 - r3; 
    p4 = j4 - r4; 
    p5 = j5 - r5; 
 
    char s1 = p1 ; 
    char s2 = p2 ;  
    char s3 = p3 ; 
    char s4 = p4 ; 
    char s5 = p5 ; 
    
       cout << s1 << s2 << s3 << s4 << s5; 
    } 
 
    return 0; 
}