// Driver program for the Segmented Least squares Algorithm
#include "includes/algo.hpp"
#include <stack>
using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::stack;

int main() {
    double c;
    int n;
    cin >> c >> n;
    vector<pair<double, double>> coords(n);

    // Algorithm expects the co-ordinates to be pre-sorted by their x-coordinate.
    for (int i = 0; i < n; i++) {
        cin >> coords[i].first >> coords[i].second;
    }
    vector<int> ans = calculatePenalty(coords, c);

    stack<pair<int, int>> prettyAns;

    for (int i = ans.size() - 1; i > 0;) {
        prettyAns.push({ans[i] + 1, i + 1});
        i = ans[i];
    }

    while (!prettyAns.empty()) {
        auto curr = prettyAns.top();
        prettyAns.pop();
        cout << curr.first << " " << curr.second << endl;
    }

    return 0;
}
