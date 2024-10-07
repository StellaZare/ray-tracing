#include "DirectionalLight.h"
#include <limits>

/**
 * Compute the direction to a direction-light 
 * 
 * @param q     query point in 3D space
 * @param d     direction vector from query to direction-light
 * @param mat_t parametric distance from q along d to reach light
 */
void DirectionalLight::direction(
    const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
    // (from query to light) = -(from light to query) 
    d = -(this->d);
    // light source is always infinite distance away
    max_t = std::numeric_limits<double>
}

