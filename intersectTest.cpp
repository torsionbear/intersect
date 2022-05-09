#include "gtest/gtest.h"

#include "intersect.h"

using namespace ::testing;

class intersectTest : public Test {
};

TEST_F(intersectTest, inside) {
    auto ray = Ray{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), sqrt(3.0f) };
    auto expected = std::vector<Vec4>{Vec4(1.0f, 1.0f, 1.0f, 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, inside_chord) {
    auto ray = Ray{ Vec4(1.0f, 0.0f, 0.0f, 1.0f), Vec4(0.0f, 0.0f, 1.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 2.0f };
    auto expected = std::vector<Vec4>{Vec4(1.0f, 0.0f, sqrt(3.0f), 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, outside) {
    auto ray = Ray{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f };
    float near = sqrt(powf(sqrt(3.0f) - 1.0f, 2) / 3);
    float far = sqrt(powf(sqrt(3.0f) + 1.0f, 2) / 3);
    auto expected = std::vector<Vec4>{Vec4(near, near, near, 1.0f), Vec4(far, far, far, 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, outside_chord) {
    auto ray = Ray{ Vec4(1.0f, 0.0f, 2.0f, 1.0f), Vec4(0.0f, 0.0f, -1.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 2.0f };
    auto expected = std::vector<Vec4>{Vec4(1.0f, 0.0f, sqrt(3.0f), 1.0f), Vec4(1.0f, 0.0f, -sqrt(3.0f), 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, outside_tangent) {
    auto ray = Ray{ Vec4(2.0f, 0.0f, 2.0f, 1.0f), Vec4(0.0f, 0.0f, -1.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 2.0f };
    auto expected = std::vector<Vec4>{Vec4(2.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, outside_no_intersection) {
    auto ray = Ray{ Vec4(2.0f, 0.0f, 2.0f, 1.0f), Vec4(0.1f, 0.0f, -1.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 2.0f };
    auto expected = std::vector<Vec4>{};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, outside_outward) {
    auto ray = Ray{ Vec4(2.0f, 0.0f, 0.0f, 1.0f), Vec4(1.0f, 0.0f, 0.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f };
    auto expected = std::vector<Vec4>{};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, on_inward) {
    auto ray = Ray{ Vec4(0.0f, 0.0f, 1.0f - 1e-9, 1.0f), Vec4(0.0f, 0.0f, -1.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f };
    auto expected = std::vector<Vec4>{Vec4(0.0f, 0.0f, -1.0f, 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, on_outward) {
    auto ray = Ray{ Vec4(0.0f, 1.0f - 1e-9, 0.0f, 1.0f), Vec4(0.0f, 1.0f, 0.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f };
    auto expected = std::vector<Vec4>{Vec4(0.0f, 1.0f, 0.0f, 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, on_tangent) {
    auto ray = Ray{ Vec4(0, 0.0f, 1.0f - 1e-9, 1.0f), Vec4(1.0, 0.0f, 0.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0, 0.0f, 0.0f, 1.0f), 1.0f };
    auto expected = std::vector<Vec4>{Vec4(0.0f, 0.0f, 1.0f, 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, deteriorated_sphere) {
    auto ray = Ray{ Vec4(1.0f, 0.0f, 0.0f, 1.0f), Vec4(-1.0f, 0.0f, 0.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.0f };
    auto expected = std::vector<Vec4>{Vec4(0.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, deteriorated_sphere_no_intersection) {
    auto ray = Ray{ Vec4(1.0f, 0.0f, 0.0f, 1.0f), Vec4(1.0f, 0.0f, 0.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.0f };
    auto expected = std::vector<Vec4>{};
    EXPECT_EQ(intersect(ray, sphere), expected);
}

TEST_F(intersectTest, deteriorated_sphere_on) {
    auto ray = Ray{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), Vec4(1.0f, 0.0f, 0.0f, 0.0f) };
    auto sphere = Sphere{ Vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.0f };
    auto expected = std::vector<Vec4>{Vec4(0.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_EQ(intersect(ray, sphere), expected);
}
