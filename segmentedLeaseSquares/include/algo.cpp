#include <limits>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include "algo.hpp"
#include "config.hpp"

using std::min;
using std::pow;

double getSSE(int i, int j, vector<pair<int, int>> &coords) {
    int n = j - i + 1;                    // The number of points in the segment
    int xi, yi, sumX, sumY, sumXY, sumX2; // sumK represents Summation(ki)
    double a, b, sse;                     // The parameters of the Best Fit Line
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

vector<int> calculatePenalty(vector<pair<int, int>> &coords, double c) {
    sort(coords.begin(), coords.end());
    int n = coords.size();    // Total number of Points
     // SSE for every combination of Segments of Points

    /*double** sse = new double*[LIMIT];
    for (int i = 0; i < LIMIT; i++)
    {
        sse[i] = new double[LIMIT];
    }
    memset(sse, 0, sizeof(sse));
    */

    auto sse = new double[LIMIT][LIMIT];
    for (int i=0;i < LIMIT;i++)
        for (int j = 0;j < LIMIT;j++)
            sse[i][j] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i - 1; j++) {
            sse[i][j] = getSSE(j, i, coords); // sse[i][j] implies sse for segment from  j to i
        }
    }

    vector<pair<double, int>> penalty(n, {LIMIT, 0}); // optimal penalty for each index considering it as last in the segment
    penalty[0].first = 0;  // Since 0 will be considered the first as well as last in the segment
    double temp;

    /**
     * Using Bottom Up Dynamic Programming approach to calculate penalty.first (the dp array)
     * penalty.second conatains the segemnet start for the segment which gives optimum penalty for that index.
     * DP Relation => dp[i] = min(sse[j][i] + C + dp[j-1]) where 0<=j<i
     * c is the penalty awarded to take into account the optimal number of best fit lines
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (j) {
                temp = sse[i][j] + c + penalty[j - 1].first;
            } else {
                temp = sse[i][j] + c;
            }
            penalty[i].second = temp < penalty[i].first ? j : penalty[i].second;
            penalty[i].first = temp < penalty[i].first ? temp : penalty[i].first;
        }
    }

    vector<int> ret(n);
    for (int i = 0; i < n; i++) {
        ret[i] = penalty[i].second;
    }
    return ret;
}
