#pragma once
#include <map>

namespace math {

    template <typename T>
    struct Spline {
        T operator[](float tIndex) {
            return mKnots[tIndex];
        }

        void addKnot(float tTime, T tVal) {
            mKnots[tTime] = tVal;
        }

        auto &knots() {
            return mKnots;
        }

    private:
        std::map<float, T> mKnots;
    };

}  // namespace math