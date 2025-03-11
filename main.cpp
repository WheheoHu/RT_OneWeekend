#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Sphere.h"
#include "Hittable_List.h"
#include "Camera.h"
#include "Material.h"
#include "Timer.h"

int main() {
//TODO Fix rendering issues when camera pull far from origin
    spdlog::set_level(spdlog::level::debug);

    //World object
    Hittable_List world;

    vec3_position cube_center = vec3_position(0.f, 0.f, 0.f);
    // Add Spheres in a cube
    constexpr int CUBE_SIZE = 3;
    // for (int i = 0; i < CUBE_SIZE; i++) {
    //     for (int j = 0; j < CUBE_SIZE; j++) {
    //         for (int k = 0; k < CUBE_SIZE; ++k) {
    //             uint32_t seed = (i + 1) * (j + 1) * (k + 1);
    //             auto sphere_radius = random_double(0.15f, 0.5f, seed);
    //             sphere_radius = 0.3f;
    //             auto sphere_position = vec3_position(i - (CUBE_SIZE - 1) / 2.0f, k + 0.5f,
    //                                                  j - CUBE_SIZE / 1.0f);
    //             cube_center += sphere_position;
    //             auto sphere_color = vec3_color(0.5f, 0.5f, 0.5f);
    //             auto sphere_material = std::make_shared<Lambertian>(sphere_color);
    //             world.add(std::make_shared<Sphere>(
    //                 sphere_position, sphere_radius, sphere_material));
    //             spdlog::debug("Added sphere at position: {} {} {},with radius {:.3f}", sphere_position.x(),
    //                           sphere_position.y(), sphere_position.z(), sphere_radius);
    //         }
    //     }
    // }
    // cube_center /= CUBE_SIZE * CUBE_SIZE * CUBE_SIZE;

    world.add(std::make_shared<Sphere>(vec3_position(0.f, -100.5f, 0.f), 100.f,
    std::make_shared<Lambertian>(vec3_color(0.7f, 0.7f, 0.7f))));
    world.add(std::make_shared<Sphere>(vec3_position(0.f, 0.f, 0.0f), 0.5f,
                                       std::make_shared<Lambertian>(vec3_color(0.5f, 0.5f, 0.5f))));
    // world.add(std::make_shared<Sphere>(vec3_position(1.5f, 0.f, -0.0f), 0.5f, std::make_shared<Dielectric>(1.5f)));
    // world.add(std::make_shared<Sphere>(vec3_position(-1.5f, 0.f, -0.0f), 0.5f,
    //                                    std::make_shared<Metal>(vec3_color(1,1,1), 0.5f)));
    // world.add(std::make_shared<Sphere>(vec3_position(1.55f, -0.1f, -1.5f), vec3_position(1.55f, 0.2f, -1.5f), 0.3f,
    //                                    std::make_shared<Metal>(vec3_color(0.8f, 0.6f, 0.2f), 0.0f)));

    // Image Settings
    const uint32_t IMAGE_WIDTH = 1280;
    const uint32_t IMAGE_HEIGHT = 720;


    //Camera Settings
    const uint32_t SPP = 30;
    const uint32_t MAX_DEPTH = 15;
    const uint32_t H_FOV = 45;

    const vec3_position CAMERA_POSITION = vec3_position(0, 2.0, 5.0);
    // const vec3_direction CAMERA_DIRECTION = vec3_direction(0.f, -0.5f, -2.5f);
    const vec3_direction CAMERA_DIRECTION = (cube_center - CAMERA_POSITION).normalized();
    spdlog::debug("Camera direction: {} {} {}", CAMERA_DIRECTION.x(), CAMERA_DIRECTION.y(), CAMERA_DIRECTION.z());
    constexpr double DEFOCUS_ANGLE = -1.0;
    constexpr double FOCUS_DISTANCE = 0.5;


    Camera cam(IMAGE_WIDTH, IMAGE_HEIGHT, SPP, MAX_DEPTH, H_FOV, CAMERA_POSITION, CAMERA_DIRECTION, DEFOCUS_ANGLE,
               FOCUS_DISTANCE);
    {
        Timer timer;
        cam.render(world, false);
    }
}
