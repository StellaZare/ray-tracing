#include "first_hit.h"
/**
 * Find the first hit object given a ray and a collection of scene objects
 * 
 * @param ray     Ray along which to search
 * @param min_t   Minimum t value to consider (>= the distance of the image plane to the camera)
 * @param objects List of objects in the scene
 * @param hit_id  A place to put the index into objects of object with first hit
 * @param t       A place to put the parametric distance along ray to the hit location
 *                i.e. ray.origin + t*ray.direction is the hit location
 * @param n       A place to put the surface normal at hit location
 */
bool first_hit(
    const Ray & ray, 
    const double min_t,
    const std::vector< std::shared_ptr<Object> > & objects,
    int & hit_id, 
    double & t,
    Eigen::Vector3d & n)
{
    // Initialize t to infinite distance
    t = std::numeric_limits<double>::infinity();

    // Loop through all objects in the scene
    for (int idx = 0; idx < objects.size(); idx++)
    {
        // Variables to store current object data
        auto obj = objects.at(idx);
        double obj_t {};
        Eigen::Vector3d obj_n {};

        // Check for intersection with ray
        obj->intersect(ray, min_t, obj_t, obj_n);

        // Replace found intersection is closer than prev AND larger than min_t
        if (obj_t < t && obj_t >= min_t)
        {
            hit_id = idx;
            t = obj_t;
            n = obj_n;
        }
    }

    // Return true if a hit was found
    return (t < std::numeric_limits<double>::infinity());
}