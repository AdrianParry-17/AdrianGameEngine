#ifndef __ENGINE_UIGAMEOBJECT_H__
#define __ENGINE_UIGAMEOBJECT_H__

#include "Engine_GameObject.h"
#include "Engine_Font.h"

namespace Engine {
    /// @brief The Label Game Object, provide a game object that can be treated as an label.
    class LabelGameObject : public GameObject {
    protected:
        void OnRender(Engine::RenderEventArgs* args) override {
            if (!Text.empty() && Font) {
                if (Multiline)
                    Font->RenderMultiline(Text, args->TargetArea.TopLeft(), ForegroundColor);
                else
                    Font->RenderSingleLine(Text, args->TargetArea.TopLeft(), ForegroundColor);
            }
        }
    public:
        /// @brief The text of the Label Game Object. Default is an empty string.
        std::string Text = "";
        /// @brief The Font use to render the Lable Game Object text. Default is nullptr mean there hasn't use a font.
        Engine::Font* Font = nullptr;
        /// @brief The foreground color (or the mod color use when render text with the given font) of the Label Game Object.
        /// Default is Color::Empty.
        Color ForegroundColor = Color::Empty;
        /// @brief If this true, will render the text of the label with multiline mode. Default is false.
        bool Multiline = false;

        LabelGameObject() = default;
        virtual ~LabelGameObject() {}

        ENGINE_NOT_COPYABLE(LabelGameObject)
        ENGINE_NOT_ASSIGNABLE(LabelGameObject)
    };
    
    /// @brief The TTF Label Game Object, provide a game object that can be treated as a label. This use TTF Font for rendering
    /// text.
    class TTFLabelGameObject : public GameObject {
    private:
        std::string __text = "";
        Texture* __text_texture = nullptr;
    protected:
        void OnUpdate() override {
            if (AutoSize && __text_texture) {
                if (__text_texture->IsAvaliable())
                    Size = __text_texture->GetSize();
            }
        }
        void OnRender(Engine::RenderEventArgs* args) override {
            GameObject::OnRender(args);
            if (__text_texture) {
                __text_texture->SetColorMod(ForegroundColor);
                Renderer::DrawTextureUnscaled(args->TargetArea, __text_texture);
                __text_texture->SetColorMod(KnownColor::White);
            }
        }
    public:
        /// @brief The font of the TTF Label Game Object. Default is nullptr mean there's none.
        TTFFont* Font = nullptr;
        /// @brief The foreground color of the text of the TTF Label Game Object. Default is Color::Empty.
        Color ForegroundColor = Color::Empty;
        /// @brief If this true, will automatically adjust the Game Object size based on it text texture. Default is false.
        bool AutoSize = false;

        TTFLabelGameObject() = default;
        virtual ~TTFLabelGameObject() {
            if (__text_texture)
                delete __text_texture;
            __text_texture = nullptr;
        }

        ENGINE_NOT_COPYABLE(TTFLabelGameObject)
        ENGINE_NOT_ASSIGNABLE(TTFLabelGameObject)

        /// @brief Get the required size of the TTF Label Game Object based on the text texture.
        /// Notice that the TTF Label Game Object must be updated it text texture before this can be use.
        /// @return The required size of the TTF Label Game Object, or Size::Zero on failure.
        Engine::Size GetRequiredSize() const { return __text_texture ? __text_texture->GetSize() : Engine::Size::Zero; }

        /// @brief Update the texture of the text of the TTF Label Game Object.
        void UpdateTextTexture() {
            if (__text_texture)
                delete __text_texture;
            if (!Font) { __text_texture = nullptr; return; }
            __text_texture = Font->RenderToTexture(__text, Color(255, 255, 255, 255));
        }

        /// @brief Set the text of the label.
        /// @param Text The text to set.
        void SetText(const std::string& Text) {
            __text = Text;
            UpdateTextTexture();
        }
        /// @brief Get the text of the label.
        /// @return The text of the label.
        std::string GetText() const { return __text; }
    };

    /// @brief The Check Box Game Object, provide a game object that can be treated as a simple check box.
    class CheckBoxGameObject : public GameObject {
    protected:
        void OnRender(Engine::RenderEventArgs* args) override {
            GameObject::OnRender(args);
            if (Checked) {
                if (!CheckedTexture) return;
                if (!CheckedTexture->IsAvaliable()) return;
                Renderer::DrawTexture(args->TargetArea, CheckedTexture);
            }
            else {
                if (!UncheckedTexture) return;
                if (!UncheckedTexture->IsAvaliable()) return;
                Renderer::DrawTexture(args->TargetArea, UncheckedTexture);
            }
        }
        
