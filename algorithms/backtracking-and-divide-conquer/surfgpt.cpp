#include <iostream>
#include <string>
using namespace std;

int n;

string makeExpression(int value, int depth) {
    string result = to_string(value);

    if (depth < n) {
        string left = makeExpression(value * 2, depth + 1);
        string right = makeExpression(value * 2 + 1, depth + 1);

        result += "+\\frac{" + left + "}{" + right + "}";
    }

    return result;
}

int main() {
    cin >> n;

    cout << makeExpression(1, 1) << endl;

    return 0;
}