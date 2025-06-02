//
// Created by Wheheohu on 6/3/25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include "Utility.h"


class Texture {
public:
    virtual ~Texture() = default;

    virtual vec3_color get_value(double u, double v, const vec3_position &p) const = 0;
};

class Solid_Color : public Texture {
public:
    Solid_Color(vec3_color albedo) : albedo(albedo) {
    }

    Solid_Color(double r, double g, double b) : albedo(r, g, b) {
    }

    vec3_color get_value(double u, double v, const vec3_position &p) const override {
        return albedo;
    }

private:
    vec3_color albedo;
};


#endif //TEXTURE_H
