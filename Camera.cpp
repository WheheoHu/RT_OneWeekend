//
// Created by Wheheohu on 2/8/24.
//
#include <iostream>
#include <fstream>
#include <thread>
// #include <omp.h>
#include <spdlog/spdlog.h>
#include "Camera.h"
#include "Image_Render.h"
#define DEBUG 0
//override << operator for glm::vec3 for ppm image output
inline std::ostream &operator<<(std::ostream &out, Eigen::Vector3f &v) {
    return out << static_cast<int>(v.x()) << " " << static_cast<int>(v.y()) << " " << static_cast<int>(v.z());
}


void Camera::render(const Hittable &world, const bool multithreading) {
    std::vector<vec3_color> framebuffer(image_width * image_height);
    if (multithreading) {
#define OMP 0

#if OMP
        const uint32_t n_tread = std::thread::hardware_concurrency();

        std::cout << "hardware_concurrency: " << n_tread << std::endl;
        omp_set_num_threads(static_cast<int>(n_tread));

#pragma omp parallel for default(none) shared(framebuffer, world)
        for (uint32_t h = 0; h < image_height; h++) {

            for (int w = 0; w < image_width; ++w) {
                uint32_t seed = w * h * image_width;
                vec3_color pixel_color(0.f, 0.f, 0.f);
                for (int sample_index = 0; sample_index < SPP; ++sample_index) {
                    auto u = (w + random_double(-0.5f, 0.5f, seed));
                    auto v = (h + random_double(-0.5f, 0.5f, seed));
                    pixel_color +=
                            ray_color(get_ray(u, v, seed), world, max_depth) / static_cast<float>(SPP);
                }
                pixel_color = linear2gamma(pixel_color, 2.2f);
                auto temp_vec = pixel_color * 255.0f;
                framebuffer[h * image_width + w] = temp_vec;
            }
        }
#else
        const uint32_t n_tread = std::thread::hardware_concurrency();
        spdlog::debug("hardware_concurrency: {}", n_tread);
        // std::cout << "hardware_concurrency: " << n_tread << std::endl;
        std::vector<std::thread> thread_vector;
        thread_vector.reserve(n_tread);
        for (uint32_t i = 0; i < n_tread; ++i) {
            thread_vector.emplace_back(
                [&, i]() {
                    for (uint32_t h = i; h < image_height; h += n_tread) {
                        for (int w = 0; w < image_width; ++w) {
                            uint32_t seed = w * h * image_width;
                            vec3_color pixel_color(0.f, 0.f, 0.f);
                            for (int sample_index = 0; sample_index < SPP; ++sample_index) {
                                auto u = (w + random_double(-0.5f, 0.5f, seed));
                                auto v = (h + random_double(-0.5f, 0.5f, seed));
                                pixel_color +=
                                        ray_color(get_ray(u, v, seed), world, max_depth) / static_cast<float>(SPP);
                            }
                            pixel_color = linear2gamma(pixel_color, 2.2f);
                            //convert color value from 0~1 to 0~255
                            vec3_value temp_vec = pixel_color * 255.0f;
                            framebuffer[h * image_width + w] = temp_vec;
                        }
                    }
                }
            );
        }
        for (auto &&thread: thread_vector) {
            thread.join();
        }
#endif
    } else {
        for (int h = 0; h <= image_height - 1; ++h) {
            std::cerr << "\rOutput: " << static_cast<uint32_t>(100.0 * static_cast<float>(h) / image_height) << '%' <<
                    std::flush;
            for (int w = 0; w < image_width; ++w) {
                uint32_t seed = w * h * image_width;

                vec3_color pixel_color(0.f, 0.f, 0.f);
                for (int i = 0; i < SPP; ++i) {
                    auto u = (w + random_double(-0.5f, 0.5f, seed));
                    auto v = (h + random_double(-0.5f, 0.5f, seed));
                    pixel_color += ray_color(get_ray(u, v, seed), world, max_depth) / static_cast<float>(SPP);
                }
                pixel_color = linear2gamma(pixel_color, 2.2f);
                auto temp_vec = pixel_color * 255.0f;
                framebuffer[h * image_width + w] = temp_vec;
            }
        }
        std::cerr << "\rOutput: 100%" << std::endl;
    }


    //output bmp img from framebuffer
    BMP_Image_Render bmp_image_render(framebuffer);
    if (bmp_image_render.render("../Output/Result.bmp", image_width, image_height)) {
        spdlog::info("Render Success,bmp file is located at ../Output/Result.bmp");
    } else {
        spdlog::error("Render Failed");
    }


    //output ppm img from framebuffer
    //    std::fstream result_img;
    //    result_img.open("../Output/Result.ppm", std::ios::out);
    //    result_img << "P3\n";
    //    result_img << image_width << " " << image_height << "\n";
    //    result_img << 255 << "\n";
    //    for (auto &&pixel: framebuffer) {
    //        result_img << pixel << "\n";
    //    }
    //    std::cout << "\rOutput: 100%" << std::endl;
    //    result_img.close();
}


