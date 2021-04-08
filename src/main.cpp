// Driver program for the Segmented Least squares Algorithm
#include "includes/algo.hpp"

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
    vector<pair<double, int>> ans = calculatePenalty(coords, c);

    stack<pair<int, int>> prettyAns;
    double totalPenalty = 0;
    double totalSSE = 0;

    for (int i = ans.size() - 1; i > 0;) {
        prettyAns.push({ans[i].second + 1, i + 1});
        totalPenalty += ans[i].first;
        totalSSE += getSSE(ans[i].second, i, coords);
        i = ans[i].second - 1;
    }

    cout << prettyAns.size() << endl; // Total Number of Segments
    while (!prettyAns.empty()) {
        auto curr = prettyAns.top();
        prettyAns.pop();
        cout << curr.first << " " << curr.second << endl;
    }

    // Total Penalty and Total SSE for the optimal Solution
    cout << totalPenalty << " " << totalSSE << endl;

    return 0;
}
