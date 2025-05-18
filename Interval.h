//
// Created by Wheheohu on 1/11/24.
//

#ifndef RT_ONEWEEKEND_INTERVAL_H
#define RT_ONEWEEKEND_INTERVAL_H
#include <cmath>

const double infinity = std::numeric_limits<double>::infinity();

class Interval {
public:
    double min, max;
    Interval();
    Interval(double min, double max);
    Interval(const Interval& a, const Interval& b);
    bool contains(const double x) const;
    bool surrounds(const double x) const;
    Interval expand(const double delta) const;



    static const Interval empty,universe;
};
static const Interval empty_interval(infinity, -infinity);
static const Interval universe_interval(-infinity, infinity);


#endif //RT_ONEWEEKEND_INTERVAL_H
