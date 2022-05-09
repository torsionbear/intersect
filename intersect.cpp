#include "intersect.h"

std::vector<Vec4> intersect(Ray const& ray, Sphere const& sphere) {
    Vec4 ray2Sphere = sphere.center - ray.position;
    float dotProduct = dot(ray2Sphere, ray.direction);
    bool inside = ray2Sphere.length() <= sphere.diameter;
    if (dotProduct < 0 && !inside)  return std::vector<Vec4>{};

    Vec4 ray2NearPoint = ray.direction * dotProduct;
    Vec4 sphere2nearPoint = ray2NearPoint - ray2Sphere;
    float distance = sphere2nearPoint.length();
    if (distance > sphere.diameter) return std::vector<Vec4>{};

    float halfChord = sqrt(sphere.diameter * sphere.diameter - distance * distance);
    if (halfChord <= EPSILON) return std::vector<Vec4> { ray2NearPoint + ray.position};
    if (inside) return std::vector<Vec4> { ray2NearPoint + ray.direction * halfChord + ray.position };
    return std::vector<Vec4> { 
        ray2NearPoint - ray.direction * halfChord + ray.position,
        ray2NearPoint + ray.direction * halfChord + ray.position,
    };
}
