//
// Created by Wheheohu on 6/20/23.
//

#ifndef RT_ONEWEEKEND_SPHERE_H
#define RT_ONEWEEKEND_SPHERE_H

#include <utility>

#include "Hittable.h"
class Sphere :public Hittable{
public:
    //static sphere
    Sphere(vec3_position sphere_center, double r, std::shared_ptr<Material> _mat);;

    //moving sphere (moving from cen_start to cen_end in 1s)
    Sphere(vec3_position cen_start,vec3_position cen_end, double r, std::shared_ptr<Material> _mat);

    bool hit(const Ray &r, Interval ray_t, Hit_Record &record) const override;

    //get moving sphere center at time between 0 and 1
    vec3_position get_center( double time) const;
    AABB get_bounding_box() const override;
private:
    vec3_position center;
    vec3_position center_end;

    vec3_direction move_direction;
    bool is_moving;

    double radius;
    std::shared_ptr<Material> mat_ptr;

    AABB sphere_bbox;
};


#endif //RT_ONEWEEKEND_SPHERE_H
