//
// Created by Wheheohu on 5/18/25.
//

#include "AABB.h"
#include "Interval.h"

AABB::AABB(const Interval &x, const Interval &y, const Interval &z): x(x), y(y), z(z) {
}

AABB::AABB(const vec3_position &a, const vec3_position &b) {
    x = (a.x() < b.x()) ? Interval(a.x(), b.x()) : Interval(b.x(), a.x());
    y = (a.y() < b.y()) ? Interval(a.y(), b.y()) : Interval(b.y(), a.y());
    z = (a.z() < b.z()) ? Interval(a.z(), b.z()) : Interval(b.z(), a.z());
}

AABB::AABB(const AABB &a, const AABB &b) {
    x = Interval(a.x, b.x);
    y = Interval(a.y, b.y);
    z = Interval(a.z, b.z);
}


bool AABB::hit(const Ray &r, const Interval &ray_interval) const {
    auto raytime_interval = ray_interval;
    const auto &ray_orig = r.getOrig();
    const auto &ray_dir = r.getDir();
    for (int axis = 0; axis < 3; ++axis) {
        const auto axis_interval = get_axis_interval_by_index(axis);
        auto t0 = (axis_interval.min - ray_orig[axis]) / ray_dir[axis];
        auto t1 = (axis_interval.max - ray_orig[axis]) / ray_dir[axis];
        if (t0 < t1) {
            raytime_interval.min = std::max(raytime_interval.min, t0);
            raytime_interval.max = std::min(raytime_interval.max, t1);
        } else {
            raytime_interval.min = std::max(raytime_interval.min, t1);
            raytime_interval.max = std::min(raytime_interval.max, t0);
        }

        if (raytime_interval.min > raytime_interval.max) {
            return false;
        }
    }
    return true;
}

const Interval &AABB::get_axis_interval_by_index(int axis_index) const {
    switch (axis_index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return Interval::empty_interval;
    }
}

uint32_t AABB::get_longest_axis_index() const {
    if (x.size() > y.size()) {
        return x.size() > z.size() ? 0 : 2;
    } else {
        return y.size() > z.size() ? 1 : 2;
    }
}

const AABB AABB::empty_aabb = AABB(Interval::empty_interval, Interval::empty_interval, Interval::empty_interval);
const AABB AABB::universe_aabb = AABB(Interval::universe_interval, Interval::universe_interval,
                                      Interval::universe_interval);
