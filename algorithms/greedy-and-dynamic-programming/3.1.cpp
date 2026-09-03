#include <iostream>
using namespace std;

int main() {
    int n;
    int result = 0;
    cin >> n;

    int p[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    int i = 0;
    while (i < n) {
        int j = i;

        while ((j + 1 < n) && (p[j + 1] < p[j])) {
            j++;
        }

        int lenght = j - i + 1;
        result = result + (lenght / 2);
        i = j + 1;
    }

    cout << result;
    return 0;

}