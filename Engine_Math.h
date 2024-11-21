#ifndef __ENGINE_MATH_H__
#define __ENGINE_MATH_H__

#include "Engine_Define.h"

#include <math.h>

namespace Engine {
    /// @brief The Interpolation Function, use to define the type of the interpolation function.
    enum class InterpolationFunction {
        Linear = 0,
        Smoothstep = 1,
        Smootherstep = 2,
        EaseIn = 3,
        EaseOut = 4
    };

    /// @brief The Interpolation class, provide static basic interpolation function.
    class Interpolation final {
    public:
        /// @brief Clamp the value between start and end.
        /// @param start The start value.
        /// @param end The end value.
        /// @param value The value to clamp.
        /// @return The result of the intepolation.
        static double Clamp(double start, double end, double value) { return ENGINE_CLAMP(start, end, value); }
        /// @brief Clamp the value between 0 and 1.
        /// @param value The value to clamp.
        /// @return The result of the intepolation.
        static double Clamp01(double value) { return ENGINE_FAST_CLAMP(0, 1, value); }

        /// @brief Linear interpolation between start and end.
        /// @param start The start value of the interpolation (when t = 0).
        /// @param end The end value of the interpolation (when t = 1).
        /// @param t The interpolation value (will clamp to be between 0 and 1).
        /// @return The result of the interpolation.
        static double Linear(double start, double end, double t) { return start + (end - start) * Clamp01(t); }
        /// @brief Inverse linear interpolation between start and end.
        /// @param start The start value of the interpolation (when t = 0).
        /// @param end The end value of the interpolation (when t = 1).
        /// @param value The value to calculate.
        /// @return The result of the interpolation (will clamp between 0 and 1).
        static double InverseLinear(double start, double end, double value) { return Clamp01((value - start) / (end - start)); }

        /// @brief Smoothly interpolation between start and end.
        /// @param start The start value of the interpolation (when t = 0).
        /// @param end The end value of the interpolation (when t = 1).
        /// @param t The interpolation value (will clamp to be between 0 and 1).
        /// @return The result of the interpolation.
        static double Smoothstep(double start, double end, double t) {
            double x = Clamp01(t);
            return Linear(start, end, x * x * (3.0 - 2.0 * x));
        }
        /// @brief Smoothly interpolation between start and end (smoother than Smoothstep).
        /// @param start The start value of the interpolation (when t = 0).
        /// @param end The end value of the interpolation (when t = 1).
        /// @param t The interpolation value (will clamp to be between 0 and 1).
        /// @return The result of the interpolation.
        static double Smootherstep(double start, double end, double t) {
            double x = Clamp01(t);
            return Linear(start, end, x * x * x * (x * (6.0 * x - 15.0) + 10.0));
        }

        /// @brief Interpolation between start and end with cubic ease-in function.
        /// @param start The start value of the interpolation (when t = 0).
        /// @param end The end value of the interpolation (when t = 1).
        /// @param t The interpolation value (will clamp to be between 0 and 1).
        /// @return The result of the interpolation.
        static double EaseIn(double start, double end, double t) {
            double x = Clamp01(t);
            return Linear(start, end, x*x*x);
        }
        /// @brief Interpolation between start and end with cubic ease-out function.
        /// @param start The start value of the interpolation (when t = 0).
        /// @param end The end value of the interpolation (when t = 1).
        /// @param t The interpolation value (will clamp to be between 0 and 1).
        /// @return The result of the interpolation.
        static double EaseOut(double start, double end, double t) {
            double x = 1 - Clamp01(t);
            return Linear(start, end, 1 - (x * x * x));
        }

        /// @brief Interpolation between start and end with the given function type.
        /// @param function The function type to interpolate. Will use Linear on invalid.
        /// @param start The start value of the interpolation (when t = 0).
        /// @param end The end value of the interpolation (when t = 1).
        /// @param t The interpolation value (will clamp to be between 0 and 1).
        /// @return The result of the interpolation.
        static double FromInterpolationFunction(InterpolationFunction function, double start, double end, double t) {
            switch (function)
            {
            case Engine::InterpolationFunction::Smoothstep:
                return Smoothstep(start, end, t);
            case Engine::InterpolationFunction::Smootherstep:
                return Smootherstep(start, end, t);
            case Engine::InterpolationFunction::EaseIn:
                return EaseIn(start, end, t);
            case Engine::InterpolationFunction::EaseOut:
                return Smoothstep(start, end, t);
            default:
                return Linear(start, end, t);
            }
        }
    };
}

#endif // __ENGINE_MATH_H__