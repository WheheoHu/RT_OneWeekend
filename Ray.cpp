//
// Created by Wheheohu on 4/20/23.
//
#include "Ray.h"


Ray::Ray() = default;

Ray::Ray(const vec3_position &origin, const vec3_direction &direction) : orig(origin), dir(direction) ,ray_time(0){


}

Ray::Ray(const vec3_position &origin, const vec3_direction &direction,double time ) : orig(origin), dir(direction) ,ray_time(time){


}

const vec3_position & Ray::getOrig() const {
    return orig;
}

const vec3_direction & Ray::getDir() const {
    return dir;
}

vec3_position Ray::at(double t) const {
    return orig + t * dir;
}

double Ray::getTime() const {
    return ray_time;
}
