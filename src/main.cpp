// Driver program for the Segmented Least squares Algorithm
#include "includes/algo.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::sort;

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

    // Segment Ranges in the format (max_index,min_index)
    cout << "Segment Ranges->" << endl;
    for (int i = ans.size() - 1; i > 0;) {
        cout << i << " " << ans[i] << endl;
        i = ans[i];
    }
    return 0;
}
