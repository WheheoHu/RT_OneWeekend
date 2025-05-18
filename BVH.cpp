//
// Created by Wheheohu on 6/18/24.
//

#include "BVH.h"


BVH_Node::BVH_Node(Hittable_List hittable_list): BVH_Node(hittable_list.get_objects(), 0,
                                                          hittable_list.get_objects().size()) {
}

BVH_Node::BVH_Node(std::vector<std::shared_ptr<Hittable> > &objects, uint32_t start, uint32_t end) {
    //get current time as seed
    uint32_t seed = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
    int axis = random_int(0, 2, seed);
    auto comparator= (axis == 0) ? box_x_compare : ((axis == 1) ? box_y_compare : box_z_compare);
    uint32_t object_span=end-start;
    if (object_span==1) {
        left=right=objects[start];
    }else if (object_span==2) {
        left=objects[start];
        right=objects[start+1];
    }
    else  {
        std::sort(std::begin(objects)+start, std::begin(objects)+end, comparator);
        auto mid= start+object_span/2;
        left= std::make_shared<BVH_Node>(objects, start, mid);
        right= std::make_shared<BVH_Node>(objects, mid, end);
    }
    bounding_box= AABB(left->get_bounding_box(), right->get_bounding_box());

}

bool BVH_Node::hit(const Ray &ray, Interval raytime_interval, Hit_Record &record) const {
    if (!bounding_box.hit(ray, raytime_interval)) {
        return false;
    }
    auto hit_left = left->hit(ray, raytime_interval, record);
    auto hit_right = right->hit(ray, Interval(raytime_interval.min, hit_left ? record.time : raytime_interval.max),
                                record);

    return hit_left || hit_right;
}

AABB BVH_Node::get_bounding_box() const {
    return bounding_box;
}

bool BVH_Node::box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis) {
    auto a_axis_interval = a->get_bounding_box().get_axis_interval_by_index(axis);
    auto b_axis_interval = b->get_bounding_box().get_axis_interval_by_index(axis);
    return a_axis_interval.min < b_axis_interval.min;
}

bool BVH_Node::box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 0);
}

bool BVH_Node::box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 1);
}

bool BVH_Node::box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 2);
}
