#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

/**
 * Determine if and where the ray intersects with the triangle soup
 * 
 * @param ray       The ray to intersect
 * @param min_t     Minimum parametric distance to consider
 * @param t         A place to store the intersection point along the ray
 * @param n         The surace normal at the point of intersection
 * 
 * @returns         True if an intersection is found
 */
bool TriangleSoup::intersect(
    const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    // Buffers for first_hit to write to
    int id_buff {};
    double t_buff {};
    Eigen::Vector3d n_buff {};

    // Find the first hit object
    if (first_hit(ray, min_t, this->triangles, id_buff, t_buff, n_buff))
    {
        // Store the intersection point and normal
        t = t_buff;
        n = n_buff;
        return true;
    }

    // Ray does not intersect with any object
    return false;
}