#ifndef __ENGINE_GAMEOBJECT_H__
#define __ENGINE_GAMEOBJECT_H__

#include "Engine_Renderer.h"

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <list>
#include <algorithm>

namespace Engine {
    class GameObject;

    /// @brief The Game Script class, provide a base class to create a script that can be attached to control the
    /// Game Object (usually for animation). A Game Script instance should only created/destroy by the Game Object with
    /// AddScript/DestroyScript member function of the Game Object.
    class GameScript {
    public:
        GameScript() = default;
        virtual ~GameScript() {}

        ENGINE_NOT_COPYABLE(GameScript)
        ENGINE_NOT_ASSIGNABLE(GameScript)

        /// @brief Will be called when the Game Script was added to the Game Object (with AddScript())
        /// @param Target The target Game Object of the script.
        virtual void OnStart(GameObject* Target) {}
        /// @brief Will be called when the Game Script was destroyed and removed from the Game Object (with DestroyScript()).
        /// @param Target The target Game Object of the script.
        virtual void OnStop(GameObject* Target) {}

        /// @brief Will be called when the Game Object was about to update.
        /// @param Target The target Game Object of the script.
        virtual void OnEarlyUpdate(GameObject* Target) {}
        /// @brief Will be called when the Game Object is updating.
        /// @param Target The target Game Object of the script.
        virtual void OnUpdate(GameObject* Target) {}
        /// @brief Will be called when the Game Object done updating.
        /// @param Target The target Game Object of the script.
        virtual void OnLateUpdate(GameObject* Target) {}
    };

    /// @brief The Game Object Event Caller, use for Game Object event.
    typedef EventCaller<GameObject, EventArgs> GameObjectEventCaller;
    /// @brief The Game Object Render Event Caller, use for Game Object render event.
    typedef EventCaller<GameObject, RenderEventArgs> GameObjectRenderEventCaller;
    /// @brief The Game Object Key Event Caller, use for Game Object keyboard event.
    typedef EventCaller<GameObject, KeyEventArgs> GameObjectKeyEventCaller;
    /// @brief The Game Object Mouse Event Caller, use for Game Object mouse button event.
    typedef EventCaller<GameObject, MouseButtonEventArgs> GameObjectMouseEventCaller;
    /// @brief The Game Object Mouse Wheel Event Caller, use for Game Object mouse wheel event.
    typedef EventCaller<GameObject, MouseWheelEventArgs> GameObjectMouseWheelEventCaller;
    /// @brief The Game Object Mouse Motion Event Caller, use for Game Object mouse motion event.
    typedef EventCaller<GameObject, MouseMotionEventArgs> GameObjectMouseMotionEventCaller;

    /// @brief The Game Object class, represent an object use for game.
    class GameObject {
    private:
        GameObject* __parent = nullptr;
        std::unordered_set<GameObject*> __childs;
        std::unordered_map<size_t, GameScript*> __scripts;

        static bool __is_destroy_all;
        static std::unordered_set<GameObject*> __created_game_objs;
    protected:
        /// @brief Occurred when the Game Object is requesting update (usually on every frame).
        virtual void OnUpdate() {}
        /// @brief Occurred when the Game Object is requesting rendering (usually after updating).
        virtual void OnRender(RenderEventArgs* args) {
            if (!RenderBackground)
                return;
            Renderer::SetDrawColor(BackgroundColor);
            Renderer::FillRectangle(args->TargetArea);
            if (BackgroundTexture)
                Renderer::DrawTexture(args->TargetArea, BackgroundTexture);
        }
        /// @brief Occurred when a key is being pressed while the Window has input focus.
        virtual void OnKeyDown(KeyEventArgs* args) {}
        /// @brief Occurred when a key is being released while the Window has input focus.
        virtual void OnKeyUp(KeyEventArgs* args) {}
        /// @brief Occurred when a mouse button is being pressed while the Window has input focus.
        virtual void OnGlobalMouseDown(MouseButtonEventArgs* args) {}
        /// @brief Occurred when a mouse button is being released while the Window has input focus.
        virtual void OnGlobalMouseUp(MouseButtonEventArgs* args) {}
        /// @brief Occurred when the mouse wheel is being scrolled while the Window has input focus.
        virtual void OnMouseScroll(MouseWheelEventArgs* args) {}
        /// @brief Occurred when the mouse cursor is moved while the Window has input focus.
        virtual void OnGlobalMouseMoved(MouseMotionEventArgs* args) {}
        /// @brief Occurred when the mouse button is being pressed while the cursor was inside the
        /// Game Object area and the Window has input focus.
        virtual void OnMouseDown(MouseButtonEventArgs* args) {}
        /// @brief Occurred when the mouse button is being released while the cursor was inside the
        /// Game Object area and the Window has input focus.
        virtual void OnMouseUp(MouseButtonEventArgs* args) {}
        /// @brief Occurred when the mouse cursor is moved while the cursor was inside the Game Object
        /// area and the Window has input focus.
        virtual void OnMouseMoved(MouseMotionEventArgs* args) {}
    public:
        /// @brief If this false, the Game Object will not receive event from the Application. Default is true.
        bool Enabled = true;
        /// @brief If this true (default), will render the background of the Game Object.
        bool RenderBackground = true;
        /// @brief If this true (default), the Game Object can receive input event from the Application (from keyboard and mouse).
        bool HandleInput = true;
        /// @brief The name of the Game Object. Default is "Game Object".
        std::string Name = "Game Object";
        /// @brief The position of the Game Object (or the local position related to it parent). Default is Point::Zero.
        Point Position = Point::Zero;
        /// @brief The size of the Game Object. Default is Size::Zero.
        Engine::Size Size = Engine::Size::Zero;
        /// @brief The alignment of the Game Object related to it parent. Default is RectangleAlignment::TopLeft.
        RectangleAlignment Alignment = RectangleAlignment::TopLeft;

