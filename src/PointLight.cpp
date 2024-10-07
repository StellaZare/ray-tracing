#include "PointLight.h"

/**
 * Compute the direction to a point light source
 * 
 * @param q     query point in 3D space
 * @param d     direction vector from q to the light
 * @param max_t parametric distance from q to search
 */
void PointLight::direction(
    const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
    // Direction from query to point-light
    d = (p - q);
    // Distance from query to point-light
    max_t = d.norm();
    // Normalize direction vector
    d.normalize();
}
