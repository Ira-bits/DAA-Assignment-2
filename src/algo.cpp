#include "includes/algo.hpp"

using std::min;
using std::pow;

double getSSE(int i, int j, vector<pair<double, double>> &coords) {
    int n = j - i + 1;                       // The number of points in the segment
    double xi, yi, sumX, sumY, sumXY, sumX2; // sumK represents Summation(ki)
    double a, b, sse;                        // The parameters of the Best Fit Line
    sse = sumX = sumY = sumXY = sumX2 = 0;

    for (int ind = i; ind <= j; ind++) {
        xi = coords[ind].first;
        yi = coords[ind].second;
        sumX += xi;
        sumY += yi;
        sumXY += xi * yi;
        sumX2 += xi * xi;
    }

    /**
     * Best fit Line => y = ax + b 
     * SSE = Sum((yi- a*xi - b)^2)
     * a = (n*Sum(xi*yi) - Sum(xi)*Sum(yi)) / (n*Sum(xi^2) - (Sum(xi))^2)
     * b = (Sum(yi) - a*Sum(xi)) / n
    */
    a = (n * sumXY - sumX * sumY) / (n * sumX2 - pow(sumX, 2));
    b = (sumY - a * sumX) / n;

    for (int ind = i; ind <= j; ind++) {
        xi = coords[ind].first;
        yi = coords[ind].second;
        sse += pow((yi - a * xi - b), 2);
    }

    return sse;
}

vector<pair<double, int>> calculatePenalty(vector<pair<double, double>> &coords, double c) {
    int n = coords.size(); // Total number of Points
    double sse;            // SSE for a combination of Segments of Points

    vector<pair<double, int>> penalty(n, {DBL_MAX, 0}); // optimal penalty for each index considering it as last in the segment
    penalty[0].first = c;                               // Since 0 will be considered the first as well as last in the segment
    double temp;

    /**
     * Using Bottom Up Dynamic Programming approach to calculate penalty.first (the dp array)
     * penalty.second conatains the segemnet start for the segment which gives optimum penalty for that index.
     * DP Relation => dp[j] = min(sse[i][j] + c + dp[i-1]) where 0<=i<j
     * c is the penalty awarded to take into account the optimal number of best fit lines
    */
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            sse = getSSE(i, j, coords); // sse for segment from  j to i
            if (i) {
                temp = sse + c + penalty[i - 1].first;
            } else {
                temp = sse + c;
            }

            if (temp < penalty[j].first) {
                penalty[j].second = i;
                penalty[j].first = temp;
            }
        }
    }

    return penalty;
}