        /// @brief The background color of the Game Object. Default is Color::Empty.
        Color BackgroundColor = Color::Empty;
        /// @brief The background texture of the Game Object. Default is nullptr mean there's no Texture.
        Texture* BackgroundTexture = nullptr;

        /// @brief Create a new Game Object. Should be created with 'new' keyword (new GameObject()).
        GameObject() { GameObject::__created_game_objs.insert(this); }
        virtual ~GameObject();

        ENGINE_NOT_COPYABLE(GameObject)
        ENGINE_NOT_ASSIGNABLE(GameObject)

        /// @brief Occurred when the Game Object is requesting update (usually on every frame).
        GameObjectEventCaller UpdateEvent;
        /// @brief Occurred when the Game Object is requesting rendering (usually after updating).
        GameObjectRenderEventCaller RenderEvent;
        /// @brief Occurred when a key is being pressed while the Window has input focus.
        GameObjectKeyEventCaller KeyDownEvent;
        /// @brief Occurred when a key is being released while the Window has input focus.
        GameObjectKeyEventCaller KeyUpEvent;
        /// @brief Occurred when a mouse button is being pressed while the Window has input focus.
        GameObjectMouseEventCaller GlobalMouseDownEvent;
        /// @brief Occurred when a mouse button is being released while the Window has input focus.
        GameObjectMouseEventCaller GlobalMouseUpEvent;
        /// @brief Occurred when the mouse wheel is being scrolled while the Window has input focus.
        GameObjectMouseWheelEventCaller MouseScrollEvent;
        /// @brief Occurred when the mouse cursor is moved while the Window has input focus.
        GameObjectMouseMotionEventCaller GlobalMouseMovedEvent;
        /// @brief Occurred when the mouse button is being pressed while the cursor was inside the
        /// Game Object area and the Window has input focus.
        GameObjectMouseEventCaller MouseDownEvent;
        /// @brief Occurred when the mouse button is being released while the cursor was inside the
        /// Game Object area and the Window has input focus.
        GameObjectMouseEventCaller MouseUpEvent;
        /// @brief Occurred when the mouse cursor is moved while the cursor was inside the Game Object
        /// area and the Window has input focus.
        GameObjectMouseMotionEventCaller MouseMovedEvent;

        /// @brief Get the area of the Game Object (or the local area related to it parent).
        /// @return The Rectangle represent the area of the Game Object.
        Rectangle GetArea() const { return Rectangle(Position, Size); }

        /// @brief Set the parent of this Game Object.
        /// @param parent The parent to set, or nullptr to detach the Game Object from it parent.
        void SetParent(GameObject* parent) {
            if (__parent) 
                __parent->__childs.erase(this);
            __parent = parent;
            if (parent)
                parent->__childs.insert(this);
        }
        /// @brief Get the parent of this Game Object.
        /// @return The parent of the Game Object, or nullptr if the Game Object has no parent.
        GameObject* GetParent() const { return __parent; }
        /// @brief Detach this Game Object from it parent.
        void DetachParent() { SetParent(nullptr); }

        /// @brief Check if the Game Object contain the given Game Object as child.
        /// @param child The Game Object to check.
        /// @param recursive If this true, will also check for the childs of each child of the Game Object recursively.
        /// Default is false.
        /// @return true if the Game Object is contain the given Game Object, false otherwise.
        bool IsContainChild(GameObject* child, bool recursive = false) const {
            if (!child) return false;
            if (!recursive) return __childs.count(child) != 0;
            for (GameObject* obj : __childs) {
                if (!obj) continue;
                if (obj == child) return true;
                if (obj->IsContainChild(child)) return true;
            }
            return false;
        }

        /// @brief Add a Game Object to this Game Object as child.
        /// @param child The Game Object to add.
        void AddChild(GameObject* child) { if (child) child->SetParent(this); }
        /// @brief Add a list of Game Objects to this Game Object as child.
        /// @param obj_list The list of Game Objects to add.
        void AddChild(std::initializer_list<GameObject*> obj_list) {
            for (GameObject* obj : obj_list)
                if (obj) obj->SetParent(this);
        }
        /// @brief Detach a child from the Game Object.
        /// @param child The child Game Object to remove.
        void DetachChild(GameObject* child) { child->SetParent(nullptr); }

        /// @brief Detach all child from the Game Object.
        void DetachAllChilds() {
            for (GameObject* child : __childs)
                if (child) child->__parent = nullptr;
            __childs.clear();
        }
        /// @brief Detach all child of the Game Object that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of childs removed.
        size_t DetachChildIf(const std::function<bool(GameObject*)>& predicate) {
            if (!predicate) return 0;
            std::vector<std::unordered_set<GameObject*>::iterator> remove_pos;
            for (auto ptr = __childs.begin(); ptr != __childs.end(); ++ptr) {
                GameObject* obj = *ptr;
                if (!obj) remove_pos.push_back(ptr);
                if (predicate(obj)) remove_pos.push_back(ptr);
            }

            size_t count = 0;
            for (auto& ptr :  remove_pos) {
                GameObject* obj = *ptr;
                if (obj) { obj->__parent = nullptr; count++; }
                __childs.erase(ptr);
            }

            return count;
        }

