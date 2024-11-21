#ifndef __ENGINE_WINDOW_H__
#define __ENGINE_WINDOW_H__

#include "Engine_Input.h"
#include "Engine_Application.h"
#include "Engine_Structure.h"

#include <SDL2/SDL_video.h>

namespace Engine {
    /// @brief The Position Event Args, use for event that related to position.
    struct PositionEventArgs : public EventArgs {
    public:
        /// @brief The Position that the event send.
        Point Position = Point::Zero;
    };

    /// @brief The Size Event Args, use for event that related to size.
    struct SizeEventArgs : public EventArgs {
    public:
        /// @brief The Size that the event send.
        Engine::Size Size = Size::Zero;
    };

    /// @brief The Window flags, use to managing the window of the game.
    class Window final {
    private:
        static SDL_Window* __window;
    public:
        /// @brief The Shown Event, occurred when the Window has shown (visible).
        static GlobalEventCaller<EventArgs> ShownEvent;
        /// @brief The Hidden Event, occurred when the Window has hidden (not visible).
        static GlobalEventCaller<EventArgs> HiddenEvent;
        /// @brief The Minimized Event, occurred when the Window has minimized.
        static GlobalEventCaller<EventArgs> MinimizedEvent;
        /// @brief The Maximized Event, occurred when the Window has maximized.
        static GlobalEventCaller<EventArgs> MaximizedEvent;
        /// @brief The Restored Event, occurred when the Window has restored from minimized or maximized.
        static GlobalEventCaller<EventArgs> RestoredEvent;
        /// @brief The Mouse Focus Gained Event, occurred when the Window has gained mouse focus.
        static GlobalEventCaller<EventArgs> MouseFocusGainedEvent;
        /// @brief The Mouse Focus Lost Event, occurred when the Window has lost mouse focus.
        static GlobalEventCaller<EventArgs> MouseFocusLostEvent;
        /// @brief The Keyboard Focus Gained Event, occurred when the Window has gained keyboard focus.
        static GlobalEventCaller<EventArgs> KeyboardFocusGainedEvent;
        /// @brief The Keyboard Focus Lost Event, occurred when the Window has lost keyboard focus.
        static GlobalEventCaller<EventArgs> KeyboardFocusLostEvent;
        /// @brief The Request Close Event, occurred when the Window has requested to be close (usually by the close button).
        static GlobalEventCaller<EventArgs> RequestCloseEvent;

        /// @brief The Moved Event, occurred when the Window has moved.
        static GlobalEventCaller<PositionEventArgs> MovedEvent;
        /// @brief The Resized Event, occurred when the Window has resized.
        static GlobalEventCaller<SizeEventArgs> ResizedEvent;
        /// @brief The Key Down Event, occurred when a key is being pressed while the Window has keyboard input focus.
        static GlobalEventCaller<KeyEventArgs> KeyDownEvent;
        /// @brief The Key Up Event, occurred when a key is being released while the Window has keyboard input focus.
        static GlobalEventCaller<KeyEventArgs> KeyUpEvent;
        /// @brief The Mouse Down Event, occurred when a mouse button is being pressed while the Window has mouse input focus.
        static GlobalEventCaller<MouseButtonEventArgs> MouseDownEvent;
        /// @brief The Mouse Up Event, occurred when a mouse button is being released while the Window has mouse input focus.
        static GlobalEventCaller<MouseButtonEventArgs> MouseUpEvent;
        /// @brief The Mouse Scroll Event, occurred when the mouse wheel is being scrolled while the Window has mouse input focus.
        static GlobalEventCaller<MouseWheelEventArgs> MouseScrollEvent;
        /// @brief The Mouse Moved Event, occurred when the mouse cursor is moved while the Window has mouse input focus.
        static GlobalEventCaller<MouseMotionEventArgs> MouseMovedEvent;

        /// @brief Get the flags of the Window (SDL_WindowFlags).
        /// @return The flags of the Window, or WindowFlags::Unknown on failed.
        static WindowFlags GetFlags() {
            return Window::__window ? static_cast<WindowFlags>(SDL_GetWindowFlags(Window::__window)) : WindowFlags::Unknown; }
        /// @brief Get the numeric ID of the Window.
        /// @return The numeric ID of the Window, or 0 on failed.
        static uint32_t GetID() { return Window::__window ? SDL_GetWindowID(Window::__window) : 0; }

