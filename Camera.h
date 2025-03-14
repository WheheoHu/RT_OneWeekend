//
// Created by Wheheohu on 2/8/24.
//

#ifndef RT_ONEWEEKEND_CAMERA_H
#define RT_ONEWEEKEND_CAMERA_H

#include "Utility.h"

#include "Hittable_List.h"


class Camera {
public:
    Camera(uint32_t imageWidth, uint32_t imageHeight, uint32_t spp, uint32_t maxDepth, uint32_t h_FOV,
           vec3_position cameraPosition, vec3_direction cameraDirection, double defocusAngle, double focusDistance);

    void render(const Hittable &world, bool multithreading);

private:

    vec3_color ray_color(const Ray &ray, const Hittable &world, uint32_t depth);
    Ray get_ray(float w, float h, uint32_t seed);
    vec3_position defocus_disk_sample(uint32_t seed);
    uint32_t image_width;
    uint32_t image_height;
    uint32_t SPP;
    uint32_t max_depth;

    uint32_t h_fov;

    vec3_position camera_position;
    vec3_direction camera_direction;


    double defocus_angle;
    double focus_distance;

    vec3_direction camera_u,camera_v,camera_w;//Camera frame basis vectors,camera_u pointing to camera right,camera_v pointing to camera up,camera_w pointing **opposite** the view direction
    vec3_direction vector_up; //vector for camera up
    vec3_direction defocus_disk_u;
    vec3_direction defocus_disk_v;

    double image_aspect_ratio;



    vec3_position camera_center;

    vec3_direction pixel_delta_u;
    vec3_direction pixel_delta_v;

    vec3_position pixel_00_location;
};


#endif //RT_ONEWEEKEND_CAMERA_H
