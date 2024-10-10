#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

/**
 * Shoot a ray into a lit scene and collect color information
 * 
 * @param ray       the ray to search
 * @param min_t     the min distance to consider
 * @param objects   list of all objects in the scene
 * @param lights    list of all lights in the scene
 * @param num_recursive_calls   the nesting level of the current call to raycolor
 * @param rgb       collected color
 * 
 * @returns true if a hit was found
 */
bool raycolor(
    const Ray & ray, 
    const double min_t,
    const std::vector< std::shared_ptr<Object> > & objects,
    const std::vector< std::shared_ptr<Light> > & lights,
    const int num_recursive_calls,
    Eigen::Vector3d & rgb)
{

    rgb = Eigen::Vector3d (0, 0, 0);

    // Buffers for hit object data
    int hit_id;
    double hit_t;
    Eigen::Vector3d hit_n (0, 0, 0);

    // No objects hit return false
    if (!first_hit(ray, min_t, objects,hit_id, hit_t, hit_n)) {
        return false;
    }

    // Normalized ray direction and normal at hit point
    hit_n.normalize();
    auto in_coming = ray.direction.normalized();

    // Get the Blinn-Phong shading contribution
    rgb += blinn_phong_shading(ray, hit_id, hit_t, hit_n, objects, lights);

    // Recursive call to get the reflection
    if (num_recursive_calls < 5) {
        // Compute the reflected ray
        Ray reflected_ray;
        reflected_ray.origin = ray.origin + (hit_t * ray.direction + 0.0001 * hit_n);
        reflected_ray.direction = reflect(in_coming, hit_n);
        
        // Get the color of the reflected ray
        Eigen::Vector3d reflected_rgb;
        raycolor(reflected_ray, 0.0001, objects, lights, num_recursive_calls + 1, reflected_rgb);

        // Add the reflected color to the current color
        auto km = objects.at(hit_id)->material->km;
        rgb += km.cwiseProduct(reflected_rgb);
    }

    return true;
}
