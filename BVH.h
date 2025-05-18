//
// Created by Wheheohu on 6/18/24.
//

#ifndef RT_ONEWEEKEND_BVH_H
#define RT_ONEWEEKEND_BVH_H
#include "Interval.h"
#include "Utility.h"
#include "Hittable.h"
#include "Hittable_List.h"



class BVH_Node : public Hittable {
    //Delegating Constructor

public:
    BVH_Node(Hittable_List hittable_list);

    BVH_Node(std::vector<std::shared_ptr<Hittable> > &objects, uint32_t start, uint32_t end);

    bool hit(const Ray &ray, Interval raytime_interval, Hit_Record &record) const override;

    AABB get_bounding_box() const override;

private:
    AABB bounding_box;
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;
    static bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis);
    static bool box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
    static bool box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
    static bool box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
};


#endif //RT_ONEWEEKEND_BVH_H
