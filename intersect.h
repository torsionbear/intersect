#pragma once

#include <iostream>
#include <limits>
#include <cmath>
#include <vector>

#define EPSILON 1e-6f
struct Vec4 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 1.0f;
    Vec4() = default;
    Vec4(float v) : x(v), y(v), z(v), w(v) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(Vec4 const& other) = default;
    float length() const {
        return std::sqrt(x*x + y*y + z*z + w*w);
    }
    Vec4 normalize() const {
        float l = this->length();
        return Vec4{x / l, y / l, z / l, w / l};
    }
    Vec4 operator+(Vec4 const& other) const {
        return Vec4{ x + other.x, y + other.y, z + other.z, w + other.w };
    }
    Vec4 operator-(Vec4 const& other) const {
        return Vec4{ x - other.x, y - other.y, z - other.z, w - other.w };
    }
    Vec4 operator*(float s) const {
        return Vec4{ x * s, y * s, z * s, w * s};
    }
    bool operator==(Vec4 const& other) const {
        return (*this - other).length() < EPSILON;
    }
    friend std::ostream& operator<<(std::ostream& os, Vec4 const& v) {
        return os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w <<"]";
    }
    friend float dot(Vec4 const& lhs, Vec4 const& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }
};

struct Ray {
    Vec4 position;
    Vec4 direction;
    Ray(Vec4 p, Vec4 d) : position(p), direction(d) {
        direction = direction.normalize();
    }
};

struct Sphere {
    Vec4 center;
    float diameter;
};

std::vector<Vec4> intersect(Ray const& ray, Sphere const& sphere);
