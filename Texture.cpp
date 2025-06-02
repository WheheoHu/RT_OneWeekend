//
// Created by Wheheohu on 5/25/25.
//

#include "Texture.h"
#include <cmath>

vec3_color Solid_Color::get_value(double u, double v, const vec3_position &p) const {
    return albedo;
}

vec3_color Checker_Texture::get_value(double u, double v, const vec3_position &p) const {
    int x_integer = static_cast<int>(std::floor(inv_scale * p.x()));
    int y_integer = static_cast<int>(std::floor(inv_scale * p.y()));
    int z_integer = static_cast<int>(std::floor(inv_scale * p.z()));
    
    bool is_even = (x_integer + y_integer + z_integer) % 2 == 0;
    
    return is_even ? even->get_value(u, v, p) : odd->get_value(u, v, p);
}
