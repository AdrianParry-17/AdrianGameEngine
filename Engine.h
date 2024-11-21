#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Engine_Animation.h"
#include "Engine_Application.h"
#include "Engine_BasicGameObject.h"
#include "Engine_Color.h"
#include "Engine_Define.h"
#include "Engine_Enum.h"
#include "Engine_Event.h"
#include "Engine_Font.h"
#include "Engine_GameObject.h"
#include "Engine_GameObjectAnimation.h"
#include "Engine_Helper.h"
#include "Engine_Imaging.h"
#include "Engine_Input.h"
#include "Engine_Keycode.h"
#include "Engine_Math.h"
#include "Engine_Renderer.h"
#include "Engine_Resource.h"
#include "Engine_Structure.h"
#include "Engine_UIGameObject.h"
#include "Engine_Window.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <chrono>
#include <thread>

namespace Engine {
    /// @brief Initialize the Engine, must be called before using the Engine.
    /// If this return false, you shouldn't continue using it.
    /// @return true on success, false on failure.
    bool Initialize() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            return false;
        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
            return false;
        if (TTF_Init() != 0)
            return false;
        if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
            return false;
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
            return false;
        
        if (!Window::Initialize())
            return false;
        if (!Renderer::Initialize())
            return false;

        if (!GameScene::Initialize())
            return false;

        return true;
    }

    /// @brief Deinitialize the Engine. After calling this, you must reinitialize the Engine before using
    /// it again.
    void Deinitialize() {
        //* Animation
        AnimationScript::DestroyAllCreatedScripts();

        //* Game Object / Game Scene
        GameObject::DestoryAllCreatedGameObjects();
        GameScene::Deinitialize();

        //* Font
        Font::DestroyAllCreatedFonts();

        //* Color Map / Texture.
        ColorMap::DestoryAllCreatedColorMaps();
        Texture::DestoryAllCreatedTextures();
        
        //* Window and renderer
        Renderer::Deinitialize();
        Window::Deinitialize();

        Mix_CloseAudio();
        SDL_Quit(); IMG_Quit(); TTF_Quit(); Mix_Quit();
    }
}

void Engine::Application::Start() {
    if (Application::__is_running || Application::__is_exiting || !Window::IsInitialized())
        return;

    Application::__is_running = true;
    Application::__is_exiting = false;

    Application::LoadEvent.Call();
    while (Application::__is_running) {
        // Check the availability of the Window.
        if (!Window::IsInitialized())
            break;

        auto start = std::chrono::steady_clock::now();
        
        Application::EarlyUpdateEvent.Call();

        // Handle the Window event.
        Application::HandleWindowEvent();

        // Check the availability of the Window again (in case the Window became not available after handle event).
        if (!Window::IsInitialized())
            break;
        
        Application::UpdateEvent.Call();

        if (GameScene::IsInitialized() && Application::RenderingScene) {
            GameScene* curr_scene = GameScene::GetCurrentScene();
            Renderer::SetDrawColor(curr_scene->BackgroundColor);
            Renderer::Clear();
            if (curr_scene->BackgroundTexture)
                Renderer::FillTexture(curr_scene->BackgroundTexture);

            curr_scene->ForEach([](GameObject* obj) {
                if (!obj->Enabled) return;

                obj->RaiseUpdateEvent(true);

                RenderEventArgs render_args;
                render_args.TargetArea = Rectangle(Point::Zero, Window::GetSize()).LocalToGlobal(obj->GetArea(), obj->Alignment);
                obj->RaiseRenderEvent(&render_args, true);
            });
            Renderer::Present();
        }

        Application::LateUpdateEvent.Call();

        if (Application::__update_wait_time >= ENGINE_MIN_WAIT_TIME_PER_UPDATE)
            SDL_Delay((int)(Application::__update_wait_time * 1000));

        Application::__delta_time = 1E-9L * (std::chrono::steady_clock::now() - start).count();
    }
    Application::__is_running = false;
    Application::__is_exiting = true;

    if (!Window::IsInitialized())
        Application::UnloadEvent.Call();

    Application::__is_exiting = false;
}

