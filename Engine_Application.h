#ifndef __ENGINE_APPLICATION_H__
#define __ENGINE_APPLICATION_H__

#define ENGINE_MIN_WAIT_TIME_PER_UPDATE 0.001L

#include "Engine_Enum.h"
#include "Engine_Event.h"

#include <string>

namespace Engine {
    /// @brief The Application class, use to managing the game application.
    class Application final {
    private:
        static bool __is_running, __is_exiting;
        static long double __update_wait_time;
        static long double __delta_time;
    public:
        /// @brief If this true (default), will rendering with the Game Scene.
        static bool RenderingScene;
        /// @brief If this true, will make the Renderer automatically present with the vertical sync rate. After changing this, you
        /// need to reinitialize the Renderer. Default is false.
        static bool EnableVSyncPresent;
        /// @brief If this true (default), will handling input event of the application (both keyboard and mouse).
        static bool HandleInput;

        /// @brief The name of the Application, default is "Game".
        static std::string Name;
        /// @brief The flags use to create the Window OR's together. After changing this, you need to reinitialize the Window
        /// for this to apply. Default to WindowFlags::Hidden.
        static Engine::WindowFlags WindowFlags;
        /// @brief The default window size that will use when initialize the Window. Default to (800, 500).
        static Size DefaultWindowSize;

        /// @brief The Load Event, occurred when the Application is about to run.
        static GlobalEventCaller<EventArgs> LoadEvent;
        /// @brief The Update Event, occurred before the Application handling event.
        static GlobalEventCaller<EventArgs> EarlyUpdateEvent;
        /// @brief The Update Event, occurred when the Application has requested to update.
        static GlobalEventCaller<EventArgs> UpdateEvent;
        /// @brief The Update Event, occurred after the current Game Scene had updated and rendered.
        static GlobalEventCaller<EventArgs> LateUpdateEvent;
        /// @brief The Unload Event, occurred when the Application is about to stop running.
        static GlobalEventCaller<EventArgs> UnloadEvent;

        /// @brief Check if the Application is currently running.
        /// @return true if the Application is currently running, false otherwise.
        static bool IsRunning() { return Application::__is_running; }
        /// @brief Stop the Application.
        static void Stop() { Application::__is_running = false; }

        /// @brief Start the Application (if the Application hasn't started), this will enter the main loop.
        /// The Window must be initialized successfully before calling this, and not deinitialized before this return.
        static void Start();

        /// @brief Handle the window event of the Application.
        /// @return The number of event handled.
        static size_t HandleWindowEvent();

        /// @brief Set the maximum update per seconds of the Application (this will use to calculate the amount of time to wait per
        /// update, so it's not very accurate).
        /// @param MaxUpdateRate The maximum update per seconds to set, or 0 for unlimited.
        static void SetMaximumUpdateRate(uint32_t MaxUpdateRate) {
            if (MaxUpdateRate == 0) Application::__update_wait_time = 0;
            else
                Application::__update_wait_time = 1.0L / MaxUpdateRate;
        }

        /// @brief Get the time that the last update took to complete.
        /// @return The time that the last update took to complete. Default to 0.001 if the Application wasn't running
        /// for the first time.
        static long double GetDeltaTime() { return Application::__delta_time; }
    };
}

bool Engine::Application::__is_running = false;
bool Engine::Application::__is_exiting = false;
long double Engine::Application::__update_wait_time = 0;
long double Engine::Application::__delta_time = 0.001L;

bool Engine::Application::RenderingScene = true;
bool Engine::Application::EnableVSyncPresent = false;
bool Engine::Application::HandleInput = true;
std::string Engine::Application::Name = "Game";
Engine::WindowFlags Engine::Application::WindowFlags = Engine::WindowFlags::Hidden;
Engine::Size Engine::Application::DefaultWindowSize = Engine::Size(800, 500);

Engine::GlobalEventCaller<Engine::EventArgs> Engine::Application::LoadEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Application::EarlyUpdateEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Application::UpdateEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Application::LateUpdateEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Application::UnloadEvent = Engine::GlobalEventCaller<Engine::EventArgs>();

#endif // __ENGINE_APPLICATION_H__