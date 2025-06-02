//
// Created by Wheheohu on 5/18/25.
//

#ifndef AABB_H
#define AABB_H
#include "Utility.h"


class AABB {
public:
    AABB() = default;

    AABB(const Interval &x, const Interval &y, const Interval &z);

    // Treat the two points(position) a and b as extrema for the bounding box
    AABB(const vec3_position &a, const vec3_position &b);

    AABB(const AABB &a, const AABB &b);

    bool hit(const Ray &r, const Interval &ray_interval) const;

    const Interval &get_axis_interval_by_index(int axis_index) const;

    uint32_t get_longest_axis_index() const;


private:
    Interval x, y, z;
};

const AABB empty_aabb = AABB(empty_interval, empty_interval, empty_interval);
const AABB universe_aabb = AABB(universe_interval, universe_interval,
                                      universe_interval);

#endif //AABB_H
