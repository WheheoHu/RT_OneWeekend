//
// Created by Wheheohu on 6/22/23.
//

#ifndef RT_ONEWEEKEND_HITTABLE_LIST_H
#define RT_ONEWEEKEND_HITTABLE_LIST_H
#include <vector>
#include "Hittable.h"
class Hittable_List: public Hittable   {
public:
    Hittable_List();
    explicit Hittable_List(const std::shared_ptr<Hittable>& object);
    void clear();
    void add(const std::shared_ptr<Hittable>& object);

    bool hit(const Ray &r, Interval ray_t, Hit_Record &record) const override;

    AABB get_bounding_box() const override;


    std::vector<std::shared_ptr<Hittable>> &get_objects() {
        return objects;
    }

private:
    std::vector<std::shared_ptr<Hittable>> objects;
    AABB hitable_list_bbox;
};


#endif //RT_ONEWEEKEND_HITTABLE_LIST_H
