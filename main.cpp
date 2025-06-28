#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Sphere.h"
#include "Hittable_List.h"
#include "Camera.h"
#include "Material.h"
#include "Timer.h"
#include "BVH.h"

int main() {
    //TODO Fix rendering issues when camera pull far from origin
    spdlog::set_level(spdlog::level::debug);

    //World object
    Hittable_List world;

    vec3_position cube_center = vec3_position(0.f, 0.f, 0.f);
    // Add Spheres in a cube
    constexpr int CUBE_SIZE = 3;
    for (int i = 0; i < CUBE_SIZE; i++) {
        for (int j = 0; j < CUBE_SIZE; j++) {
            for (int k = 0; k < CUBE_SIZE; ++k) {
                uint32_t seed = (i + 1) * (j + 1) * (k + 1);
                auto sphere_radius = random_double(0.15f, 0.5f, seed);
                // sphere_radius = 0.3f;
                auto sphere_position = vec3_position(i - (CUBE_SIZE - 1) / 2.0f, k + 0.5f,
                                                     j - CUBE_SIZE / 1.0f);
                cube_center += sphere_position;
                auto sphere_color = vec3_color(0.6f, 0.6f, 0.5f);
                auto material_metal = std::make_shared<Metal>(sphere_color);
                auto material_lambertian = std::make_shared<Lambertian>(sphere_color);
                auto material_dielectric = std::make_shared<Dielectric>(1.5);

                std::shared_ptr<Material> sphere_material;
                // if (random_double(-1, 1, seed) > 0) {
                //     sphere_material = material_dielectric;
                // } else {
                //     sphere_material = material_metal;
                // }
                //random choose a material
                switch (random_int(0, 3, seed)) {
                    case 0:
                        sphere_material = material_lambertian;
                        break;
                    case 1:
                        sphere_material = material_metal;
                        break;
                    case 2:
                        sphere_material = material_dielectric;
                        break;
                    default:
                        sphere_material = material_lambertian;
                        break;
                }
                world.add(std::make_shared<Sphere>(
                    sphere_position, sphere_radius, sphere_material));
                spdlog::debug("Added sphere at position: {} {} {},with radius {:.3f},Material: {}", sphere_position.x(),
                              sphere_position.y(), sphere_position.z(), sphere_radius, sphere_material->get_name());
            }
        }
    }
    cube_center /= CUBE_SIZE * CUBE_SIZE * CUBE_SIZE;

    // for (int i = 0; i < 5; ++i) {
    //     world.add(std::make_shared<Sphere>(vec3_position(0, 0, -i), 0.2f,
    //                                        std::make_shared<Lambertian>(vec3_color(0.5f, 0.5f, 0.5f))));
    // }
    //Ground Sphere
    auto checker_texture=std::make_shared<Checker_Texture>(0.5,vec3_color(1.0,1.0,1.0),vec3_color(0.0,0.0,1.0));
    world.add(std::make_shared<Sphere>(vec3_position(0.f, -100.5f, 0.f), 100.f,
                                       std::make_shared<Lambertian>(checker_texture)));

    // world.add(std::make_shared<Sphere>(vec3_position(0., 0, 0), 0.5,
    //                                    std::make_shared<Lambertian>(vec3_color(0.5, 0.5, 0.5))));
    // world.add(std::make_shared<Sphere>(vec3_position(1.5f, 0.f, -0.0f), 0.5f, std::make_shared<Dielectric>(1.5f)));
    // world.add(std::make_shared<Sphere>(vec3_position(-1.5f, 0.f, -0.0f), 0.5f,
    //                                    std::make_shared<Metal>(vec3_color(1,1,1), 0.0)));
    // world.add(std::make_shared<Sphere>(vec3_position(1.55f, -0.1f, -1.5f), vec3_position(1.55f, 0.2f, -1.5f), 0.3f,
    //                                    std::make_shared<Metal>(vec3_color(0.8f, 0.6f, 0.2f), 0.0f)));

    {
        Timer timer;
        //Build BVH for world
        world = Hittable_List(std::make_shared<BVH_Node>(world));
    }
    spdlog::debug("BVH building finished");
    // Image Settings
    const uint32_t IMAGE_WIDTH = 1280;
    const uint32_t IMAGE_HEIGHT = 720;


    //Camera Settings
    const uint32_t SPP = 30;
    const uint32_t MAX_DEPTH = 15;
    const uint32_t H_FOV = 55;
    vec3_position camera_focus = cube_center;
    const vec3_position CAMERA_POSITION = vec3_position(0, 5, 6);
    // const vec3_direction CAMERA_DIRECTION = vec3_direction(0.f, -0.5f, -2.5f);
    const vec3_direction CAMERA_DIRECTION = (camera_focus - CAMERA_POSITION).normalized();
    spdlog::debug("Camera direction: {} {} {}", CAMERA_DIRECTION.x(), CAMERA_DIRECTION.y(), CAMERA_DIRECTION.z());
    constexpr double DEFOCUS_ANGLE = -1.0;
    constexpr double FOCUS_DISTANCE = 10;


    Camera cam(IMAGE_WIDTH, IMAGE_HEIGHT, SPP, MAX_DEPTH, H_FOV, CAMERA_POSITION, CAMERA_DIRECTION, DEFOCUS_ANGLE,
               FOCUS_DISTANCE); {
        Timer timer;
        cam.render(world, false);
    }
}
