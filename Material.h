//
// Created by Wheheohu on 2/26/24.
//

#ifndef RT_ONEWEEKEND_MATERIAL_H
#define RT_ONEWEEKEND_MATERIAL_H

#include "Utility.h"


class Hit_Record;

class Material {
public:
    virtual ~Material() = default;
    virtual std::string get_name() const = 0;
    virtual bool scatter(const Ray &r_in, const Hit_Record &rec, vec3_value &attenuation, Ray &scattered) const = 0;

};

class Lambertian : public Material {
public:
    explicit Lambertian(const vec3_color &albedo) : albedo(albedo) {}

    std::string get_name() const override;

    bool scatter(const Ray &r_in, const Hit_Record &rec, vec3_value &attenuation, Ray &scattered) const override;

private:
    vec3_value albedo;
};

class Metal : public Material {
public:
    Metal(const vec3_value &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    std::string get_name() const override;

    bool scatter(const Ray &r_in, const Hit_Record &rec, vec3_value &attenuation, Ray &scattered) const override;

private:
    vec3_value albedo;
    double fuzz;
};

class Dielectric : public Material {
public:
    explicit Dielectric(double ref_idx) : ref_idx(ref_idx) {}

    std::string get_name() const override;

    bool scatter(const Ray &r_in, const Hit_Record &rec, vec3_value &attenuation, Ray &scattered) const override;

private:
    double ref_idx;
    static double reflectance(double cosine,double ref_idx);
};


#endif //RT_ONEWEEKEND_MATERIAL_H
