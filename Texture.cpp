//
// Created by Wheheohu on 6/3/25.
//

#include "Texture.h"


vec3_color Checker_Texture::get_value(double u, double v, const vec3_position &p) const {
    int x_int = static_cast<int>(floor(inv_scale * p.x));
    int y_int = static_cast<int>(floor(inv_scale * p.y));
    int z_int = static_cast<int>(floor(inv_scale * p.z));
    bool is_even = (x_int + y_int + z_int) % 2 == 0;
    return is_even ? even_texture->get_value(u, v, p) : odd_texture->get_value(u, v, p);
}
