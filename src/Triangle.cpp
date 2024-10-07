#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Dense>

/**
 * Determine if and where the ray intersects with the triangle
 * 
 * @param ray       The ray to intersect
 * @param min_t     Minimum parametric distance to consider
 * @param t         A place to store the intersection point along the ray
 * @param n         The surface normal at the point of intersection
 */
bool Triangle::intersect(
    const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    // Get the vertices of the triangle
    Eigen::Vector3d a = std::get<0>(corners);
    Eigen::Vector3d b = std::get<1>(corners);
    Eigen::Vector3d c = std::get<2>(corners);

    // Compute the edges of the triangle
    Eigen::Vector3d ab = b - a;
    Eigen::Vector3d ac = c - a;

    // Compute the normal of the triangle
    Eigen::Vector3d tri_normal = ab.cross(ac).normalized();

    // Intersect the plane with the ray
    double numerator = (a - ray.origin).dot(tri_normal);
    double denominator = ray.direction.dot(tri_normal);

    // Check if the ray is parallel to the plane
    if (denominator == 0) return false;
    
    double t_plane = numerator / denominator;
    // Check if the intersection is in front of the ray
    if (t_plane < min_t) return false;

    // Compute the intersection point
    Eigen::Vector3d p = ray.origin + t_plane * ray.direction;

    // Compute the vectors from the vertices to the intersection point
    Eigen::Vector3d ap = p - a;
    Eigen::Vector3d bp = p - b;
    Eigen::Vector3d cp = p - c;

    // Compute the areas of the sub-triangles using the cross product
    double area_abc = ab.cross(ac).norm();
    double area_pbc = bp.cross(cp).norm();
    double area_pca = cp.cross(ap).norm();
    double area_pab = ap.cross(bp).norm();

    // Compute the barycentric coordinates
    double alpha = area_pbc / area_abc;
    double beta = area_pca / area_abc;
    double gamma = area_pab / area_abc;

    // Check if the intersection point is inside the triangle
    if ((alpha >= 0) && (beta >= 0) && (gamma >= 0) && (alpha + beta + gamma <= 1 + 1e-6))
    {
        // Store the intersection point and normal
        t = t_plane;
        n = tri_normal;
        return true;
    }
    
    return false;
}