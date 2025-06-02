//
// Created by Wheheohu on 5/25/25.
//

#include "Texture.h"



vec3_color Solid_Color::get_value(double u, double v, const vec3_position &p) const {
    return albedo;
}

vec3_color Checker_Texture::get_value(double u, double v, const vec3_position &p) const {

}
