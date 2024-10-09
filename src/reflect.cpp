#include <Eigen/Core>

/**
 * Reflect an incoming ray into an out going ray
 * 
 * @param in  incoming _unit_ ray direction
 * @param n   surface _unit_ normal about which to reflect
 * 
 * @returns outward _unit_ ray direction of the reflected ray
 */
Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
    Eigen::Vector3d reflected_ray = in - 2 * in.dot(n) * n;
    return reflected_ray;
}
