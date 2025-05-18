//
// Created by Wheheohu on 6/24/23.
//

#ifndef RT_ONEWEEKEND_RT_WEEKEND_H
#define RT_ONEWEEKEND_RT_WEEKEND_H

#include <cmath>
#include <memory>
#include <random>

#include <Eigen/Dense>



typedef Eigen::Vector3d vec3_color,vec3_direction,vec3_position,vec3_value;
//const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;
const double EPSILON = 1e-4;

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

//magic rcg hash
inline uint32_t pcg_hash(uint32_t input) {
    uint32_t state = input * 747796405u + 2891336453u;
    uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

//return a random number in [0, 1) using rcg hash
inline double random_pcg(uint32_t &seed) {
    seed = pcg_hash(seed);
    return static_cast<double>(seed) / std::numeric_limits<uint32_t>::max();
}

//return a random number with min and max using random_pcg
inline double random_double(double min, double max, uint32_t& seed) {
    return min + (max - min) * random_pcg(seed);
}

inline int random_int(int min, int max, uint32_t &seed) {
    return static_cast<int>(random_double(min, max+1, seed));
}

//return a random number in [0, 1) using c++ std random (SLOWWWWW)
inline double random_double(){
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the distribution for real numbers between 0 and 1
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Generate a random number
    return dis(gen);
}

inline double random_double_slow(double min, double max) {
    return min + (max - min) * random_double();
}

inline vec3_color linear2gamma(vec3_color color, float gamma) {
    return {pow(color.x(), 1.0f/gamma), pow(color.y(), 1.0f/gamma), pow(color.z(), 1.0f/gamma)};
}
inline vec3_color gamma2linear(vec3_color color, float gamma) {
    return {pow(color.x(), gamma), pow(color.y(), gamma), pow(color.z(), gamma)};
}

#include "Ray.h"
#include "Interval.h"

#endif //RT_ONEWEEKEND_RT_WEEKEND_H
