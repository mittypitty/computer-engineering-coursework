#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    int arr_a[n];
    int arr_b[n];
    for (int i = 0; i < n; i++) {
        cin >> arr_a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> arr_b[i];
    }

    if (n == 1) {
        if (arr_a[0] >= arr_b[0]) {
            cout << "YES";
            return 0;
        }
        else {
            cout << "NO";
            return 0;
        }
    }
    bool bigger = true;
    bool possible = false;
    for (int i = 0; i < n; i++) {
        if (arr_a[i] < arr_b[i]) {
            bigger = false;
            // int a = arr_a[i];
            // int b = arr_b[i];
            // for (int j = 0; j < n; j++) {
            //     if(arr_a[j] > b - a) {
            //         possible = true;
            //         break;
            //     }
            // }
        }
    }
    if (bigger || possible) {
        cout << "YES";
        return 0;
    }


    int a_i;
    int a_j;
    long long sum_a = 0;
    long long sum_b = 0;

    for (int i = 0; i < n; i++) {
        sum_a += arr_a[i];
        sum_b += arr_b[i];
    }
    if(n == 2) {
        if(sum_a == sum_b) {
            cout << "YES";
            return 0;
        }
        else {
            cout << "NO"; 
            return 0;
        }
    }
    long long difference = sum_a - sum_b;
    int x = difference / (n-2);

    if(difference % (n-2) != 0) {
        cout << "NO";
        return 0;
    }

    bool flag = true;
    for(int i = 0; i < n; i++) {
        if(arr_a[i] < arr_b[i] - x || arr_a[i] > arr_b[i] + x) {
            flag = false;
            break;
        }
        if(((arr_b[i] + x - arr_a[i]) % 2) != 0) {
            flag = false;
            break;
        }
    }
    if(flag) {
        cout << "YES";
        return 0;
    }
    else {
        cout << "NO";
        return 0;
    }
     
    return 0;
}