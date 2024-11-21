#ifndef __ENGINE_GAMEOBJECTANIMATION_H__
#define __ENGINE_GAMEOBJECTANIMATION_H__

#include "Engine_Animation.h"

namespace Engine {
    /// @brief The StartEnd Move Animation Script, provide a movement Animation Script for moving from specific start and end point.
    class StartEndMoveAnimationScript : public AnimationScript {
    protected:
        void OnUpdateAnimation(GameObject* Target, double AnimationTime) override {
            Target->Position.X = (int)roundf(Interpolation::FromInterpolationFunction(
                MovementInterpolationFunction, StartPosition.X, EndPosition.X, AnimationTime
            ));
            Target->Position.Y = (int)roundf(Interpolation::FromInterpolationFunction(
                MovementInterpolationFunction, StartPosition.Y, EndPosition.Y, AnimationTime
            ));
        }
    public:
        /// @brief The start position of the movement animation. Default is Point::Zero.
        Point StartPosition = Point::Zero;
        /// @brief The end position of the movement animation. Default is Point::Zero.
        Point EndPosition = Point::Zero;
        /// @brief The interpolation function type use for the movement animation. Default to linear.
        InterpolationFunction MovementInterpolationFunction = InterpolationFunction::Linear;
    };

    /// @brief The Directional Move Animation Script, provide a movement Animation Script for moving with specific
    /// direction and amount.
    class DirectionalMoveAnimationScript : public AnimationScript {
    private:
        Point __start_position;
    protected:
        void OnStartAnimation(GameObject* Target) override { __start_position = Target->Position; }
        void OnUpdateAnimation(GameObject* Target, double AnimationTime) override {
            int x_end = __start_position.X + Direction.X, y_end = __start_position.Y + Direction.Y;
            Target->Position.X = (int)roundf(Interpolation::FromInterpolationFunction(
                MovementInterpolationFunction, 0, Direction.X, AnimationTime
            ) + __start_position.X);
            Target->Position.Y = (int)roundf(Interpolation::FromInterpolationFunction(
                MovementInterpolationFunction, 0, Direction.Y, AnimationTime
            ) + __start_position.Y);
        }
    public:
        /// @brief The direction (also distance for each dimension) of the movement animation. Default is Point::Zero.
        Point Direction = Point::Zero;
        /// @brief The interpolation function type use for the movement animation. Default to linear.
        InterpolationFunction MovementInterpolationFunction = InterpolationFunction::Linear;
    };

    /// @brief The Move To Animation Script, provide a movement Animation Script for moving to specific position.
    class MoveToAnimationScript : public AnimationScript {
    private:
        Point __start_position;
    protected:
        void OnStartAnimation(GameObject* Target) override { __start_position = Target->Position; }
        void OnUpdateAnimation(GameObject* Target, double AnimationTime) override {
            Target->Position.X = (int)roundf(Interpolation::FromInterpolationFunction(
                MovementInterpolationFunction, __start_position.X, EndPosition.X, AnimationTime
            ));
            Target->Position.Y = (int)roundf(Interpolation::FromInterpolationFunction(
                MovementInterpolationFunction, __start_position.Y, EndPosition.Y, AnimationTime
            ));
        }
    public:
        /// @brief The end position of the movement animation. Default is Point::Zero.
        Point EndPosition = Point::Zero;
        /// @brief The interpolation function type use for the movement animation. Default to linear.
        InterpolationFunction MovementInterpolationFunction = InterpolationFunction::Linear;
    };
    /// @brief The Move From Animation Script, provide a movement Animation Script for moving from specific position.
    class MoveFromAnimationScript : public AnimationScript {
    private:
        Point __end_position;
    protected:
        void OnStartAnimation(GameObject* Target) override { __end_position = Target->Position; }
        void OnUpdateAnimation(GameObject* Target, double AnimationTime) override {
            Target->Position.X = (int)roundf(Interpolation::FromInterpolationFunction(
                MovementInterpolationFunction, __end_position.X, StartPosition.X, AnimationTime
            ));
            Target->Position.Y = (int)roundf(Interpolation::FromInterpolationFunction(
                MovementInterpolationFunction, __end_position.Y, StartPosition.Y, AnimationTime
            ));
        }
    public:
        /// @brief The start position of the movement animation. Default is Point::Zero.
        Point StartPosition = Point::Zero;
        /// @brief The interpolation function type use for the movement animation. Default to linear.
        InterpolationFunction MovementInterpolationFunction = InterpolationFunction::Linear;
    };
}

#endif // __ENGINE_GAMEOBJECTANIMATION_H__