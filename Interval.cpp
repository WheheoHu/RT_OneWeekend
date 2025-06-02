//
// Created by Wheheohu on 1/11/24.
//

#include "Interval.h"

#include <algorithm>

Interval::Interval(double min, double max): min(min), max(max) {}

Interval::Interval(const Interval &a, const Interval &b) {
    min=std::min(a.min, b.min);
    max=std::max(a.max, b.max);
}

Interval::Interval(): min(+infinity), max(-infinity) {}

bool Interval::contains(const double x) const {
    return x >= min && x <= max;
}

bool Interval::surrounds(const double x) const {
    return x > min && x < max;
}

Interval Interval::expand(const double delta) const {
    const auto pandding = delta / 2;
    return {min - pandding, max + pandding};
}

double Interval::size() const {
    return abs(max-min);
}