        /// @brief Execute an action for each child of the Game Object.
        /// @param action The action to execute.
        /// @return The number of childs that called with the given action.
        size_t ForEachChild(const std::function<void(GameObject*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (GameObject* obj : __childs)
                if (obj) { action(obj); count++; }

            return count;
        }
        /// @brief Execute an action for each child of the Game Object, if the Game Object is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of childs that called with the given action.
        size_t ForEachChildIf(const std::function<void(GameObject*)>& action, const std::function<bool(GameObject*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachChild(action);
            size_t count = 0;
            for (GameObject* obj : __childs) {
                if (!obj) continue;
                if (!predicate(obj)) continue;
                action(obj); count++;
            }

            return count;
        }

        /// @brief Find the first child with the given name in the Game Object.
        /// @param name The name to find.
        /// @return The first child with the given name, or nullptr if not found.
        GameObject* FindChild(const std::string& name) const {
            for (GameObject* obj : __childs) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first child in the Game Object that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first child that satisfied the given predicate, or nullptr if no child satisfied.
        GameObject* FindChildIf(const std::function<bool(GameObject*)>& predicate) const {
            if (!predicate) return nullptr;
            for (GameObject* obj : __childs) {
                if (!obj) continue;
                if (predicate(obj)) return obj;
            }
            return nullptr;
        }

        /// @brief Create and add a Game Script with the given type to the Game Object.
        /// @tparam GameScriptT The type of the Game Script to add, must be derived from GameScript.
        /// @return The newly created Game Script that added to the Game Object, or a Game Script from the Game Object
        /// if there's already a Game Script with the given type added to the Game Object.
        template <typename GameScriptT>
        typename std::enable_if<std::is_base_of<GameScript, GameScriptT>::value, GameScriptT*>::type AddScript() {
            size_t type_hash_code = typeid(GameScriptT).hash_code();
            GameScript* result = nullptr;
            if (__scripts.count(type_hash_code) != 0) {
                result = __scripts[type_hash_code];
                if (result) return (GameScriptT*)result;
            }
            result = (GameScript*)(new GameScriptT());
            __scripts[type_hash_code] = result;
            result->OnStart(this);
            return (GameScriptT*)result;
        }
        /// @brief Destroy and remove a Game Script with the given type from the Game Object.
        /// @tparam GameScriptT The type of the Game Script to add, must be derived from GameScript.
        template <typename GameScriptT>
        typename std::enable_if<std::is_base_of<GameScript, GameScriptT>::value>::type DestroyScript() {
            size_t type_hash_code = typeid(GameScriptT).hash_code();
            if (__scripts.count(type_hash_code) == 0)
                return;
            GameScript* script = __scripts[type_hash_code];
            if (script) { script->OnStop(this); delete script; }
            __scripts.erase(type_hash_code);
        }
        /// @brief Get a Game Script with the given type from the Game Object.
        /// @tparam GameScriptT The type of the Game Script to add, must be derived from GameScript.
        /// @return The Game Script from the Game Object with the given type, or nullptr if not found.
        template <typename GameScriptT>
        typename std::enable_if<std::is_base_of<GameScript, GameScriptT>::value, GameScriptT*>::type GetScript() {
            size_t type_hash_code = typeid(GameScriptT).hash_code();
            if (__scripts.count(type_hash_code) == 0)
                return nullptr;

            GameScript* result = __scripts[type_hash_code];
            if (!result) { __scripts.erase(type_hash_code); return nullptr; }
            return (GameScriptT*)result;
        }
        /// @brief Check if a Game Script with the given type is added to the Game Object.
        /// @tparam GameScriptT The type of the Game Script to add, must be derived from GameScript.
        /// @return true if there's a Game Script with the given type in the Game Object, false otherwise.
        template <typename GameScriptT>
        typename std::enable_if<std::is_base_of<GameScript, GameScriptT>::value, bool>::type IsContainScript() {
            size_t type_hash_code = typeid(GameScriptT).hash_code();
            if (__scripts.count(type_hash_code) == 0)
                return false;
            return (bool)__scripts[type_hash_code];
        }

        /// @brief Execute an action for each Game Script of the Game Object.
        /// @param action The action to execute.
        /// @return The number of Game Scripts that called with the given action.
        size_t ForEachScript(const std::function<void(GameScript*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (auto& pair : __scripts)
                if (pair.second) { action(pair.second); count++; }

            return count;
        }
        /// @brief Execute an action for each Game Script of the Game Object, if the Game Object is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Game Scripts that called with the given action.
        size_t ForEachScriptIf(const std::function<void(GameScript*)>& action, const std::function<bool(GameScript*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachScript(action);
            size_t count = 0;
            for (auto& pair : __scripts) {
                if (!pair.second) continue;
                if (!predicate(pair.second)) continue;
                action(pair.second); count++;
            }

            return count;
        }

        /// @brief Find the first Game Script in the Game Object that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Game Script that satisfied the given predicate, or nullptr if no Game Script satisfied.
        GameScript* FindScriptIf(const std::function<bool(GameScript*)>& predicate) const {
            if (!predicate) return nullptr;
            for (auto& pair : __scripts) {
                if (!pair.second) continue;
                if (predicate(pair.second)) return pair.second;
            }
            return nullptr;
        }



        /// @brief Raise the Update event to the Game Object.
        /// @param recursive If this true (default), will also raise the event on all of the Game Object child recursively
        /// if it's enabled.
        void RaiseUpdateEvent(bool recursive = true) {
            for (auto& pair : __scripts)
                if (pair.second) pair.second->OnEarlyUpdate(this);

            OnUpdate();
            for (auto& pair : __scripts)
                if (pair.second) pair.second->OnUpdate(this);
            UpdateEvent.Call(this);
            if (!recursive) return;
            for (GameObject* child : __childs)
                if (child) child->RaiseUpdateEvent();
            
            for (auto& pair : __scripts)
                if (pair.second) pair.second->OnLateUpdate(this);
        }
        /// @brief Raise the Render event to the Game Object.
        /// @param recursive If this true (default), will also raise the event on all of the Game Object child recursively
        /// if it's enabled. The given args will be adjust base on each Game Object.
        void RaiseRenderEvent(RenderEventArgs* args, bool recursive = true) {
            RenderEventArgs* tmp = !args ? new RenderEventArgs() : args;
            OnRender(tmp); RenderEvent.Call(this, tmp);
            if (recursive) {
                for (GameObject* child : __childs) {
                    if (!child) continue;
                    if (!child->Enabled) continue;

                    RenderEventArgs child_args(*tmp);
                    child_args.TargetArea = child_args.TargetArea.LocalToGlobal(child->GetArea(), child->Alignment);
                    child->RaiseRenderEvent(&child_args, recursive);
                }
            }
            if (tmp && !args) delete tmp;
        }
        /// @brief Raise the Key Down event to the Game Object.
        /// @param recursive If this true (default), will also raise the event on all of the Game Object child recursively
        /// if it's enabled.
        void RaiseKeyDownEvent(KeyEventArgs* args, bool recursive = true) {
            KeyEventArgs* tmp = !args ? new KeyEventArgs() : args;
            OnKeyDown(tmp); KeyDownEvent.Call(this, tmp);
            if (recursive) {
                for (GameObject* child : __childs) {
                    if (!child) continue;
                    if (!child->Enabled || !child->HandleInput) continue;

                    child->RaiseKeyDownEvent(tmp, recursive);
                }
            }
            if (tmp && !args) delete tmp;
        }
        /// @brief Raise the Key Up event to the Game Object.
        /// @param recursive If this true (default), will also raise the event on all of the Game Object child recursively
        /// if it's enabled.
        void RaiseKeyUpEvent(KeyEventArgs* args, bool recursive = true) {
            KeyEventArgs* tmp = !args ? new KeyEventArgs() : args;
            OnKeyUp(tmp); KeyUpEvent.Call(this, tmp);
            if (recursive) {
                for (GameObject* child : __childs) {
                    if (!child) continue;
                    if (!child->Enabled || !child->HandleInput) continue;

                    child->RaiseKeyUpEvent(tmp, recursive);
                }
            }
            if (tmp && !args) delete tmp;
        }
        /// @brief Raise the Mouse Scroll event to the Game Object.
        /// @param recursive If this true (default), will also raise the event on all of the Game Object child recursively
        /// if it's enabled.
        void RaiseMouseScrollEvent(MouseWheelEventArgs* args, bool recursive = true) {
            MouseWheelEventArgs* tmp = !args ? new MouseWheelEventArgs() : args;
            OnMouseScroll(tmp); MouseScrollEvent.Call(this, tmp);
            if (recursive) {
                for (GameObject* child : __childs) {
                    if (!child) continue;
                    if (!child->Enabled || !child->HandleInput) continue;

                    child->RaiseMouseScrollEvent(tmp, recursive);
                }
            }
            if (tmp && !args) delete tmp;
        }

        /// @brief Raise the Mouse Down event to the Game Object.
        /// @param recursive If this true (default), will also raise the event on all of the Game Object child recursively
        /// if it's enabled. The given args will be adjust base on each Game Object.
        void RaiseMouseDownEvent(MouseButtonEventArgs* args, bool recursive = true) {
            MouseButtonEventArgs* tmp = !args ? new MouseButtonEventArgs() : args;
            OnGlobalMouseDown(tmp); GlobalMouseDownEvent.Call(this, tmp);
            if (Rectangle(Point::Zero, Size).IsContain(tmp->LocalPosition)) {
                OnMouseDown(tmp); MouseDownEvent.Call(this, tmp);
            }
            if (recursive) {
                for (GameObject* child : __childs) {
                    if (!child) continue;
                    if (!child->Enabled || !child->HandleInput) continue;

                    MouseButtonEventArgs child_args(*tmp);
                    Rectangle child_area = GetArea().LocalToGlobal(child->GetArea(), child->Alignment);
                    child_args.LocalPosition -= child_area.TopLeft();

                    child->RaiseMouseDownEvent(&child_args, recursive);
                }
            }
            if (tmp && !args) delete tmp;
        }
        /// @brief Raise the Mouse Up event to the Game Object.
        /// @param recursive If this true (default), will also raise the event on all of the Game Object child recursively
        /// if it's enabled. The given args will be adjust base on each Game Object.
        void RaiseMouseUpEvent(MouseButtonEventArgs* args, bool recursive = true) {
            MouseButtonEventArgs* tmp = !args ? new MouseButtonEventArgs() : args;
            OnGlobalMouseUp(tmp); GlobalMouseUpEvent.Call(this, tmp);
            if (Rectangle(Point::Zero, Size).IsContain(tmp->LocalPosition)) {
                OnMouseUp(tmp); MouseUpEvent.Call(this, tmp);
            }
            if (recursive) {
                for (GameObject* child : __childs) {
                    if (!child) continue;
                    if (!child->Enabled || !child->HandleInput) continue;

                    MouseButtonEventArgs child_args(*tmp);
                    Rectangle child_area = GetArea().LocalToGlobal(child->GetArea(), child->Alignment);
                    child_args.LocalPosition -= child_area.TopLeft();

                    child->RaiseMouseUpEvent(&child_args, recursive);
                }
            }
            if (tmp && !args) delete tmp;
        }
        /// @brief Raise the Mouse Moved event to the Game Object.
        /// @param recursive If this true (default), will also raise the event on all of the Game Object child recursively
        /// if it's enabled. The given args will be adjust base on each Game Object.
        void RaiseMouseMovedEvent(MouseMotionEventArgs* args, bool recursive = true) {
            MouseMotionEventArgs* tmp = !args ? new MouseMotionEventArgs() : args;
            OnGlobalMouseMoved(tmp); GlobalMouseMovedEvent.Call(this, tmp);
            if (Rectangle(Point::Zero, Size).IsContain(tmp->LocalPosition)) {
                OnMouseMoved(tmp); MouseMovedEvent.Call(this, tmp);
            }
            if (recursive) {
                for (GameObject* child : __childs) {
                    if (!child) continue;
                    if (!child->Enabled || !child->HandleInput) continue;

                    MouseMotionEventArgs child_args(*tmp);
                    Rectangle child_area = GetArea().LocalToGlobal(child->GetArea(), child->Alignment);
                    child_args.LocalPosition -= child_area.TopLeft();

                    child->RaiseMouseMovedEvent(&child_args, recursive);
                }
            }
            if (tmp && !args) delete tmp;
        }

        std::unordered_set<GameObject*>::iterator begin() { return __childs.begin(); }
        std::unordered_set<GameObject*>::const_iterator begin() const { return __childs.begin(); }
        std::unordered_set<GameObject*>::iterator end() { return __childs.end(); }
        std::unordered_set<GameObject*>::const_iterator end() const { return __childs.end(); }


        /// @brief Execute an action for each created Game Object.
        /// @param action The action to execute.
        /// @return The number of Game Object that called with the given action.
        static size_t ForEachGameObject(const std::function<void(GameObject*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (GameObject* scene : GameObject::__created_game_objs)
                if (scene) { action(scene); count++; }

            return count;
        }
        /// @brief Execute an action for each created Game Object, if the Game Object is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Game Object that called with the given action.
        static size_t ForEachGameObjectIf(const std::function<void(GameObject*)>& action, const std::function<bool(GameObject*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachGameObject(action);
            size_t count = 0;
            for (GameObject* scene : GameObject::__created_game_objs) {
                if (!scene) continue;
                if (!predicate(scene)) continue;
                action(scene); count++;
            }

            return count;
        }
        /// @brief Find the first created Game Object with the given name.
        /// @param name The name to find.
        /// @return The first Game Object with the given name, or nullptr if not found.
        static GameObject* FindGameObject(const std::string& name) {
            for (GameObject* obj : GameObject::__created_game_objs) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first created Game Object that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Game Object that satisfied the given predicate, or nullptr if no Game Object satisfied.
        static GameObject* FindGameObjectIf(const std::function<bool(GameObject*)>& predicate) {
            if (!predicate) return nullptr;
            for (GameObject* obj : GameObject::__created_game_objs) {
                if (!obj) continue;
                if (predicate(obj)) return obj;
            }
            return nullptr;
        }

        /// @brief Destroy all created Game Objects, this will be called on Engine::Deinitialize().
        static void DestoryAllCreatedGameObjects();
    };

    /// @brief The Game Scene struct, provide a collection of Game Object. This can also use to manage Game Scenes.
    struct GameScene final {
    private:
        std::vector<std::unordered_set<GameObject*>> __layers = std::vector<std::unordered_set<GameObject*>>(1);

        static bool __is_initialize;
        static GameScene* __curr_scene;
        static std::unordered_set<GameScene*> __created_scenes;
    public:
        /// @brief The name of the Game Scene. Default is "Game Scene".
        std::string Name = "Game Scene";
        /// @brief The background color of the Game Scene. Default is Color::Empty.
        Color BackgroundColor = Color::Empty;
        /// @brief The background texture of the Game Scene. Default is nullptr mean there's no background.
        Texture* BackgroundTexture = nullptr;

        /// @brief Create a new empty Game Scene. Should be created with 'new' keyword (new GameScene()).
        GameScene() {
            if (!GameScene::__is_initialize && !GameScene::IsInitialized())
                throw std::runtime_error("The Game Scene must be initialized successfully before creating a Game Scene!");
            __created_scenes.insert(this);
        }
        
        GameScene(const GameScene& scene) : Name(scene.Name), BackgroundColor(scene.BackgroundColor),
            BackgroundTexture(scene.BackgroundTexture), __layers(scene.__layers) {

            if (!GameScene::__is_initialize && !GameScene::IsInitialized())
                throw std::runtime_error("The Game Scene must be initialized successfully before creating a Game Scene!");
            __created_scenes.insert(this);
        }
        GameScene(GameScene* scene) : Name(scene->Name), BackgroundColor(scene->BackgroundColor),
            BackgroundTexture(scene->BackgroundTexture), __layers(scene->__layers) {
                
            if (!GameScene::__is_initialize && !GameScene::IsInitialized())
                throw std::runtime_error("The Game Scene must be initialized successfully before creating a Game Scene!");
            __created_scenes.insert(this);
        }
        
        virtual ~GameScene() {
            if (!GameScene::__is_initialize && GameScene::IsInitialized()) {
                if (GameScene::__curr_scene == this)
                    GameScene::__curr_scene = new GameScene();
                GameScene::__created_scenes.erase(this);
            }
        }

        /// @brief Get the number of layers of the Game Scene.
        /// @return The number of layers of the Game Scene.
        size_t CountLayer() const { return __layers.size(); }
        /// @brief Add a new layer to the Game Scene.
        /// @param index The index of the layer in the Game Scene to add. If this value is negative (which is default), 
        /// will append to the end (top layer).
        /// @return The index of the new layer.
        int AddLayer(int index = -1) {
            int target_index = (index < 0 || index >= __layers.size()) ? __layers.size() : index;
            __layers.insert(__layers.begin() + target_index, std::unordered_set<Engine::GameObject*>());
            return target_index;
        }
        /// @brief Remove a layer from the Game Scene. This will removed all Game Object in that layers.
        /// @param index The index of the layer to remove. If this value is negative (which is default), 
        /// will remove the last layer (top layer).
        void RemoveLayer(int index = -1) {
            if (__layers.size() == 1) { __layers[0].clear(); return; }
            
            int target_index = (index < 0 || index >= __layers.size()) ? __layers.size() - 1 : index;
            __layers.erase(__layers.begin() + target_index);
        }
        /// @brief Get the layer that the given added Game Object currently in the Game Scene. 
        /// @param obj The added Game Object in the Game Scene.
        /// @return The index of the layer in the Game Scene that contain the given Game Object, or -1 if the Game Scene
        /// didn't contain it.
        int GetGameObjectLayer(GameObject* obj) const {
            if (!obj) return -1;
            auto ptr = __layers.begin();
            for (int i = 0; i < __layers.size(); ++i, ++ptr)
                if ((*ptr).count(obj) != 0) return i;
            return -1;
        }

        /// @brief Get the number of Game Object in the Game Scene.
        /// @return The number of Game Object in the Game Scene.
        size_t Count() const {
            size_t result = 0;
            for (auto& layer : __layers)
                result += layer.size();
            return result;
        }
        /// @brief Get the number of Game Object in a Game Scene layer.
        /// @param layer_index The index of the layer to query.
        /// @return The number of Game Object in the Game Scene layer. Will also return 0 on failed (usually on negative or out of range).
        size_t Count(int layer_index) const { return (layer_index < 0 || layer_index >= __layers.size()) ? __layers[layer_index].size() : 0; }

        /// @brief Execute an action for each Game Object in a Game Scene layer.
        /// @param action The action to execute.
        /// @param layer_index The index of the layer in the Game Scene.
        /// @return The number of Game Object that called with the given action.
        size_t ForEachInLayer(const std::function<void(GameObject*)>& action, int layer_index) {
            if (!action) return 0;
            if ((layer_index < 0 || layer_index >= __layers.size()))
                return 0;
            size_t count = 0;
            for (GameObject* obj : __layers[layer_index])
                if (obj) { action(obj); ++count; }
            
            return count;
        }
        /// @brief Execute an action for each Game Object in a Game Scene layer, if the Game Object is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @param layer_index The index of the layer in the Game Scene.
        /// @return The number of Game Object that called with the given action.
        size_t ForEachInLayerIf(const std::function<void(GameObject*)>& action, const std::function<bool(GameObject*)>& predicate, int layer_index) {
            if (!action) return 0;
            if (layer_index < 0 || layer_index >= __layers.size())
                return 0;
            if (!predicate) return ForEachInLayer(action, layer_index);
            size_t count = 0;
            for (GameObject* obj : __layers[layer_index]) {
                if (!obj) continue;
                if (!predicate(obj)) continue;
                action(obj); ++count;
            }
            return count;
        }

        /// @brief Find the first Game Object with the given name in a Game Scene layer.
        /// @param name The name to find.
        /// @param layer_index The index of the layer in the Game Scene.
        /// @return The first Game Object with the given name, or nullptr if not found.
        GameObject* FindInLayer(const std::string& name, int layer_index) const {
            if (layer_index < 0 || layer_index >= __layers.size())
                return 0;
            for (GameObject* obj : __layers[layer_index]) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first Game Object in a Game Scene layer that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @param layer_index The index of the layer in the Game Scene.
        /// @return The first Game Object that satisfied the given predicate, or nullptr if no Game Object satisfied.
        GameObject* FindInLayerIf(const std::function<bool(GameObject*)>& predicate, int layer_index) const {
            if (!predicate) return nullptr;
            if (layer_index < 0 || layer_index >= __layers.size())
                return 0;
            for (GameObject* obj : __layers[layer_index]) {
                if (!obj) continue;
                if (predicate(obj))
                    return obj;
            }
            return nullptr;
        }

        /// @brief Remove all Game Object from a Game Scene layer.
        /// @param layer_index The index of the layer in the Game Scene.
        void ClearLayer(int layer_index) {
            if (layer_index < 0 || layer_index >= __layers.size())
                return;
            __layers[layer_index].clear();
        }

        /// @brief Swap two layer contents.
        /// @param layer_index1 The index of the first layer to swap.
        /// @param layer_index2 The index of the second layer to swap.
        void SwapLayer(int layer_index1, int layer_index2) {
            if (layer_index1 == layer_index2)
                return;
            if (layer_index1 < 0 || layer_index1 >= __layers.size())
                return;
            if (layer_index2 < 0 || layer_index2 >= __layers.size())
                return;
                
            __layers[layer_index1].swap(__layers[layer_index2]);
        }

        /// @brief Check if a Game Scene layer contain the given Game Object.
        /// @param obj The Game Object to check.
        /// @param recursive If this true, will also check for the child of each Game Object in the Game Scene recursively.
        /// Default is false.
        /// @return true if the Game Scene is contain the given Game Object, false otherwise.
        bool IsLayerContain(GameObject* obj, int layer_index, bool recursive = false) const {
            if (!obj) return false;
            if (layer_index < 0 || layer_index >= __layers.size())
                return false;
            if (!recursive) return __layers[layer_index].count(obj) != 0;
            for (GameObject* __obj : __layers[layer_index]) {
                if (!__obj) continue;
                if (__obj == obj) return true;
                if (__obj->IsContainChild(obj)) return true;
            }
            return false;
        }


        /// @brief Add a Game Object to the Game Scene.
        /// @param obj The Game Object to add. If the Game Object is already in the Game Scene, will just re-added the Game Object
        /// to the given layer.
        /// @param layer The index of the layer in the Game Scene to add. If this value is negative (which is default),
        /// will added to the last layer (top layer).
        void Add(GameObject* obj, int layer = -1) {
            if (!obj) return;
            int curr_layer = (layer < 0 || layer >= __layers.size()) ? __layers.size() - 1 : layer;
            auto ptr = __layers.begin();

            for (int i = 0; i < __layers.size(); ++i, ++ptr)
                (*ptr).erase(obj);
            __layers[curr_layer].insert(obj);
        }

        /// @brief Check if the Game Scene contain the given Game Object.
        /// @param obj The Game Object to check.
        /// @param recursive If this true, will also check for the child of each Game Object in the Game Scene recursively.
        /// Default is false.
        /// @return true if the Game Scene is contain the given Game Object, false otherwise.
        bool IsContain(GameObject* obj, bool recursive = false) const {
            if (!obj) return false;
            for (auto& layer : __layers) {
                if (layer.count(obj) != 0)
                    return true;
                if (!recursive)
                    continue;
                for (GameObject* __obj : layer) {
                    if (!__obj) continue;
                    if (__obj->IsContainChild(obj)) return true;
                }
            }
            return false;
        }

        /// @brief Remove a Game Object from the Game Scene.
        /// @param obj The Game Object to remove.
        void Remove(GameObject* obj) {
            if (!obj) return;
            for (auto& layer : __layers)
                layer.erase(obj);
        }
        /// @brief Remove all Game Object from the Game Scene.
        void Clear() {
            for (auto& layer : __layers)
                layer.clear();
        }
        /// @brief Remove all Game Object in the Game Scene that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Game Object removed.
        size_t RemoveIf(const std::function<bool(GameObject*)>& predicate) {
            if (!predicate) return 0;
            size_t count = 0;
            for (auto& layer : __layers) {
                std::list<GameObject*> remove_objs;
                for (GameObject* obj : layer) {
                    if (!obj) remove_objs.push_back(obj);
                    if (predicate(obj)) remove_objs.push_back(obj);
                }

                for (GameObject* obj : remove_objs) {
                    if (obj) ++count;
                    layer.erase(obj);
                }
            }

            return count;
        }

        /// @brief Execute an action for each Game Object in the Game Scene.
        /// @param action The action to execute.
        /// @return The number of Game Object that called with the given action.
        size_t ForEach(const std::function<void(GameObject*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (auto& layer : __layers) {
                for (GameObject* obj : layer)
                    if (obj) { action(obj); ++count; }
            }

            return count;
        }
        /// @brief Execute an action for each Game Object in the Game Scene, if the Game Object is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Game Object that called with the given action.
        size_t ForEachIf(const std::function<void(GameObject*)>& action, const std::function<bool(GameObject*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEach(action);
            size_t count = 0;
            for (auto& layer : __layers) {
                for (GameObject* obj : layer) {
                    if (!obj) continue;
                    if (!predicate(obj)) continue;
                    action(obj); ++count;
                }
            }

            return count;
        }

        /// @brief Find the first Game Object with the given name in the Game Scene.
        /// @param name The name to find.
        /// @return The first Game Object with the given name, or nullptr if not found.
        GameObject* Find(const std::string& name) const {
            for (auto& layer : __layers) {
                for (GameObject* obj : layer) {
                    if (!obj) continue;
                    if (obj->Name == name) return obj;
                }
            }

            return nullptr;
        }
        /// @brief Find the first Game Object in the Game Scene that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Game Object that satisfied the given predicate, or nullptr if no Game Object satisfied.
        GameObject* FindIf(const std::function<bool(GameObject*)>& predicate) const {
            if (!predicate) return nullptr;
            for (auto& layer : __layers) {
                for (GameObject* obj : layer) {
                    if (!obj) continue;
                    if (predicate(obj)) return obj;
                }
            }
            return nullptr;
        }



        /// @brief Get the current Game Scene of the game.
        /// @return The current Game Scene, or nullptr if the Game Scene wasn't initialized successfully.
        static GameScene* GetCurrentScene() {
            if (!GameScene::IsInitialized())
                return nullptr;
            return __curr_scene;
        }
        /// @brief Set the current Game Scene of the game, the Game Scene must initialized successfully.
        /// @param scene The Game Scene to set. If this null, will do nothing.
        static void SetCurrentScene(GameScene* scene) {
            if (GameScene::IsInitialized() && scene)
                GameScene::__curr_scene = scene;
        }

        /// @brief Execute an action for each created Game Scene.
        /// @param action The action to execute.
        /// @return The number of Game Scene that called with the given action.
        static size_t ForEachScene(const std::function<void(GameScene*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (GameScene* scene : GameScene::__created_scenes)
                if (scene) { action(scene); count++; }

            return count;
        }
        /// @brief Execute an action for each created Game Scene, if the Game Scene is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Game Scene that called with the given action.
        static size_t ForEachSceneIf(const std::function<void(GameScene*)>& action, const std::function<bool(GameScene*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachScene(action);
            size_t count = 0;
            for (GameScene* scene : GameScene::__created_scenes) {
                if (!scene) continue;
                if (!predicate(scene)) continue;
                action(scene); count++;
            }

            return count;
        }
        /// @brief Find the first created Game Scene with the given name.
        /// @param name The name to find.
        /// @return The first Game Scene with the given name, or nullptr if not found.
        static GameScene* FindScene(const std::string& name) {
            for (GameScene* obj : GameScene::__created_scenes) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first created Game Scene that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Game Scene that satisfied the given predicate, or nullptr if no Game Scene satisfied.
        static GameScene* FindSceneIf(const std::function<bool(GameScene*)>& predicate) {
            if (!predicate) return nullptr;
            for (GameScene* obj : GameScene::__created_scenes) {
                if (!obj) continue;
                if (predicate(obj)) return obj;
            }
            return nullptr;
        }

        /// @brief Check if the Game Scene is initialized successfully.
        /// @return true if the Game Scene is initialized successfully, false otherwise.
        static bool IsInitialized() { return GameScene::__curr_scene && !GameScene::__created_scenes.empty(); }
        /// @brief Initialize (or re-initialize) the Game Scene (this will destroy all previous created Game Scene),
        /// this will be called on Engine::Initialize().
        /// @return true on success, false on failure.
        static bool Initialize() {
            try {
                GameScene::__is_initialize = true;
                for (GameScene* scene : GameScene::__created_scenes)
                    if (scene) delete scene;
                GameScene::__created_scenes.clear();
                GameScene::__curr_scene = new GameScene();

                GameScene::__created_scenes.insert(__curr_scene);
                GameScene::__is_initialize = false;
                
                return true;
            }
            catch (std::exception&) {
                return false;
            }
        }
        /// @brief Deinitialize the Game Scene (this will destroy all created Game Scene),
        /// this will be called on Engine::Deinitialize().
        static void Deinitialize() { 
            GameScene::__is_initialize = true;
            for (GameScene* scene : GameScene::__created_scenes)
                if (scene) delete scene;
            GameScene::__created_scenes.clear();
            GameScene::__curr_scene = nullptr;
            GameScene::__is_initialize = false;
        }
    };

}

bool Engine::GameObject::__is_destroy_all = false;
std::unordered_set<Engine::GameObject*> Engine::GameObject::__created_game_objs = std::unordered_set<Engine::GameObject*>();

bool Engine::GameScene::__is_initialize = false;
Engine::GameScene* Engine::GameScene::__curr_scene = nullptr;
std::unordered_set<Engine::GameScene*> Engine::GameScene::__created_scenes = std::unordered_set<Engine::GameScene*>();

Engine::GameObject::~GameObject() {
    DetachAllChilds();
    DetachParent();
    if (!GameObject::__is_destroy_all) {
        for (auto& pair : __scripts)
            if (pair.second) { pair.second->OnStop(this); delete pair.second; }
        __scripts.clear();
        GameObject::__created_game_objs.erase(this);
        GameScene::ForEachScene(
            [this](GameScene* scene){ scene->Remove(this); }
        );
    }
}

void Engine::GameObject::DestoryAllCreatedGameObjects() {
    GameObject::__is_destroy_all = true;
    for (GameObject* obj : GameObject::__created_game_objs)
        if (obj) delete obj;
    GameObject::__created_game_objs.clear();
    GameScene::ForEachScene([](GameScene* scene){ scene->Clear(); });
    GameObject::__is_destroy_all = false;
}

#endif // __ENGINE_GAMEOBJECT_H__