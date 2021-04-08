#pragma once
#include <bits/stdc++.h>

using std::pair;
using std::vector;

/**
 * \brief Calculates the Sum of Squared Errors for Best Fit Line for points i to j.
 * \param int i start index for the set of points.
 * \param int j end index for the set of points.
 * \param vector<pair<double,double>>& set of (x,y) co-ordinates of the points.
 * \return double the Sum of Squared Errors.
*/
double getSSE(int, int, vector<pair<double, double>> &);

/**
 * \brief Calculates Optimal Penalty for each point, considering it to be the last in segment.
 * \param vector<pair<double,double>>& set of (x,y) co-ordinates of the points.
 * \param double the cost of adding lines.
 * \return vector<pair<double,int>> a vector of segment start index with minimum penalty for each.
*/
vector<pair<double, int>> calculatePenalty(vector<pair<double, double>> &, double);
