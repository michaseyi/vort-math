#pragma once
#include "Vec.hpp"

#define MATRIX_SCALAR_OPERATION(operation)                                               \
    template <size_t nRows, size_t nColumns, typename T>                                 \
    Mat<nRows, nColumns, T> operator operation(Mat<nRows, nColumns, T> tMat, T tValue) { \
        for (size_t i = 0; i < nRows; i++) {                                             \
            for (size_t j = 0; j < nColumns; j++) {                                      \
                tMat[i][j] operation## = tValue;                                         \
            }                                                                            \
        }                                                                                \
        return tMat;                                                                     \
    }

namespace math {

    template <size_t nRows, size_t nColumns, typename T, std::enable_if_t<(nRows > 0 && nColumns > 0), int> = 0>
    struct Mat {
        Vec<nRows, T>& operator[](size_t tIndex) {
            return data[tIndex];
        }

        Vec<nRows, T> data[nColumns];
    };

    template <size_t nRows, size_t nColumns, typename T>
    Mat<nColumns, nRows, T> transpose(Mat<nRows, nColumns, T> tMat) {
        Mat<nColumns, nRows, T> result;

        for (size_t i = 0; i < nRows; i++) {
            for (size_t j = 0; j < nColumns; j++) {
                result[i][j] = tMat[j][i];
            }
        }

        return result;
    }

    template <size_t nRows1, size_t nColumns1, size_t nRows2, size_t nColumns2, typename T,
              std::enable_if_t<(nColumns1 == nRows2), int> = 0>
    Mat<nRows1, nColumns2, T> operator*(Mat<nRows1, nColumns1, T> tMat1, Mat<nRows2, nColumns2, T> tMat2) {
        Mat<nRows1, nColumns2, T> result;

        auto transposedTMat1 = transpose(tMat1);
        for (size_t i = 0; i < nRows1; i++) {
            for (size_t j = 0; j < nColumns2; j++) {
                result[j][i] = dot(transposedTMat1[i], tMat2[j]);
            }
        }
        return result;
    }

    template <size_t nRows1, size_t nColumns1, size_t nRows2, typename T,
              std::enable_if_t<(nColumns1 == nRows2), int> = 0>
    Vec<nRows1, T> operator*(Mat<nRows1, nColumns1, T> tMat, Vec<nRows2, T> tVec) {
        Vec<nRows1, T> result;

        auto transposedTMat = transpose(tMat);
        for (size_t i = 0; i < nRows1; i++) {
            result[i] = dot(transposedTMat[i], tVec);
        }
        return result;
    }

    template <size_t nRows1, size_t nRows2, size_t nColumns2, typename T, std::enable_if_t<(1 == nRows2), int> = 0>
    Mat<nRows1, nColumns2, T> operator*(Vec<nRows1, T> tVec, Mat<nRows2, nColumns2, T> tMat) {
        return Mat<nRows1, 1, T>{tVec} * tMat;
    }

    template <size_t nRows, size_t nColumns, typename T, std::enable_if_t<(nRows == nColumns), int> i = 0>
    Mat<nRows, nColumns, T> inverse(Mat<nRows, nColumns, T> tMat) {
    }

    template <size_t nRows, size_t nColumns, typename T>
    T determinant(Mat<nRows, nColumns, T> tMat) {
    }

    template <size_t nRows, typename T>
    Mat<nRows + 1, nRows + 1, T> translation(Vec<nRows, T> tPosition) {
        Mat<nRows + 1, nRows + 1, T> result{};

        return result;
    }

    template <size_t nRows, typename T>
    Mat<nRows + 1, nRows + 1, T> scale(Vec<nRows, T> tVec) {
        Mat<nRows + 1, nRows + 1, T> result{};

        return result;
    }

    template <size_t nRows, typename T>
    Mat<nRows + 1, nRows + 1, T> rotation(float tAngle, Vec<nRows, T> tAxis) {
        Mat<nRows + 1, nRows + 1, T> result{};

        return result;
    }

    MATRIX_SCALAR_OPERATION(*);
    MATRIX_SCALAR_OPERATION(/);
    MATRIX_SCALAR_OPERATION(-);
    MATRIX_SCALAR_OPERATION(+);

    using Mat4 = Mat<4, 4, float>;
    using Mat3 = Mat<3, 3, float>;
    using Mat2 = Mat<2, 2, float>;
}  // namespace math