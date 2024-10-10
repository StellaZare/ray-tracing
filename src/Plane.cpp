#include "Plane.h"
#include "Ray.h"

/**
 * Determine if and where a ray intersects with the plane
 * 
 * @param ray           Ray to intersect with
 * @param min_t         Minimum parameteric distance to consider
 * @param t             A place to put the point of intersection
 * @param n             A place to put the surface normal at the point of intersection
 * 
 * @returns             True if an intersection is found
 */
bool Plane::intersect(
    const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    /**
     * For a ray r(t) = o + td and point on the plane p and normal n
     * Intersection is given by (p - o) dot n / (d dot n)
     */

    auto numerator = (point - ray.origin).dot(normal);
    auto denominator = ray.direction.dot(normal);

    if (denominator == 0)
    {
        // Ray is parallel to the plane
        return false;
    }

    t = numerator / denominator;
    if (t >= min_t)
    {
        // The intersection is in front of the ray
        n = normal;
        return true;
    }

    // The intersection is behind the ray
    return false;
}
