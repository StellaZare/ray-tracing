#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
    const Ray & ray,
    const int & hit_id, 
    const double & t,
    const Eigen::Vector3d & n,
    const std::vector< std::shared_ptr<Object> > & objects,
    const std::vector<std::shared_ptr<Light> > & lights)
{   
    Eigen::Vector3d color (0, 0, 0);
    Eigen::Vector3d point_hit = ray.origin + t * ray.direction;

    // Material properties
    Eigen::Vector3d ka = objects.at(hit_id)->material->ka;
    Eigen::Vector3d kd = objects.at(hit_id)->material->kd;
    Eigen::Vector3d ks = objects.at(hit_id)->material->ks;
    double phong_exp  = objects.at(hit_id)->material->phong_exponent;

    // Ambient component
    color += ka * 0.1;

    // Compute the color contribution for each light source
    for (int idx = 0; idx < lights.size(); idx++) {

        // Obtain "light" ray from hit-point to light source
        Eigen::Vector3d light_dir;
        Eigen::Vector3d light_intensity = lights.at(idx)->I;
        double light_t;
        lights.at(idx)->direction(point_hit, light_dir, light_t);
        light_dir.normalize();

        // Construct shadow ray
        Ray shadow_ray;
        shadow_ray.origin = point_hit + 0.0001 * n;
        shadow_ray.direction = light_dir;

        // Buffers for hit object data
        int shadow_hit_id; 
        double shadow_t; 
        Eigen::Vector3d shadow_n;

        // Check if the light source is visible: no hit or hit is further than the light source
        bool shadow_intersect_obj = first_hit(shadow_ray, 0.0001, objects, shadow_hit_id, shadow_t, shadow_n);
        if ( !shadow_intersect_obj || shadow_t > light_t ) {

            // Diffuse component
            Eigen::Vector3d I_diff = kd.cwiseProduct(light_intensity) * std::max(0.0, n.dot(light_dir));

            // Specular component
            Eigen::Vector3d h = (light_dir + (-ray.direction)).normalized();
            auto cos_nh = std::max(0.0, n.dot(h));
            Eigen::Vector3d I_spec = (ks.cwiseProduct(light_intensity) * pow(cos_nh, phong_exp));

            // Add color contribution
            color += (I_diff + I_spec);
        }
    }
    
    return color;   
}