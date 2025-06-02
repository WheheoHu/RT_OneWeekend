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

class Checker_Texture : public Texture {
public:
    Checker_Texture(const double scale, const std::shared_ptr<Texture> &even_texture,
                    const std::shared_ptr<Texture> &odd_texture) : inv_scale(1.0 / scale), even_texture(even_texture),
                                                                   odd_texture(odd_texture) {
    }

    Checker_Texture(const double scale, const vec3_color &even_color, const vec3_color &odd_color): Checker_Texture(
        scale, std::make_shared<Solid_Color>(even_color), std::make_shared<Solid_Color>(odd_color)) {
    }

    vec3_color get_value(double u, double v, const vec3_position &p) const override;

private:
    double inv_scale;
    std::shared_ptr<Texture> even_texture;
    std::shared_ptr<Texture> odd_texture;
};
#endif //TEXTURE_H
