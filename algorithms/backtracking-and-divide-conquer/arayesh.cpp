#include <bits/stdc++.h>
using namespace std;

void createOrder(int length, vector<int>& output) {
    if (length == 0) {
        return;
    }
    if (length == 1) {
        output.push_back(1);
        return;
    }

    vector<int> firstGroup;
    vector<int> secondGroup;

    createOrder((length + 1) / 2, firstGroup);
    createOrder(length / 2, secondGroup);

    for (int number : firstGroup) {
        output.emplace_back(number * 2 - 1);
    }
    for (int number : secondGroup) {
        output.emplace_back(number * 2);
    }
}

int main() {
    int size;
    cin >> size;
    vector<int> answer;

    answer.reserve(size); 
    createOrder(size, answer);

    for (int i = 0; i < size; i++) {
        cout << answer[i] << (i + 1 == size ? '\n' : ' ');
    }

    return 0;
}