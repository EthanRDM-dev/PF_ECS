/**
 * @file Vec2.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief 2-dimensional vector, and its operators overload
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <cmath>

//Shortcut for directions vector
#define LEFT    (Vec2) {-1,0}
#define RIGHT   (Vec2) {1,0}
#define UP      (Vec2) {0,-1}
#define DOWN    (Vec2) {0,1}
//Shortcut for zeros and ones vector
#define ZEROS   (Vec2) {0,0}
#define ONES    (Vec2) {1,1}

/**
 * @brief 2-dimensional vector
 * 
 */
struct Vec2 {
    Vec2() : x{0.0f}, y{0.0f} {}
    Vec2(float _x, float _y) : x{_x}, y{_y} {}

    float x;
    float y;

    /**
     * @brief vector length squared
     * 
     * @return float 
     */
    float lengthSquared() {
        return (x * x) + (y * y);
    }

    /**
     * @brief vector length (magnitude)
     * 
     * @return float 
     */
    float mag() {
        return sqrtf(lengthSquared());
    }

    /**
     * @brief return a normalized vector (unit vector of the actual vector)
     * 
     * @return Vec2 normalized vector
     */
    Vec2 normalized() {
        Vec2 unitVec{x/mag(), y/mag()};
        return unitVec;
    }

    /**
     * @brief normalize itself
     * 
     * @return Vec2& reference to itself
     */
    Vec2& normalize() {
        x /= mag();
        y /= mag();

        return *this;
    }

    /**
     * @brief vector dot product
     * 
     * @param v vector multiplying this vector
     * @return float dot product result
     */
    float dot(Vec2& v) {
        return (x * v.x) + (y * v.y);
    }

    // float angle(Vec2& v) {
    //     float dot = (x * v.x) + (y * v.y);
    //     float det = (x * v.x) - (y * v.y);

    //     return atan2(det, dot);
    // }

    /**
     * @brief += operator overload
     * 
     * @param v 
     * @return Vec2& initial vector
     */
    Vec2& operator+=(Vec2 const& v) {
        x += v.x;
        y += v.y;

        return *this;
    }
    
    /**
     * @brief -= operator overload
     * 
     * @param v 
     * @return Vec2& initial vector
     */
    Vec2& operator-=(Vec2 const& v) {
        x -= v.x;
        y -= v.y;

        return *this;
    }
    
    /**
     * @brief *= operator overload with another vector
     * 
     * @param v a vector
     * @return Vec2& initial vector
     */
    Vec2& operator*=(Vec2 const& v) {
        x *= v.x;
        y *= v.y;

        return *this;
    }
    
    /**
     * @brief *= operator overload with a scalar
     * 
     * @param v a scalar
     * @return Vec2& initial vector
     */
    Vec2& operator*=(float const& v) {
        x *= v;
        y *= v;

        return *this;
    }

    /**
     * @brief return x if i is even, y if i is odd
     * 
     * @param i
     * @return float the attribute we want to get
     */
    float get(int i) {
        if(i % 2 == 0) return x;
        return y;
    }

    /**
     * @brief set x to r if i is even, set y to r if i is odd
     * 
     * @param i 
     * @param r 
     */
    void set(int i, float r) {
        if(i % 2 == 0) {
            x = r;
        } else {
            y = r;
        }
    }

    /**
     * @brief << operator overload
     * 
     * @param os out stream
     * @param v vector we want to print
     * @return std::ostream& the out stream
     */
    friend std::ostream& operator<<(std::ostream& os, Vec2 const& v) {
        os << v.x << "," << v.y;
        return os;
    }
};

/**
 * @brief + operator overload
 * 
 * @param v1 vector 1
 * @param v2 vector 2
 * @return Vec2& resulting vector
 */
Vec2 operator+(Vec2 const& v1, Vec2 const& v2) {
    Vec2 v(v1.x + v2.x, v1.y + v2.y);
    return v;
}

/**
 * @brief - operator overload
 * 
 * @param v1 vector 1
 * @param v2 vector 2
 * @return Vec2& resulting vector
 */
Vec2 operator-(Vec2 const& v1, Vec2 const& v2) {
    Vec2 v(v1.x - v2.x, v1.y - v2.y);
    return v;
}

/**
 * @brief * operator overload with a vector
 * 
 * @param v1 vector 1
 * @param v2 vector 2
 * @return Vec2& resulting vector
 */
Vec2 operator*(Vec2 const& v1, Vec2 const& v2) {
    Vec2 v(v1.x * v2.x, v1.y * v2.y);
    return v;
}

/**
 * @brief * operator overload with a scalar
 * 
 * @param v1 vector
 * @param v2 scalar
 * @return Vec2& resulting vector
 */
Vec2 operator*(Vec2 const& v1, float const& v2) {
    Vec2 v(v1.x * v2, v1.y * v2);
    return v;
}