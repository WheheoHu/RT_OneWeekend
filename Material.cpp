//
// Created by Wheheohu on 2/26/24.
//

#include "Material.h"
#include "Hittable.h"

inline vec3_direction diffuse_random_direction(uint32_t seed) {

    seed = seed * 747796405u + 2891336453u;
    double z = random_double(-1, 1, seed) ;

    seed = seed * 747796405u + 2891336453u;
    double phi = 2.0 * M_PI * random_double(0, 1, seed);

    double r = sqrt(1.0 - z * z);
    double x = r * cos(phi);
    double y = r * sin(phi);

    return vec3_direction(x, y, z);
}

inline vec3_direction reflect(const vec3_direction &v, const vec3_direction &n) {
    return v - 2 * v.dot(n) * n;
}

//refrect ray camera_v by normal n
//Note:camera_v and n are both normalized
inline vec3_direction refrect(const vec3_direction &v, const vec3_direction &n, double eta_in, double eta_out) {
    auto cos_theta = fmin((-v).dot(n), 1.0);
    auto r_out_perp = static_cast<float>(eta_in / eta_out) * (v + static_cast<float>(cos_theta) * n);
    auto r_out_parallel = -static_cast<float>(sqrt(fabs(1.0 - pow(r_out_perp.norm(), 2)))) * n;
    return r_out_perp + r_out_parallel;
}

std::string Lambertian::get_name() const {
    return "Lambertian";
}

bool Lambertian::scatter(const Ray &r_in, const Hit_Record &rec, vec3_value &attenuation, Ray &scattered) const {
    auto seed = static_cast<uint32_t>(rec.position.norm() * rec.time *1000000);
    auto diffuse_direction = diffuse_random_direction(seed);
    if (diffuse_direction.dot(rec.normal) <= 0) {
        diffuse_direction = -diffuse_direction;
    }

    vec3_direction scatter_direction = rec.normal + diffuse_direction;
    if (scatter_direction.squaredNorm() < 1e-8) {
        scatter_direction = rec.normal;
    }
    scatter_direction.normalize();
    attenuation = texture->get_value(rec.u,rec.v,rec.position);
    scattered = Ray(rec.position, scatter_direction, r_in.getTime());

    return true;
}

std::string Metal::get_name() const {
    return "Metal";
}

bool Metal::scatter(const Ray &r_in, const Hit_Record &rec, vec3_value &attenuation, Ray &scattered) const {
    auto seed = static_cast<uint32_t>(rec.position.norm() * rec.time *1000000);
    auto reflect_direction = reflect(r_in.getDir().normalized(), rec.normal);
    auto reflect_fuzzed = reflect_direction + fuzz * diffuse_random_direction(seed);
    scattered = Ray(rec.position, reflect_fuzzed.normalized(), r_in.getTime());
    attenuation = albedo;
    return scattered.getDir().dot(rec.normal) > 0;
}

std::string Dielectric::get_name() const {
    return "Dielectric";
}

bool Dielectric::scatter(const Ray &r_in, const Hit_Record &rec, vec3_value &attenuation, Ray &scattered) const {
    attenuation = vec3_value(1.0, 1.0, 1.0);
    auto r_in_normal = r_in.getDir().normalized();
    double cos_theta = fmin(-r_in_normal.dot(rec.normal), 1.0);
    auto sin_theta = sqrt(1.0 - pow(cos_theta, 2));
    vec3_direction refrection_direction;
    auto ref_ratio = rec.front_face ? (1.0 / ref_idx) : ref_idx;

    auto seed = static_cast<uint32_t>(rec.position.norm() * rec.time *1000000);

    if (ref_ratio * sin_theta > 1 || reflectance(cos_theta, ref_idx) > random_pcg(seed)) {
        refrection_direction = reflect(r_in_normal, rec.normal);
    } else {
        if (rec.front_face) {
            refrection_direction = refrect(r_in_normal, rec.normal, 1.0, ref_idx);
        } else {
            refrection_direction = refrect(r_in_normal, rec.normal, ref_idx, 1.0);
        }
    }
    scattered = Ray(rec.position, refrection_direction, r_in.getTime());
    return true;
}

double Dielectric::reflectance(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = pow(r0, 2.0);
    return r0 + (1 - r0) * pow((1 - cosine), 5.0);
}
