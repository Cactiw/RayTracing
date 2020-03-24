//
// Created by cactiw on 16.03.2020.
//
#ifndef VECTOR_3F_H
#define VECTOR_3F_H

#include <cassert>
#include <cstddef>
#include <cmath>

template <size_t DIM, typename T> struct vec {
    vec() { for (size_t i=DIM; i--; data_[i] = T()); }
    T& operator[](const size_t i)       { assert(i<DIM); return data_[i]; }
    const T& operator[](const size_t i) const { assert(i<DIM); return data_[i]; }
private:
    T data_[DIM];
};

template <typename T> struct vec<3,T> {
    vec() : x(T()), y(T()), z(T()) {}
    vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
    T& operator[](const size_t i)       { assert(i<3); return i<=0 ? x : (1==i ? y : z); }
    const T& operator[](const size_t i) const { assert(i<3); return i<=0 ? x : (1==i ? y : z); }

    vec<3, T> operator + (const vec<3, T> other) const {
        return vec<3, T>(this->x + other.x, this->y + other.y, this->z + other.z);
    }
    vec<3, T> operator - (const vec<3, T> other) const {
        return vec<3, T>(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    float dotProduct(const vec<3, T> other) const {
//        auto new_this = this->normalize();
//        auto new_other = other.normalize();
        return this->x * other.x + this->y * other.y + this-> z * other.z;
    }
    float norm() { return std::sqrt(x*x+y*y+z*z); }
    vec<3,T> & normalize() {
        auto normSaved = norm();
        this->x = x / normSaved;
        this->y = y / normSaved;
        this->z = z / normSaved;
        return *this;
    }
    T x,y,z;
};

typedef vec<3, float  > Vec3f;

#endif
