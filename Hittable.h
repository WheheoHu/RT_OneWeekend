//
// Created by Wheheohu on 6/20/23.
//

#ifndef RT_ONEWEEKEND_HITTABLE_H
#define RT_ONEWEEKEND_HITTABLE_H
#include <memory>

#include "BVH.h"
#include "Ray.h"
#include "Interval.h"
#include "Material.h"

class Hit_Record {
public:
    vec3_position position;
    vec3_direction normal;
    double time;
    bool front_face;
    std::shared_ptr<Material> mat_ptr;
    inline void set_face_normal(const Ray &ray, const vec3_direction &outward_normal) {
        front_face = ray.getDir().dot(outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;

    }
};

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray &r, Interval ray_t, Hit_Record &record) const = 0;
    virtual AABB get_bounding_box() const = 0;
};


#endif //RT_ONEWEEKEND_HITTABLE_H
