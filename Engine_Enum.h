#ifndef __ENGINE_ENUM_H__
#define __ENGINE_ENUM_H__

#include "Engine_Define.h"

#include <SDL2/SDL.h>

namespace Engine {
    /// @brief The Rectangle Alignment enum, usually for define the alignment in the rectangle.
    enum class RectangleAlignment {
        TopLeft = 0,
        TopCenter = 1,
        TopRight = 2,
        MiddleLeft = 3,
        MiddleCenter = 4,
        MiddleRight = 5,
        BottomLeft = 6,
        BottomCenter = 7,
        BottomRight = 8
    };

    /// @brief The Window Flags enum, use to identify the flags of the window.
    enum class WindowFlags {
        /// @brief Unknown flags.
        Unknown = 0,

        /// @brief The window is fullscreen.
        Fullscreen = SDL_WINDOW_FULLSCREEN,
        /// @brief The window is usable with OpenGL context.
        OpenGL = SDL_WINDOW_OPENGL,
        /// @brief The window is visible.
        Shown = SDL_WINDOW_SHOWN,
        /// @brief The window is not visible.
        Hidden = SDL_WINDOW_HIDDEN,
        /// @brief The window has no border decoration.
        Borderless = SDL_WINDOW_BORDERLESS,
        /// @brief The window can be resized by the user.
        Resizable = SDL_WINDOW_RESIZABLE,
        /// @brief The window is minimized.
        Minimized = SDL_WINDOW_MINIMIZED,
        /// @brief The window is maximized.
        Maximized = SDL_WINDOW_MAXIMIZED,
        /// @brief The window has grabbed mouse input.
        MouseGrabbed = SDL_WINDOW_MOUSE_GRABBED,
        /// @brief The window has input focus.
        InputFocus = SDL_WINDOW_INPUT_FOCUS,
        /// @brief The window has mouse focus.
        MouseFocus = SDL_WINDOW_MOUSE_FOCUS,
        /// @brief The window is fullscreen in desktop mode (fullscreen but take the desktop size as window size).
        FullscreenDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
        Foreign = SDL_WINDOW_FOREIGN,
        /// @brief The window is created in high-DPI mode (if supported).
        AllowHighDPI = SDL_WINDOW_ALLOW_HIGHDPI,
        /// @brief The window has mouse captured.
        MouseCapture = SDL_WINDOW_MOUSE_CAPTURE,
        /// @brief The window is always be above others.
        AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP,
        /// @brief The window is not added to the taskbar.
        SkipTaskbar = SDL_WINDOW_SKIP_TASKBAR,
        /// @brief The window is treated as a utility window.
        Utility = SDL_WINDOW_UTILITY,
        /// @brief The window is treated as a tooltip.
        Tooltip = SDL_WINDOW_TOOLTIP,
        /// @brief The window is treated as a popup menu.
        PopupMenu = SDL_WINDOW_POPUP_MENU,
        /// @brief The window has grabbed keyboard input.
        KeyboardGrabbed = SDL_WINDOW_KEYBOARD_GRABBED,
        /// @brief The window is usable with Vulkan surface.
        Vulkan = SDL_WINDOW_VULKAN,
        /// @brief The window is usable with Metal view.
        Metal = SDL_WINDOW_METAL
    };
    ENGINE_DEFINE_ENUM_OPERATORS(WindowFlags)

    /// @brief The Draw Blend Mode enum class, the mode use for blending operation.
    enum class DrawBlendMode {
        None = SDL_BLENDMODE_NONE,
        AlphaBlend = SDL_BLENDMODE_BLEND,
        Additive = SDL_BLENDMODE_ADD,
        Modulate = SDL_BLENDMODE_MOD,
        Multiply = SDL_BLENDMODE_MUL,
        Invalid = SDL_BLENDMODE_INVALID
    };

	/// @brief The Mouse Button that used for mouse handling.
	enum class MouseButton {
		Unknown = 0,
		Left = SDL_BUTTON_LEFT,
		Right = SDL_BUTTON_RIGHT,
		Middle = SDL_BUTTON_MIDDLE,
		X1 = SDL_BUTTON_X1,
		X2 = SDL_BUTTON_X2
	};

	/// @brief The Mouse Button Mask that used for mouse button state.
	enum class MouseButtonMask {
		Left = SDL_BUTTON_LMASK,
		Right = SDL_BUTTON_RMASK,
		Middle = SDL_BUTTON_MMASK,
		X1 = SDL_BUTTON_X1MASK,
		X2 = SDL_BUTTON_X2MASK
	};
}

#endif // __ENGINE_ENUM_H__