//
// Created by Wheheohu on 4/20/23.
//

#ifndef RT_ONEWEEKEND_RAY_H
#define RT_ONEWEEKEND_RAY_H

#include "Utility.h"

class Ray {
public:
    Ray();

    Ray(const vec3_position &origin, const vec3_direction &direction);
    Ray(const vec3_position &origin, const vec3_direction &direction,double time );

    [[nodiscard]] double getTime() const;
    [[nodiscard]] const vec3_position & getOrig() const;

    [[nodiscard]] const vec3_direction & getDir() const;

    [[nodiscard]] vec3_position at(float t) const;


private:
    vec3_position orig;
    vec3_direction dir;
    double ray_time=0;

};


#endif //RT_ONEWEEKEND_RAY_H
