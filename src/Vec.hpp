
#pragma once
#include <cmath>
#include <iostream>

#define VECTOR_VECTOR_OPERATION(operation)                                       \
    template <size_t nRows, typename T>                                          \
    Vec<nRows, T> operator operation(Vec<nRows, T> tVec1, Vec<nRows, T> tVec2) { \
        Vec<nRows, T> result{};                                                  \
                                                                                 \
        for (size_t i = 0; i < nRows; i++) {                                     \
            (&result.x)[i] = (&tVec1.x)[i] operation(&tVec2.x)[i];               \
        }                                                                        \
                                                                                 \
        return result;                                                           \
    }

#define VECTOR_SCALAR_OPERATION(operation)                             \
    template <size_t nRows, typename T>                                \
    Vec<nRows, T> operator operation(Vec<nRows, T> tVec, T tDivisor) { \
        for (size_t i = 0; i < nRows; i++) {                           \
            (&tVec.x)[i] operation## = tDivisor;                       \
        }                                                              \
        return tVec;                                                   \
    }

namespace math {

    template <size_t nRows, typename T, std::enable_if_t<(nRows > 0 && nRows < 5), int> = 0>
    struct Vec {};

    template <typename T>
    struct Vec<1, T> {
        union {
            T x;
            T r;
        };
        T& operator[](size_t tIndex) {
            return (&x)[tIndex];
        }
    };

    template <typename T>
    struct Vec<2, T> {
        union {
            T x;
            T r;
        };
        union {
            T y;
            T b;
        };
        T& operator[](size_t tIndex) {
            return (&x)[tIndex];
        }
    };

    template <typename T>
    struct Vec<3, T> {
        union {
            T x;
            T r;
        };
        union {
            T y;
            T b;
        };
        union {
            T z;
            T g;
        };
        T& operator[](size_t tIndex) {
            return (&x)[tIndex];
        }
    };

    template <typename T>
    struct Vec<4, T> {
        union {
            T x;
            T r;
        };
        union {
            T y;
            T b;
        };
        union {
            T z;
            T g;
        };
        union {
            T w;
            T a;
        };

        T& operator[](size_t tIndex) {
            return (&x)[tIndex];
        }
    };

    VECTOR_VECTOR_OPERATION(*);
    VECTOR_VECTOR_OPERATION(/);
    VECTOR_VECTOR_OPERATION(-);
    VECTOR_VECTOR_OPERATION(+);

    VECTOR_SCALAR_OPERATION(*);
    VECTOR_SCALAR_OPERATION(/);
    VECTOR_SCALAR_OPERATION(-);
    VECTOR_SCALAR_OPERATION(+);

    template <size_t nRows, typename T>
    Vec<nRows, T>& operator+=(Vec<nRows, T>& tVec1, Vec<nRows, T> tVec2) {
        for (size_t i = 0; i < nRows; i++) {
            (&tVec1.x)[i] += (&tVec2.x)[i];
        }
        return tVec1;
    }

    template <size_t nRows, typename T>
    std::ostream& operator<<(std::ostream& tOutput, Vec<nRows, T> tVec) {
        tOutput << "Vec<" << nRows << ">{";

        for (size_t i = 0; i < nRows; i++) {
            tOutput << (&tVec.x)[i];

            if (i != nRows - 1) {
                tOutput << ", ";
            }
        }
        tOutput << "}\n";
        return tOutput;
    }

    template <size_t nRows, typename T>
    T dot(Vec<nRows, T> tVec1, Vec<nRows, T> tVec2) {
        T result;

        for (size_t i = 0; i < nRows; i++) {
            result += ((&tVec1.x)[i] * (&tVec2.x)[i]);
        }
        return result;
    }

    template <size_t nRows, typename T>
    T length(Vec<nRows, T> tVec) {
        T result;

        for (size_t i = 0; i < nRows; i++) {
            result += ((&tVec.x)[i] * (&tVec.x)[i]);
        }
        return sqrt(result);
    }

    template <size_t nRows, typename T>
    Vec<nRows, T> normalize(Vec<nRows, T> tVec) {
        return tVec / length(tVec);
    }

    template <size_t nRows, typename T, std::enable_if_t<(nRows == 3), int> = 0>
    Vec<nRows, T> cross(Vec<nRows, T> tVec1, Vec<nRows, T> tVec2) {
        
    }

    using Vec4 = Vec<4, float>;
    using Vec3 = Vec<3, float>;
    using Vec2 = Vec<2, float>;
    using Vec1 = Vec<1, float>;
}  // namespace math
