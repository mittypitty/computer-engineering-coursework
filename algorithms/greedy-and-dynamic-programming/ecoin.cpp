#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> sales(n);

    for(int i = 0; i < n; i++) {
        cin >> sales[i];
    }

    int min_price = sales[0];
    int idx_buy = 1;
    int idx_best_buy = 1;
    int max_sale = 0;
    int idx_sale = 1;
    for(int i = 0; i < n; i++) {
        if(sales[i] - min_price > max_sale) {
            max_sale = sales[i] - min_price;
            idx_buy = idx_best_buy;
            idx_sale = i + 1;
        }
        if(sales[i] < min_price) {
            min_price = sales[i];
            idx_best_buy = i + 1;
        }

    }

    cout << idx_buy << " " << idx_sale;
}