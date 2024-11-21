#ifndef __ENGINE_ANIMATION_H__
#define __ENGINE_ANIMATION_H__

#include "Engine_GameObject.h"
#include "Engine_Math.h"
#include "Engine_Renderer.h"

namespace Engine {
    class AnimationScript;

    /// @brief The Animation Script Event Caller, use for calling Animation Script event.
    typedef EventCaller<AnimationScript, EventArgs> AnimationScriptEventCaller;

    /// @brief The Animation Script class, provide a base class to create a script for animating Game Object.
    class AnimationScript : public GameScript {
    private:
        bool __is_started = false, __is_played = false;
        double __delay = 0, __duration = 0.01;
        double __time = 0;

        static bool __is_destroy_all;
        static std::unordered_set<AnimationScript*> __created_scripts;
    protected:
        /// @brief Occurred when the Animation Script is delaying (after started but before playing).
        /// @param Target The target Game Object of the animation.
        virtual void OnDelayAnimation(GameObject* Target) {}
        /// @brief Occurred when the Animation Script is starting (before updating).
        /// @param Target The target Game Object of the animation.
        virtual void OnStartAnimation(GameObject* Target) {}
        /// @brief Occurred when the Animation Script is request updating (when playing).
        /// @param Target The target Game Object of the animation.
        /// @param AnimationTime The time of the animation, usually in range [0, 1].
        virtual void OnUpdateAnimation(GameObject* Target, double AnimationTime) {}
        /// @brief Occurred when the Animation Script is stopping (after updating).
        /// @param Target The target Game Object of the animation.
        virtual void OnStopAnimation(GameObject* Target) {}
    public:
        /// @brief If this true (default), will reset the Animation Script after finish playing.
        bool ResetOnFinish = true;
        /// @brief If this true, will reset and play the Animation Script after finish the animation. Default is false.
        bool Repeated = false;

        /// @brief The Delay Animation Event, will occurred when the Animation Script is delaying (after started but before playing).
        AnimationScriptEventCaller DelayAnimationEvent;
        /// @brief The Start Animation Event, will occurred when the Animation Script is starting (before updating).
        AnimationScriptEventCaller StartAnimationEvent;
        /// @brief The Update Animation Event, will occurred when the Animation Script is request updating (when playing).
        AnimationScriptEventCaller UpdateAnimationEvent;
        /// @brief The Stop Animation Event, will occurred when the Animation Script is stopping (after updating).
        AnimationScriptEventCaller StopAnimationEvent;

        /// @brief Create a new Animation Script, should be created with 'new' keyword (new AnimationScript()).
        AnimationScript() { AnimationScript::__created_scripts.insert(this); }
        virtual ~AnimationScript() {
            if (!AnimationScript::__is_destroy_all)
                AnimationScript::__created_scripts.erase(this);
        }

        ENGINE_NOT_COPYABLE(AnimationScript)
        ENGINE_NOT_ASSIGNABLE(AnimationScript)

        /// @brief Set the duration of the Animation Script.
        /// @param Duration The duration in seconds to set, will clamped to be at least 0.01.
        void SetDuration(double Duration) { __duration = (Duration < 0.01) ? 0.01 : Duration; }
        /// @brief Get the duration of the Animation Script.
        /// @return The duration of the Animation Script in seconds.
        double GetDuration() const { return __duration; }

        /// @brief Set the amount of time to wait after starting the Animation Script, but before playing.
        /// @param Delay The amount of time to delay in seconds to set, will clamped to be non-negative.
        void SetDelay(double Delay) { __delay = Delay < 0 ? 0 : Delay; }
        /// @brief Get the amount of time to delay before playing of the Animation Script.
        /// @return The amount of time to delay before playing of the Animation Script in seconds.
        double GetDelay() const { return __delay; }

        /// @brief Get the current playing time of the Animation Script.
        /// @return The current playing time of the Animation Script in seconds.
        double GetPlayTime() const { return __time; }

        /// @brief Play the animation.
        void PlayAnimation() { __is_started = true; }
        /// @brief Pause the animation.
        void PauseAnimation() { __is_started = false; }
        /// @brief Reset the animation to the beginning.
        void ResetAnimation() { __time = 0; __is_played = false; }
        /// @brief Reset and stop the animation.
        void StopAnimation() { ResetAnimation(); __is_started = false; }

        /// @brief Check if the Animation Script is started and playing (not delaying).
        /// @return true if the Animation Script is playing, false otherwise.
        bool IsPlaying() const { return __is_started && __time >= __delay; }
        /// @brief Check if the Animation Script is started delaying.
        /// @return true if the Animation Script is delaying, false otherwise.
        bool IsDelay() const { return __is_started && __time < __delay; }
        /// @brief Check if the Animation Script is started.
        /// @return true if the Animation Script is started, false otherwise.
        bool IsStarted() const { return __is_started; }


        void OnUpdate(Engine::GameObject* Target) override {
            if (!__is_started)
                return;
            __time += Application::GetDeltaTime();
            if (__time < __delay) {
                OnDelayAnimation(Target); DelayAnimationEvent.Call(this);
                return;
            }
            if (!__is_played && __time >= __delay) {
                __is_played = true;
                OnStartAnimation(Target); StartAnimationEvent.Call(this);
            }
            double end_time = __delay + __duration;
            OnUpdateAnimation(Target, Interpolation::InverseLinear(__delay, end_time, __time));
            UpdateAnimationEvent.Call(this);
            if (__time > end_time) {
                __is_started = false;
                OnStopAnimation(Target); StopAnimationEvent.Call(this);
                if (ResetOnFinish || Repeated)
                    ResetAnimation();
                if (Repeated)
                    PlayAnimation();
            }
        }


        /// @brief Destroy all created Animation Scripts. This will be called on Engine::Deinitialize()
        static void DestroyAllCreatedScripts() {
            AnimationScript::__is_destroy_all = true;
            for (AnimationScript* script : AnimationScript::__created_scripts)
                if (script) delete script;
            AnimationScript::__created_scripts.clear();
            AnimationScript::__is_destroy_all = false;
        }
    };

}

bool Engine::AnimationScript::__is_destroy_all = false;
std::unordered_set<Engine::AnimationScript*> Engine::AnimationScript::__created_scripts
    = std::unordered_set<Engine::AnimationScript*>();

#endif // __ENGINE_ANIMATION_H__