#include <iostream>
using namespace std;

int main() {
        int n;
        int a[101];
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int m;
        int b[101];
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }


        int c[101];
        for (int i = 0; i < n; i++) {
            int temp = a[i];
            c[i] = temp;
            for (int j = i + 1; j < n; j++) {
                temp += a[j];
                if (temp > c[i]) {
                    c[i] = temp;
                }
            }
        }

        int d[101];
         for (int i = 0; i < m; i++) {
            int temp = b[i];
            d[i] = temp;
            for (int j = i + 1; j < m; j++) {
                temp += b[j];
                if (temp > d[i]) {
                    d[i] = temp;
                } 
            }
        }

        int n_ptr = 0;
        int m_ptr = 0;
        int current = 0;
        int result = 0;

        for (int i = 0; i < n + m; i++) {
            if (n_ptr >= n) {
                current += b[m_ptr];
                m_ptr++;
            } 
            else if (m_ptr >= m) {
                current += a[n_ptr];
                n_ptr++;
            } 
            else if (c[n_ptr] > d[m_ptr]) {
                current += a[n_ptr];
                n_ptr++;
            } 
            else if (d[m_ptr] > c[n_ptr]) {
                current += b[m_ptr];
                m_ptr++;
            } else {
                if (a[n_ptr] > b[m_ptr]) {
                    current += a[n_ptr];
                    n_ptr++;
                } else {
                    current += b[m_ptr];
                    m_ptr++;
                }
            }

            if (current > result) {
                result = current;
            }
        }
        cout << result;
        
    return 0;
}
