#include "Sphere.h"
#include "Ray.h"

/**
 * Determine if and where a ray intersects with the sphere
 * 
 * @param ray           Ray to intersect with
 * @param min_t         Minimum parameteric distance to consider
 * @param t             A place to put the first intersection at ray.origin + t * ray.direction
 * @param n             A place to put the surface normal at the point of intersection
 * 
 * @returns             True if an intersection is found
 */
bool Sphere::intersect(
    const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    
    /**
     * For a ray r(t) = o + td, the intersection with a sphere of radius r and center c is given by
     * (d dot d) t^2 + 2(d dot (o - c)) t + ((o - c) dot (o - c) - r^2) = 0
     */

    auto a = ray.direction.dot(ray.direction);
    auto b = 2 * ray.direction.dot(ray.origin - center);
    auto c = (ray.origin - center).dot(ray.origin - center) - radius * radius;

    /**
     * The discriminant of the quadratic equation is b^2 - 4ac
     * It determines the number of intersection points
     */
    auto discriminant = (b * b) - (4 * a * c);

    if (discriminant > 0)
    {
        // Get the two intersection points
        auto t1 = (-b - sqrt(discriminant)) / (2 * a);
        auto t2 = (-b + sqrt(discriminant)) / (2 * a);
        
        if (t1 >= min_t) t = t1;
        else if (t2 >= min_t) t = t2;
        else return false;

        // Get surface normal
        n = (ray.origin + t * ray.direction - center).normalized();
        return true;
    }
    else if (discriminant == 0)
    {   
        // Get the single intersection point
        t = -b / (2 * a);
        // Get surface normal
        n = (ray.origin + t * ray.direction - center).normalized();
        return true;
    }

    // No intersection
    return false;
}