vec3_color Camera::ray_color(const Ray &ray, const Hittable &world, uint32_t depth) {
    if (depth <= 0) {
        return {0.0f, 0.0f, 0.0f};
    }
    Hit_Record record{};

    if (world.hit(ray, Interval(0.001, +infinity), record)) {
        Ray scattered;
        vec3_color attenuation;
        auto mat = record.mat_ptr;
        record.position += record.normal * 0.001f;
        // spdlog::debug("Material:{}", mat->get_name());
        if (mat->scatter(ray, record, attenuation, scattered)) {
            return attenuation.cwiseProduct(ray_color(scattered, world, depth - 1));
        }
        return {0, 0, 0};
    }

    //background vec3_color
    vec3_direction ray_dir = ray.getDir().normalized();
    auto t = 0.5f * (ray_dir.y() + 1.0f);
    return (1.0f - t) * gamma2linear(vec3_color(1.0f, 1.0f, 1.0f), 2.2f) + t * gamma2linear(
               vec3_color(0.5f, 0.7f, 1.0f), 2.2f);
}

Camera::Camera(uint32_t imageWidth, uint32_t imageHeight, uint32_t spp, uint32_t maxDepth, uint32_t h_FOV,
               vec3_position cameraPosition, vec3_direction cameraDirection, float defocusAngle, float focusDistance)
    : image_width(imageWidth),
      image_height(imageHeight),
      SPP(spp),
      max_depth(maxDepth),
      h_fov(h_FOV),
      camera_position(std::move(cameraPosition)),
      camera_direction(std::move(cameraDirection)),
      defocus_angle(defocusAngle),
      focus_distance(focusDistance) {
    image_aspect_ratio = static_cast<float>(image_width) / image_height;


    camera_center = camera_position;
    auto fov_radians = degrees_to_radians(h_fov);

    //setting up viewport
    camera_direction.normalize();
    vup.normalize();

    auto viewport_width = 2 * focus_distance * tan(fov_radians / 2.0f);
    auto viewport_height = viewport_width / image_aspect_ratio;


    camera_w = camera_direction;
    camera_u = camera_direction.cross(vup).normalized();
    camera_v = camera_u.cross(camera_w).normalized();


    vec3_direction viewport_u = static_cast<float>(viewport_width) * camera_u;
    vec3_direction viewport_v = static_cast<float>(viewport_height) * -camera_v;

    pixel_delta_u = viewport_u / static_cast<float>(image_width);
    pixel_delta_v = viewport_v / static_cast<float>(image_height);


    vec3_position viewport_upper_left =
            camera_center + focus_distance * camera_w - viewport_u / 2.0f - viewport_v / 2.0f;

    float defocus_radius = focus_distance * static_cast<float>(tan(degrees_to_radians(defocus_angle / 2.0f)));
    defocus_disk_u = camera_u * defocus_radius;
    defocus_disk_v = camera_v * defocus_radius;

    //pixel (0,0) center location
    pixel_00_location = viewport_upper_left + pixel_delta_u / 2.0f + pixel_delta_v / 2.0f;
}

inline vec3_position random_in_unit_disk(uint32_t &seed) {
    vec3_position p;
    do {
        p = vec3_position(random_double(-1.f, 1.f, seed), random_double(-1.f, 1.f, seed), 0.0f);
    } while (p.dot(p) >= 1.0f);
    return p;
}


Ray Camera::get_ray(float w, float h, uint32_t seed) {
    vec3_position pixel_center =
            pixel_00_location + w * pixel_delta_u + h * pixel_delta_v;
    auto ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample(seed);

#if  DEBUG
    ray_origin = camera_center;
#endif
    vec3_direction ray_direction = pixel_center - ray_origin;
    auto ray_time = random_double(0.0f, 1.0f, seed);
    return Ray(ray_origin, ray_direction.normalized(), ray_time);
}

vec3_position Camera::defocus_disk_sample(uint32_t seed) {
    auto p = random_in_unit_disk(seed);
    return camera_position + p.x() * defocus_disk_u + p.y() * defocus_disk_v;
}