        void OnMouseDown(Engine::MouseButtonEventArgs* args) override {
            if (Checked) {
                Checked = false;
                RaiseUncheckedEvent();
            }
            else {
                Checked = true;
                RaiseCheckedEvent();
            }
        }

        /// @brief Occurred when the check box is being checked.
        virtual void OnChecked() {}
        /// @brief Occurred when the check box is being unchecked.
        virtual void OnUnchecked() {}
    public:
        /// @brief The check state of the Check Box Game Object (true if checked, false otherwise).
        bool Checked = false;

        /// @brief The texture used for the Check Box Game Object when it is checked. Default is nullptr mean there's no texture.
        Texture* CheckedTexture = nullptr;
        /// @brief The texture used for the Check Box Game Object when it isn't checked. Default is nullptr mean there's no texture.
        Texture* UncheckedTexture = nullptr;

        /// @brief The Checked Event, occurred when the check box is being checked.
        GameObjectEventCaller CheckedEvent;
        /// @brief The Unchecked Event, occurred when the check box is being unchecked.
        GameObjectEventCaller UncheckedEvent;

        /// @brief Set the checked state of the Check Box Game Object. This will also raise the event.
        /// @param value The checked state to set.
        void SetChecked(bool value) {
            Checked = value;
            if (Checked)
                RaiseCheckedEvent();
            else
                RaiseUncheckedEvent();
        }

        /// @brief Raise the Checked event to the Check Box Game Object.
        void RaiseCheckedEvent() { OnChecked(); CheckedEvent.Call(this); }
        /// @brief Raise the Unchecked event to the Check Box Game Object.
        void RaiseUncheckedEvent() { OnUnchecked(); UncheckedEvent.Call(this); }
    };
    /// @brief The Button Game Object, provide a game object that can be treated as a button.
    class ButtonGameObject : public GameObject {
    private:
        bool __hovered = false, __clicked = false;
    protected:
        void OnRender(RenderEventArgs* args) override {
            if (RenderBackground) {
                if (__clicked && ClickedTexture) {
                    if (ClickedTexture->IsAvaliable()) {
                        Renderer::SetDrawColor(BackgroundColor);
                        Renderer::FillRectangle(args->TargetArea);
                        Renderer::DrawTexture(args->TargetArea, ClickedTexture);
                        return;
                    }
                }
                if (__hovered && HoveredTexture) {
                    if (HoveredTexture->IsAvaliable()) {
                        Renderer::SetDrawColor(BackgroundColor);
                        Renderer::FillRectangle(args->TargetArea);
                        Renderer::DrawTexture(args->TargetArea, HoveredTexture);
                        return;
                    }
                }
            }
            GameObject::OnRender(args);
        }

        void OnGlobalMouseMoved(MouseMotionEventArgs* args) override {
            bool hover = GetArea().IsContain(args->LocalPosition);
            if (!__hovered && hover) { OnMouseEnter(args); MouseEnterEvent.Call(this, args); }
            else if (__hovered && !hover) { OnMouseLeave(args); MouseLeaveEvent.Call(this, args); }
            __hovered = hover;
            GameObject::OnGlobalMouseMoved(args);
        }
        void OnGlobalMouseDown(MouseButtonEventArgs* args) override {
            __clicked = GetArea().IsContain(args->LocalPosition);
            GameObject::OnGlobalMouseDown(args);
        }
        void OnGlobalMouseUp(MouseButtonEventArgs* args) override {
            __clicked = false;
            GameObject::OnGlobalMouseUp(args);
        }

        /// @brief Occurred when the mouse enter the button area.
        virtual void OnMouseEnter(MouseMotionEventArgs* args) {}
        /// @brief Occurred when the mouse leave the button area.
        virtual void OnMouseLeave(MouseMotionEventArgs* args) {}
    public:
        /// @brief The texture of the button when it's being clicked. Default is nullptr mean there's none.
        Texture* ClickedTexture = nullptr;
        /// @brief The texture of the button when it's being hovered. Default is nullptr mean there's none.
        Texture* HoveredTexture = nullptr;

        /// @brief The Mouse Leave Event, occurred when the mouse leave the button area.
        GameObjectMouseMotionEventCaller MouseLeaveEvent;
        /// @brief The Mouse Enter Event, occurred when the mouse enter the button area.
        GameObjectMouseMotionEventCaller MouseEnterEvent;
    };
}

#endif // __ENGINE_UIGAMEOBJECT_H__