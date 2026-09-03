#include <unordered_set>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    int q;
    int answer = 0;

    if(!(cin >> n)) {
        return 0;
    }
    cin.ignore();

    unordered_set<string> names;
    unordered_set<string> visited;

    for(int i = 0; i < n; i++) {
        string name;
        getline(cin, name);
        names.insert(name);
    }

    
    if(!(cin >> q)) {
        return 0;
    }
    cin.ignore();


    for (int i = 0; i < q; i++) {
        string email;
        getline(cin, email);
        if(names.find(email) != names.end()) {
            visited.insert(email);
            if(visited.size() == n) {
                answer +=1;

                visited.clear();
                visited.insert(email);
            }
        }
    }

    cout << answer;

    return 0;
}