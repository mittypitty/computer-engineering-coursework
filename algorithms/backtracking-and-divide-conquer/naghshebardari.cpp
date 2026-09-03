#include <bits/stdc++.h>
using namespace std;

struct House {
    int from;
    int to;
    int tall;
};

struct BreakPoint {
    int place;
    int height;
};

vector<House> city;

void insertBreak(vector<BreakPoint>& shape, int place, int height) {
    if (!shape.empty() && shape.back().place == place) {
        shape.back().height = max(shape.back().height, height);
        return;
    }

    if (!shape.empty() && shape.back().height == height) {
        return;
    }

    shape.push_back({place, height});
}

vector<BreakPoint> joinShapes(
    const vector<BreakPoint>& first,
    const vector<BreakPoint>& second
) {
    vector<BreakPoint> answer;

    int p1 = 0;
    int p2 = 0;

    int height1 = 0;
    int height2 = 0;

    while (p1 < (int)first.size() || p2 < (int)second.size()) {
        int currentPlace;

        if (p2 == (int)second.size() ||
            (p1 < (int)first.size() && first[p1].place < second[p2].place)) {
            
            currentPlace = first[p1].place;
            height1 = first[p1].height;
            p1++;
        }
        else if (p1 == (int)first.size() ||
                 second[p2].place < first[p1].place) {
            
            currentPlace = second[p2].place;
            height2 = second[p2].height;
            p2++;
        }
        else {
            currentPlace = first[p1].place;
            height1 = first[p1].height;
            height2 = second[p2].height;
            p1++;
            p2++;
        }

        insertBreak(answer, currentPlace, max(height1, height2));
    }

    return answer;
}

vector<BreakPoint> getShape(int left, int right) {
    if (left == right) {
        vector<BreakPoint> single;

        single.push_back({city[left].from, city[left].tall});
        single.push_back({city[left].to, 0});

        return single;
    }

    int middle = left + (right - left) / 2;

    vector<BreakPoint> leftShape = getShape(left, middle);
    vector<BreakPoint> rightShape = getShape(middle + 1, right);

    return joinShapes(leftShape, rightShape);
}

int main() {
    int countBuildings;
    cin >> countBuildings;

    city.resize(countBuildings);

    for (int i = 0; i < countBuildings; i++) {
        cin >> city[i].from >> city[i].to >> city[i].tall;
    }

    vector<BreakPoint> finalShape = getShape(0, countBuildings - 1);

    cout << finalShape.size() << '\n';

    for (const BreakPoint& point : finalShape) {
        cout << point.place << ' ' << point.height << '\n';
    }

    return 0;
}