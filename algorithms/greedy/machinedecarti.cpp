#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    vector<unsigned long long> answers(t);

    for(int i = 0; i < t; i++) {

        unsigned long long a[5];
        
        for(int j = 0; j < 5; j++) {
            cin >> a[j];
        }

        long long x = (long long)a[0] - (long long)a[2];
        long long y = (long long)a[1] - (long long)a[3];
        
        long long abs_x = llabs(x);
        long long abs_y = llabs(y);

        if(abs_x >= a[4] && abs_y >= a[4]) {
            answers[i] = (abs_x - a[4]) * (abs_x - a[4]) + (abs_y - a[4]) * (abs_y - a[4]);

        } else if(abs_x >= a[4] && abs_y < a[4]) {
            long long new_abs_x = abs_x - abs_y;
            long long new_abs_y = 0;
            long long new_k = a[4] - abs_y;
            new_abs_x = new_abs_x - new_k;

            if(new_k % 2 == 0) {
                new_abs_y = 0;
            } else {
                new_abs_y = 1;
            }


            answers[i] = (new_abs_x * new_abs_x) + (new_abs_y * new_abs_y);

        }   else if(abs_x < a[4] && abs_y >= a[4]) {
            long long new_abs_y = abs_y - abs_x;
            long long new_abs_x = 0;
            long long new_k = a[4] - abs_x;
            new_abs_y = new_abs_y - new_k;

            if(new_k % 2 == 0) {
                new_abs_x = 0;
            } else {
                new_abs_x = 1;
            }

            answers[i] = (new_abs_x * new_abs_x) + (new_abs_y * new_abs_y);

        } else {
            if((abs_x + abs_y) % 2 == 1) {
                answers[i] = 1;
            } else {
                answers[i] = 0;
            }
        }
    }

    for(int i = 0; i < t; i++) {
        cout << answers[i] << "\n";
    }

    
    return 0;
    
    //     long long s = x + y;
    //     long long d = llabs(x - y);

    //     d = max(0LL, d - 2 * a[4]);

    //     if((d % 2) != (llabs(s) % 2)) {
    //         d++;
    //     }

    //     long long ans = (s * s + d * d) / 2;

    //     cout << ans << '\n';
    // }

    // return 0;
}

