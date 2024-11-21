#ifndef __ENGINE_INPUT_H__
#define __ENGINE_INPUT_H__

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_events.h>

#include "Engine_Enum.h"
#include "Engine_Keycode.h"
#include "Engine_Event.h"
#include "Engine_Structure.h"

namespace Engine {
	/// @brief The Keys static class, provide static method for working with keyboard input.
	class Keys final {
	public:
		/// @brief Check if a key is being pressed down.
		/// @param Scancode The Scancode of the key to check.
		/// @return true if the key is being pressed down, false otherwise.
		static bool IsKeyDown(Engine::Scancode Scancode) {
			return SDL_GetKeyboardState(nullptr)[(int)Scancode] == 1;
		}
		/// @brief Check if a key is being pressed down.
		/// @param KeyCode The Key Code of the key to check.
		/// @return true if the key is being pressed down, false otherwise.
		static bool IsKeyDown(Engine::KeyCode KeyCode) {
			return SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey((SDL_Keycode)KeyCode)] == 1;
		}

		/// @brief Check if a key is not being pressed down.
		/// @param Scancode The Scancode of the key to check.
		/// @return true if the key is not being pressed down, false otherwise.
		static bool IsKeyUp(Engine::Scancode Scancode) {
			return SDL_GetKeyboardState(nullptr)[(int)Scancode] == 0;
		}
		/// @brief Check if a key is not being pressed down.
		/// @param KeyCode The Key Code of the key to check.
		/// @return true if the key is not being pressed down, false otherwise.
		static bool IsKeyUp(Engine::KeyCode KeyCode) {
			return SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey((SDL_Keycode)KeyCode)] == 0;
		}

		/// @brief Get the corresponding Key Code from the given Scancode.
		/// @param Scancode The Scancode to get the Key Code.
		/// @return The Key Code that corresponds to the given Scancode.
		static KeyCode GetKeyCodeFromScancode(Engine::Scancode Scancode) {
			return (KeyCode)SDL_GetKeyFromScancode((SDL_Scancode)Scancode);
		}
		/// @brief Get the corresponding Scancode from the given Key Code.
		/// @param KeyCode The Key Code to get the Scancode.
		/// @return The Scancode that corresponds to the given Key Code.
		static Scancode GetScancodeFromKeyCode(Engine::KeyCode KeyCode) {
			return (Scancode)SDL_GetScancodeFromKey((SDL_KeyCode)KeyCode);
		}

		/// @brief Get the name of the given Key Code.
		/// @param KeyCode The Key Code to get the name from.
		/// @return The name of the given Key Code, or an empty string ("") if the given key didn't have
		/// a name.
		static const char* GetKeyName(Engine::KeyCode KeyCode) {
			return SDL_GetKeyName((SDL_Keycode)KeyCode);
		}
	};

	/// @brief The Key Event Args, usually for keyboard input handling event.
	struct KeyEventArgs : public EventArgs {
	public:
		/// @brief One or more modifier keys that being pressed down while the key 
		/// cause the event. If this None mean there's no modifier key. 
		KeyModifier Modifiers = KeyModifier::None;
		/// @brief The Scancode of the key that cause the event.
		Scancode Scancode = Scancode::Unknown;
		/// @brief The Key Code of the key that cause the event.
		KeyCode KeyCode = KeyCode::Unknown;

		/// @brief If this is true, this is a Key Down event.
		bool IsDownEvent = false;
		/// @brief If this is true, this is a Key Up event.
		bool IsUpEvent = false;
		/// @brief If this is true, the key is being pressed.
		bool IsPressed = false;
		/// @brief If this is true, the key is released.
		bool IsReleased = false;

		static KeyEventArgs FromSDLKeyboardEvent(const SDL_KeyboardEvent& key_e) {
			KeyEventArgs key_args;
			key_args.Modifiers = (KeyModifier)key_e.keysym.mod;
			key_args.Scancode = (Engine::Scancode)key_e.keysym.scancode;
			key_args.KeyCode = (Engine::KeyCode)key_e.keysym.sym;
			
			key_args.IsDownEvent = key_e.type == SDL_KEYDOWN;
			key_args.IsUpEvent = key_e.type == SDL_KEYUP;
			key_args.IsPressed = key_e.state == SDL_PRESSED;
			key_args.IsReleased = key_e.state == SDL_RELEASED;

			return key_args;
		}
	};

	/// @brief The Mouse static class, provide static method for working with mouse input.
	class Mouse final {
	public:
		/// @brief Get the cursor position that relative to the focus window.
		/// @return The cursor position that relative to the focus window.
		static Point GetLocalPosition() {
			int x = 0, y = 0; SDL_GetMouseState(&x, &y); return Point(x, y);
		}
		/// @brief Get the cursor position that relative to the desktop.
		/// @return The cursor position that relative to the desktop.
		static Point GetPosition() {
			int x = 0, y = 0; SDL_GetGlobalMouseState(&x, &y); return Point(x, y);
		}
		/// @brief Enable or disable the relative mode of the mouse.
		/// While in relative mode, the mouse is hidden, and the mouse motion event will
		/// occured continuous even if the mouse is at the edge of the window.
		/// @param Enable true to enable relative mode, false to disable it.
		static void SetRelativeMode(bool Enable) {
			SDL_SetRelativeMouseMode(Enable ? SDL_TRUE : SDL_FALSE);
		}
		/// @brief Check if currently in relative mode.
		/// @return true if currently in relative mode, false otherwise.
		static bool IsRelativeMode() { return SDL_GetRelativeMouseMode() == SDL_TRUE; }
	};

	/// @brief The Mouse Button Event Args, usually for mouse button handling event.
	struct MouseButtonEventArgs : public EventArgs {
	public:
		/// @brief The cursor position relative to the focus window, or Game Object.
		Point LocalPosition = Point::Zero;
		/// @brief The mouse button that cause the event.
		MouseButton Button = MouseButton::Unknown;
		/// @brief The number of clicks (1 for single-click, 2 for double-click,...).
		int Clicks = 0;

		/// @brief If this is true, this is a Mouse Button Down event.
		bool IsDownEvent = false;
		/// @brief If this is true, this is a Mouse Button Up event.
		bool IsUpEvent = false;
		/// @brief If this is true, the button is being pressed.
		bool IsPressed = false;
		/// @brief If this is true, the button is released.
		bool IsReleased = false;

		static MouseButtonEventArgs FromSDLMouseButtonEvent(const SDL_MouseButtonEvent& button_e) {
			MouseButtonEventArgs button_args;
			button_args.LocalPosition = Point(button_e.x, button_e.y);
			button_args.Button = (MouseButton)button_e.button;
			button_args.Clicks = button_e.clicks;

			button_args.IsDownEvent = button_e.type == SDL_MOUSEBUTTONDOWN;
			button_args.IsUpEvent = button_e.type == SDL_MOUSEBUTTONUP;
			button_args.IsPressed = button_e.state == SDL_PRESSED;
			button_args.IsReleased = button_e.state == SDL_RELEASED;

			return button_args;
		}
	};

	/// @brief The Mouse Wheel Event Args, usually for mouse wheel handling event.
	struct MouseWheelEventArgs : public EventArgs {
	public:
		/// @brief The amount scroll horizontally, negative on the left and positive on the right.
		int DeltaX = 0;
		/// @brief The amount scroll vertically, negative if scroll backward
		/// and positive if scroll forward.
		int DeltaY = 0;

		/// @brief The amount scroll horizontally, negative on the left and positive on the right.
		/// Same as DeltaX but with float precision.
		float PreciseDeltaX = 0.0F;
		/// @brief The amount scroll vertically, negative if scroll backward
		/// and positive if scroll forward. Same as DeltaY but with float precision.
		float PreciseDeltaY = 0.0F;

		/// @brief If this was true, the amount of scroll (DeltaX, DeltaY) is flipped.
		/// If this was true and you want to get the non-flipped value, multiply it by -1.
		bool IsFlipped = false;

		static MouseWheelEventArgs FromSDLMouseWheelEvent(const SDL_MouseWheelEvent& wheel_e) {
			MouseWheelEventArgs wheel_args;
			wheel_args.DeltaX = wheel_e.x;
			wheel_args.DeltaY = wheel_e.y;
			wheel_args.PreciseDeltaX = wheel_e.preciseX;
			wheel_args.PreciseDeltaY = wheel_e.preciseY;

			return wheel_args;
		}
	};

	/// @brief The Mouse Motion Event Args, usually for mouse move handling event.
	class MouseMotionEventArgs : public EventArgs {
	public:
		/// @brief Use flags to indicate the mouse button state (will contain the flag if pressed).
		MouseButtonMask ButtonState;
		/// @brief The mouse position relative to the focus window, or Game Object.
		Point LocalPosition = Point::Zero;
		/// @brief The x position of the mouse relative to the last mouse motion event.
		/// (negative if move left, positive if move right and 0 if not moving in x direction).
		int DeltaX = 0;
		/// @brief The x position of the mouse relative to the last mouse motion event.
		/// (negative if move up, positive if move down and 0 if not moving in y direction).
		int DeltaY = 0;

		static MouseMotionEventArgs FromSDLMouseMotionEvent(const SDL_MouseMotionEvent& motion_e) {
			MouseMotionEventArgs motion_args;
			motion_args.ButtonState = (MouseButtonMask)motion_e.state;
			motion_args.LocalPosition = Point(motion_e.x, motion_e.y);
			motion_args.DeltaX = motion_e.xrel;
			motion_args.DeltaY = motion_e.yrel;

			return motion_args;
		}
	};
}

#endif // __ENGINE_INPUT_H__