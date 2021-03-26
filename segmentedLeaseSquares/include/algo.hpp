#pragma once

using std::pair;
using std::vector;

/**
 * \brief Calculates the Sum of Squared Errors for Best Fit Line for points i to j.
 * \param int i start index for the set of points.
 * \param int j end index for the set of points.
 * \param vector<pair<int,int>>& set of (x,y) co-ordinates of the points.
 * \return double the Sum of Squared Errors.
*/
double getSSE(int, int, vector<pair<int, int>> &);

/**
 * \brief Calculates Optimal Penalty for each point, considering it to be the last in segment.
 * \param vector<pair<int,int>>& set of (x,y) co-ordinates of the points.
 * \param double the cost of adding lines.
 * \return vector<int> a vector of segment start index with minimum penalty for each.
*/
vector<int> calculatePenalty(vector<pair<int, int>> &, double);
