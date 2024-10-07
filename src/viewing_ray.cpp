#include "viewing_ray.h"

/**
 * Construct a viewing ray given a camera and subscripts to a pixel
 * 
 * @param camera    Perspective camera object
 * @param i         Pixel row index
 * @param j         Pixel column index
 * @param width     Number of pixels width of image
 * @param height    Number of pixels height of image
 * @param ray       Viewing ray starting at camera shooting through pixel. 
 *                  When t=1, then ray.origin + t*ray.direction 
 *                  should land exactly on the center of the pixel (i,j)
 */
void viewing_ray(
    const Camera & camera,
    const int i,
    const int j,
    const int width,
    const int height,
    Ray & ray)
{
    // Compute aspect ratio
    double aspect_ratio = camera.width / camera.height;

    // Compute the screen coordinates
    double px = (2 * (j + 0.5) / width - 1) * aspect_ratio;
    double py = 1 - 2 * (i + 0.5) / height;

    // Ray direction is the vector from the camera's eye to the pixel
    // Do not normalize the direction vector so the ray.origin + ray.direction lands on the pixel
    ray.direction = (-camera.d * camera.w) + (px * camera.u) + (py * camera.v);

    // Ray origin is the camera's eye
    ray.origin = camera.e;
}