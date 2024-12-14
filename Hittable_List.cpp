//
// Created by Wheheohu on 6/22/23.
//

#include "Hittable_List.h"



Hittable_List::Hittable_List(const std::shared_ptr<Hittable>& object) {
    add(object);

}

bool Hittable_List::hit(const Ray &r, Interval ray_t, Hit_Record &record) const {
    Hit_Record temp_rec{};
    bool hit_anything = false;
    auto closest_so_far = ray_t.max;

    for (const auto& obj: objects) {
        if (obj->hit(r, Interval(ray_t.min,closest_so_far), temp_rec)){
            hit_anything= true;
            closest_so_far=temp_rec.t;
            record=temp_rec;
        }
    }
    return hit_anything;
}

AABB Hittable_List::get_bounding_box() const {
    return hitable_list_bbox;
}

void Hittable_List::clear() {
    objects.clear();
}

void Hittable_List::add(const std::shared_ptr<Hittable>& object) {
    objects.push_back(object);
    hitable_list_bbox=AABB(hitable_list_bbox,object->get_bounding_box());

}

Hittable_List::Hittable_List() = default;
