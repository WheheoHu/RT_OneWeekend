//
// Created by Wheheohu on 6/20/23.
//

#include "Sphere.h"
#include "Interval.h"

bool Sphere::hit(const Ray &r, Interval ray_time_interval, Hit_Record &record) const {
    auto current_center = get_center(r.getTime());

    auto oc = r.getOrig() - current_center;
    auto a = r.getDir().dot(r.getDir());
    auto b = 2 * r.getDir().dot(oc);
    auto c = oc.dot(oc) - pow(radius, 2);

    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    auto root = (-b - sqrt(discriminant)) / (2.0 * a);
    if (!ray_time_interval.surrounds(root)) {
        root = (-b + sqrt(discriminant)) / (2.0 * a);
        if (!ray_time_interval.surrounds(root)) {
            return false;
        }
    }

    record.time = root;
    record.position = r.at(record.time);


    vec3_direction outward_normal = (record.position - current_center) / radius;
    outward_normal.normalize();
    record.set_face_normal(r, outward_normal);
    //record.p+=EPSILON*outward_normal.normalized();

    record.position += EPSILON * record.normal;
    record.mat_ptr = mat_ptr;
    return true;
}

Sphere::Sphere(vec3_position center_start, vec3_position center_end, double r,
               std::shared_ptr<Material> _mat) : center(std::move(center_start)), center_end(std::move(center_end)),
                                                 radius(r), mat_ptr(std::move(_mat)), is_moving(true) {
    move_direction = center_end - center;
    const auto temp_radius_vector = vec3_direction(r, r, r);
    const auto start_bbox = AABB(center_start - temp_radius_vector, center_start + temp_radius_vector);
    const auto end_bbox = AABB(center_end - temp_radius_vector, center_end + temp_radius_vector);
    sphere_bbox = AABB(start_bbox, end_bbox);
}

Sphere::Sphere(vec3_position sphere_center, double r,
               std::shared_ptr<Material> _mat) : center(std::move(sphere_center)), radius(r), mat_ptr(std::move(_mat)),
                                                 is_moving(false) {
    auto temp_radius_vector = vec3_direction(r, r, r);
    sphere_bbox = AABB(center - temp_radius_vector, center + temp_radius_vector);
}

vec3_position Sphere::get_center(double time) const {
    if (!is_moving) {
        return center;
    }
    return center + move_direction * time;
}

AABB Sphere::get_bounding_box() const {
    return sphere_bbox;
}
