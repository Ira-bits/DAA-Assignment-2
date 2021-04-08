// Driver program for the Segmented Least squares Algorithm
#include "ctime"
#include "includes/algo.hpp"
#include "sys/sysinfo.h"
#include "sys/types.h"

using std::cin;
using std::clock;
using std::cout;
using std::endl;
using std::setprecision;
using std::sort;
using std::stack;

void dbg_out() {
    cout << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cout << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cout << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__), cout << endl

int main() {
    double c;
    int n;
    cin >> c >> n;
    vector<pair<double, double>> coords(n);

    // Algorithm expects the co-ordinates to be pre-sorted by their x-coordinate.
    for (int i = 0; i < n; i++) {
        cin >> coords[i].first >> coords[i].second;
    }

    const clock_t begin_time = clock();
    vector<pair<double, int>> ans = calculatePenalty(coords, c);

    stack<pair<int, int>> prettyAns;
    double totalPenalty = ans[ans.size() - 1].first;
    double totalSSE = 0;

    for (int i = ans.size() - 1; i > 0;) {
        prettyAns.push({ans[i].second + 1, i + 1});
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
    cout << setprecision(10) << totalPenalty << " " << totalSSE << endl;
    std::cout << setprecision(4) << "Time taken: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}
