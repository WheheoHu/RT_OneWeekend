//
// Created by Wheheohu on 6/18/24.
//

#ifndef RT_ONEWEEKEND_BVH_H
#define RT_ONEWEEKEND_BVH_H
#include "Interval.h"
#include "RT_Weekend.h"


class BVH {

};

class AABB {
public:
    AABB() = default;
    AABB(const Interval &x, const Interval &y, const Interval &z);

    // Treat the two points(position) a and b as extrema for the bounding box
    AABB(const vec3_position& a, const vec3_position& b);
    AABB(const AABB& a, const AABB& b);

    bool hit(const Ray& r) const;


private:
    Interval x, y, z;
    const Interval& get_axis_interval_by_index(int axis_index) const;

};

#endif //RT_ONEWEEKEND_BVH_H