        /// @brief Get the title of the Window.
        /// @return The title of the Window, or an empty string ("") on failed or there's no title.
        static const char* GetTitle() { return Window::__window ? SDL_GetWindowTitle(Window::__window) : ""; }
        /// @brief Set the title of the Window.
        /// @param Title The title of the Window. If null, will set to an empty string ("").
        static void SetTitle(const char* Title) { if (Window::__window) SDL_SetWindowTitle(Window::__window, !Title ? "" : Title); }
    
        /// @brief Get the position of the Window.
        /// @return The position of the Window, or Point::Zero on failed.
        static Point GetPosition() {
            if (!Window::__window) return Point::Zero;
            int x = 0, y = 0; SDL_GetWindowPosition(Window::__window, &x, &y); return {x, y};
        }
        /// @brief Set the position of the Window.
        /// @param Position The position to set.
        static void SetPosition(const Point& Position) {
            if (Window::__window)
                SDL_SetWindowPosition(Window::__window, Position.X, Position.Y);
        }
        /// @brief Set the position of the Window.
        /// @param X The x position of the Window.
        /// @param Y The y position of the Window.
        static void SetPosition(int X, int Y) { SetPosition(Point(X, Y)); }

        /// @brief Get the ratio of the Window screen (Width/Height).
        /// @return The ratio of the Window screen, or 0 on failed (or either Width or Height is 0).
        static double GetRatio() {
            if (!Window::__window) return 0;
            int w = 0, h = 0; SDL_GetWindowSize(Window::__window, &w, &h);
            if (w == 0 || h == 0) return 0;
            return (double)w / (double)h;
        }

        /// @brief Get the size of the Window.
        /// @return The size of the Window, or Size::Zero on failed.
        static Size GetSize() {
            if (!Window::__window) return Size::Zero;
            int w = 0, h = 0; SDL_GetWindowSize(Window::__window, &w, &h); return {w, h};
        }
        /// @brief Set the size of the Window.
        /// @param Size The size to set, will not set if the given size area is 0.
        static void SetSize(const Engine::Size& Size) {
            if (Window::__window && !Size.IsEmptyArea())
                SDL_SetWindowSize(Window::__window, Size.Width, Size.Height);
        }
        /// @brief Set the size of the Window.
        /// @param Width The width of the window, will not set if this value is 0.
        /// @param Height The height of the window, will not set if this value is 0.
        static void SetSize(int Width, int Height) { SetSize(Size(Width, Height)); }

        /// @brief Get the minimum size of the Window.
        /// @return The minimum size of the Window, or Size::Zero on failed.
        static Size GetMinimumSize() {
            if (!Window::__window) return Size::Zero;
            int w = 0, h = 0; SDL_GetWindowMinimumSize(Window::__window, &w, &h); return {w, h};
        }
        /// @brief Set the minimum size of the Window.
        /// @param Size The minimum size to set, will not set if the given size area is 0.
        static void SetMinimumSize(const Engine::Size& Size) {
            if (Window::__window && !Size.IsEmptyArea())
                SDL_SetWindowMinimumSize(Window::__window, Size.Width, Size.Height);
        }
        /// @brief Set the minimum size of the Window.
        /// @param Width The minimum width of the window, will not set if this value is 0.
        /// @param Height The minimum height of the window, will not set if this value is 0.
        static void SetMinimumSize(int Width, int Height) { SetMinimumSize(Size(Width, Height)); }

        /// @brief Get the maximum size of the Window.
        /// @return The maximum size of the Window, or Size::Zero on failed.
        static Size GetMaximumSize() {
            if (!Window::__window) return Size::Zero;
            int w = 0, h = 0; SDL_GetWindowMaximumSize(Window::__window, &w, &h); return {w, h};
        }
        /// @brief Set the maximum size of the Window.
        /// @param Size The maximum size to set, will not set if the given size area is 0.
        static void SetMaximumSize(const Engine::Size& Size) {
            if (Window::__window && !Size.IsEmptyArea())
                SDL_SetWindowMaximumSize(Window::__window, Size.Width, Size.Height);
        }
        /// @brief Set the maximum size of the Window.
        /// @param Width The maximum width of the window, will not set if this value is 0.
        /// @param Height The maximum height of the window, will not set if this value is 0.
        static void SetMaximumSize(int Width, int Height) { SetMaximumSize(Size(Width, Height)); }