size_t Engine::Application::HandleWindowEvent() {
    SDL_Event e;
    size_t count = 0;
    while (SDL_PollEvent(&e) != 0) {
        // Check the availability of the Window.
        if (!Window::IsInitialized())
            continue;
        uint32_t window_id = Window::GetID();

        switch (e.type)
        {
        case SDL_WINDOWEVENT: {
            // Check if it's an event for the Window.
            if (e.window.windowID != window_id)
                break;

            count++;

            // Handling window event.
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_SHOWN:
                Window::ShownEvent.Call();
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                Window::HiddenEvent.Call();
                break;
            case SDL_WINDOWEVENT_MOVED: {
                Engine::PositionEventArgs args; args.Position = Point(e.window.data1, e.window.data2);
                Window::MovedEvent.Call(&args);
                break;
            }
            case SDL_WINDOWEVENT_RESIZED: {
                Engine::SizeEventArgs args; args.Size = Size(e.window.data1, e.window.data2);
                Window::ResizedEvent.Call(&args);
                break;
            }
            case SDL_WINDOWEVENT_MINIMIZED:
                Window::MinimizedEvent.Call();
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                Window::MaximizedEvent.Call();
                break;
            case SDL_WINDOWEVENT_RESTORED:
                Window::RestoredEvent.Call();
                break;
            case SDL_WINDOWEVENT_ENTER:
                Window::MouseFocusGainedEvent.Call();
                break;
            case SDL_WINDOWEVENT_LEAVE:
                Window::MouseFocusLostEvent.Call();
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                Window::KeyboardFocusGainedEvent.Call();
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                Window::KeyboardFocusLostEvent.Call();
                break;
            case SDL_WINDOWEVENT_CLOSE:
                Window::RequestCloseEvent.Call();
                break;

            default:
                break;
            }
            break;
        }
        case SDL_KEYDOWN: {
            // Check if it's an event for the Window.
            if (!Application::HandleInput)
                break;
            if (e.window.windowID != window_id)
                break;

            count++;
            KeyEventArgs key_args = KeyEventArgs::FromSDLKeyboardEvent(e.key);
            Window::KeyDownEvent.Call(&key_args);

            if (GameScene::IsInitialized()) {
                GameScene* curr_scene = GameScene::GetCurrentScene();
                curr_scene->ForEach([&key_args](GameObject* obj) {
                    if (!obj->Enabled || !obj->HandleInput) return;
                    obj->RaiseKeyDownEvent(&key_args, true);
                });
            }

            break;
        }
        case SDL_KEYUP: {
            // Check if it's an event for the Window.
            if (!Application::HandleInput)
                break;
            if (e.window.windowID != window_id)
                break;

            count++;
            KeyEventArgs key_args = KeyEventArgs::FromSDLKeyboardEvent(e.key);
            Window::KeyUpEvent.Call(&key_args);

            if (GameScene::IsInitialized()) {
                GameScene* curr_scene = GameScene::GetCurrentScene();
                curr_scene->ForEach([&key_args](GameObject* obj) {
                    if (!obj->Enabled || !obj->HandleInput) return;
                    obj->RaiseKeyUpEvent(&key_args, true);
                });
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            // Check if it's an event for the Window.
            if (!Application::HandleInput)
                break;
            if (e.window.windowID != window_id)
                break;

            count++;
            MouseButtonEventArgs button_args = MouseButtonEventArgs::FromSDLMouseButtonEvent(e.button);
            Window::MouseDownEvent.Call(&button_args);

            if (GameScene::IsInitialized()) {
                GameScene* curr_scene = GameScene::GetCurrentScene();
                curr_scene->ForEach([&](GameObject* obj) {
                    if (!obj->Enabled || !obj->HandleInput) return;

                    MouseButtonEventArgs child_args(button_args);
                    Rectangle child_area = Rectangle(Point::Zero, Window::GetSize()).LocalToGlobal(obj->GetArea(), obj->Alignment);
                    child_args.LocalPosition -= child_area.TopLeft();

                    obj->RaiseMouseDownEvent(&child_args, true);
                });
            }

            break;
        }
        case SDL_MOUSEBUTTONUP: {
            // Check if it's an event for the Window.
            if (!Application::HandleInput)
                break;
            if (e.window.windowID != window_id)
                break;

            count++;
            MouseButtonEventArgs button_args = MouseButtonEventArgs::FromSDLMouseButtonEvent(e.button);
            Window::MouseUpEvent.Call(&button_args);

            if (GameScene::IsInitialized()) {
                GameScene* curr_scene = GameScene::GetCurrentScene();
                curr_scene->ForEach([&](GameObject* obj) {
                    if (!obj->Enabled || !obj->HandleInput) return;

                    MouseButtonEventArgs child_args(button_args);
                    Rectangle child_area = Rectangle(Point::Zero, Window::GetSize()).LocalToGlobal(obj->GetArea(), obj->Alignment);
                    child_args.LocalPosition -= child_area.TopLeft();

                    obj->RaiseMouseUpEvent(&child_args, true);
                });
            }
            break;
        }
        case SDL_MOUSEWHEEL: {
            // Check if it's an event for the Window.
            if (!Application::HandleInput)
                break;
            if (e.window.windowID != window_id)
                break;

            count++;
            MouseWheelEventArgs wheel_args = MouseWheelEventArgs::FromSDLMouseWheelEvent(e.wheel);
            Window::MouseScrollEvent.Call(&wheel_args);

            if (GameScene::IsInitialized()) {
                GameScene* curr_scene = GameScene::GetCurrentScene();
                curr_scene->ForEach([&wheel_args](GameObject* obj) {
                    if (!obj->Enabled || !obj->HandleInput) return;
                    obj->RaiseMouseScrollEvent(&wheel_args, true);
                });
            }
            break;
        }
        case SDL_MOUSEMOTION: {
            // Check if it's an event for the Window.
            if (!Application::HandleInput)
                break;
            if (e.window.windowID != window_id)
                break;

            count++;
            MouseMotionEventArgs motion_args = MouseMotionEventArgs::FromSDLMouseMotionEvent(e.motion);
            Window::MouseMovedEvent.Call(&motion_args);

            if (GameScene::IsInitialized()) {
                GameScene* curr_scene = GameScene::GetCurrentScene();
                curr_scene->ForEach([&](GameObject* obj) {
                    if (!obj->Enabled || !obj->HandleInput) return;

                    MouseMotionEventArgs child_args(motion_args);
                    Rectangle child_area = Rectangle(Point::Zero, Window::GetSize()).LocalToGlobal(obj->GetArea(), obj->Alignment);
                    child_args.LocalPosition -= child_area.TopLeft();

                    obj->RaiseMouseMovedEvent(&child_args, true);
                });
            }
            break;
        }
        default:
            break;
        }
    }

    return count;
}

#endif // __ENGINE_H__