        /// @brief Check if the Window is resizable by the user.
        /// @return true if the Window is resizable, false otherwise (also on failed).
        static bool IsResizable() { return (static_cast<uint64_t>(GetFlags()) & SDL_WINDOW_RESIZABLE) != 0; }
        /// @brief Make the Window can be resized by the user.
        static void EnableResizing() { if (Window::__window) SDL_SetWindowResizable(Window::__window, SDL_TRUE); }
        /// @brief Make the Window cannot be resized by the user.
        static void DisableResizing() { if (Window::__window) SDL_SetWindowResizable(Window::__window, SDL_FALSE); }
    
        /// @brief Check if the Window is visible.
        /// @return true if the Window is visible, false otherwise (also on failed).
        static bool IsVisible() { return (static_cast<uint64_t>(GetFlags()) & SDL_WINDOW_SHOWN) != 0; }
        /// @brief Make the Window visible.
        static void Show() { if (Window::__window) SDL_ShowWindow(Window::__window); }
        /// @brief Make the Window not visible.
        static void Hide() { if (Window::__window) SDL_HideWindow(Window::__window); }

        /// @brief Check if the Window is fullscreen.
        /// @return true if the Window is fullscreen, false otherwise (also on failed.)
        static bool IsFullscreen() { return (static_cast<uint64_t>(GetFlags()) & SDL_WINDOW_FULLSCREEN) != 0; }
        /// @brief Make the Window fullscreen.
        /// @param RealFullscreen If this false (default), will take the desktop size as the window size (fake fullscreen).
        static void MakeFullscreen(bool RealFullscreen = false) {
            if (Window::__window)
                SDL_SetWindowFullscreen(Window::__window, RealFullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        /// @brief Restore the Window from fullscreen.
        static void RestoreFromFullscreen() { if (Window::__window) SDL_RestoreWindow(Window::__window); }

        /// @brief Check if the Window have a border.
        /// @return true if the Window is bordered, false otherwise.
        static bool IsBordered() { return (static_cast<uint64_t>(GetFlags()) & SDL_WINDOW_BORDERLESS) == 0; }
        /// @brief Make the Window bordered (have a border).
        static void MakeBordered() { if (Window::__window) SDL_SetWindowBordered(Window::__window, SDL_TRUE); }
        /// @brief Make the Window borderless (didn't have a border).
        static void MakeBorderless() { if (Window::__window) SDL_SetWindowBordered(Window::__window, SDL_FALSE); }

        /// @brief Make the window always above others window.
        static void EnableAlwaysOnTop() { if (Window::__window) SDL_SetWindowAlwaysOnTop(Window::__window, SDL_TRUE); }
        /// @brief Disable the always on top mode of the window.
        static void DisableAlwaysOnTop() { if (Window::__window) SDL_SetWindowAlwaysOnTop(Window::__window, SDL_FALSE); }
        /// @brief Check if the window is always above others.
        /// @return true if the window is always on top, false otherwise.
        static bool IsAlwaysOnTop() { return (static_cast<uint64_t>(GetFlags()) & SDL_WINDOW_ALWAYS_ON_TOP) != 0; }

        /// @brief Raise the window to above other and set the input focus to it.
        static void RaiseWindow() { if (Window::__window) SDL_RaiseWindow(Window::__window); }

        /// @brief Check if the Window is initialized successfully.
        /// @return true if the Window is initialized successfully, false otherwise.
        static bool IsInitialized() { return (bool)Window::__window; }
        /// @brief Initialize (or re-initialize) the Window, this should be called on Engine::Initialize().
        /// If you called this manually (usually for re-initialize), then you must re-initialize the Renderer also
        /// (as now the Renderer is unusable because it's target the old window, which is destroyed.)
        /// @return true on success, false on failure.
        static bool Initialize() {
            if (Window::__window) {
                SDL_DestroyWindow(Window::__window);
                Window::__window = nullptr;
            }
            
            Size target_size = Application::DefaultWindowSize.Absolute();
            if (target_size.IsEmptyArea())
                target_size = Size(800, 500);
            Window::__window = SDL_CreateWindow(
                Application::Name.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                target_size.Width, target_size.Height,
                static_cast<uint32_t>(Application::WindowFlags)
            );
            return (bool)Window::__window;
        }
        /// @brief Deinitialize the Window, this should be called on Engine::Deinitialize().
        /// After calling this, the Window will be unusable (also the Renderer will be unusable
        /// because it's target the window, which is destroyed).
        static void Deinitialize() {
            if (Window::__window) {
                SDL_DestroyWindow(Window::__window);
                Window::__window = nullptr;
            }
        }

        /// @brief Handle event of the Window.
        /// @return The number of event handled.
        static size_t HandleEvent();
    };
}

SDL_Window* Engine::Window::__window = nullptr;

/// @brief The Shown Event, occurred when the Window has shown (visible).
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::ShownEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Hidden Event, occurred when the Window has hidden (not visible).
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::HiddenEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Minimized Event, occurred when the Window has minimized.
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::MinimizedEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Maximized Event, occurred when the Window has maximized.
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::MaximizedEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Restored Event, occurred when the Window has restored from minimized or maximized.
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::RestoredEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Mouse Focus Gained Event, occurred when the Window has gained mouse focus.
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::MouseFocusGainedEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Mouse Focus Lost Event, occurred when the Window has lost mouse focus.
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::MouseFocusLostEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Keyboard Focus Gained Event, occurred when the Window has gained keyboard focus.
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::KeyboardFocusGainedEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Keyboard Focus Lost Event, occurred when the Window has lost keyboard focus.
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::KeyboardFocusLostEvent = Engine::GlobalEventCaller<Engine::EventArgs>();
/// @brief The Request Close Event, occurred when the Window has requested to be close (usually by the close button).
Engine::GlobalEventCaller<Engine::EventArgs> Engine::Window::RequestCloseEvent = Engine::GlobalEventCaller<Engine::EventArgs>();

/// @brief The Moved Event, occurred when the Window has moved.
Engine::GlobalEventCaller<Engine::PositionEventArgs> Engine::Window::MovedEvent = Engine::GlobalEventCaller<Engine::PositionEventArgs>();
/// @brief The Resized Event, occurred when the Window has resized.
Engine::GlobalEventCaller<Engine::SizeEventArgs> Engine::Window::ResizedEvent = Engine::GlobalEventCaller<Engine::SizeEventArgs>();
/// @brief The Key Down Event, occurred when a key is being pressed while the Window has keyboard input focus.
Engine::GlobalEventCaller<Engine::KeyEventArgs> Engine::Window::KeyDownEvent = Engine::GlobalEventCaller<Engine::KeyEventArgs>();
/// @brief The Key Up Event, occurred when a key is being released while the Window has keyboard input focus.
Engine::GlobalEventCaller<Engine::KeyEventArgs> Engine::Window::KeyUpEvent = Engine::GlobalEventCaller<Engine::KeyEventArgs>();
/// @brief The Mouse Down Event, occurred when a mouse button is being pressed while the Window has mouse input focus.
Engine::GlobalEventCaller<Engine::MouseButtonEventArgs> Engine::Window::MouseDownEvent = Engine::GlobalEventCaller<Engine::MouseButtonEventArgs>();
/// @brief The Mouse Up Event, occurred when a mouse button is being released while the Window has mouse input focus.
Engine::GlobalEventCaller<Engine::MouseButtonEventArgs> Engine::Window::MouseUpEvent = Engine::GlobalEventCaller<Engine::MouseButtonEventArgs>();
/// @brief The Mouse Scroll Event, occurred when the mouse wheel is being scrolled while the Window has mouse input focus.
Engine::GlobalEventCaller<Engine::MouseWheelEventArgs> Engine::Window::MouseScrollEvent = Engine::GlobalEventCaller<Engine::MouseWheelEventArgs>();
/// @brief The Mouse Moved Event, occurred when the mouse cursor is moved while the Window has mouse input focus.
Engine::GlobalEventCaller<Engine::MouseMotionEventArgs> Engine::Window::MouseMovedEvent = Engine::GlobalEventCaller<Engine::MouseMotionEventArgs>();

#endif // __ENGINE_WINDOW_H__