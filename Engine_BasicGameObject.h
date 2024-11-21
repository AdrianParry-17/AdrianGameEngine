#ifndef __ENGINE_BASICGAMEOBJECT_H__
#define __ENGINE_BASICGAMEOBJECT_H__

#include "Engine_GameObject.h"
#include "Engine_Imaging.h"
#include "Engine_Font.h"

namespace Engine {
    /// @brief The Layout Game Object class, use for rendering Game Object with layout texture (grayscale texture).
    class LayoutGameObject : public GameObject {
    protected:
        void OnRender(Engine::RenderEventArgs* args) override {
            GameObject::OnRender(args);
            if (LayoutTexture) {
                LayoutTexture->SetColorMod(LayoutColor);
                Renderer::DrawTexture(args->TargetArea, LayoutTexture);
                LayoutTexture->SetColorMod(Color(255, 255, 255, 255));
            }
        }
    public:
        /// @brief The layout texture of the Game Object to draw, should be grayscale. Default is nullptr mean
        /// there's no texture.
        Texture* LayoutTexture = nullptr;
        /// @brief The layout color use for the layout texture. Default is KnownColor::White.
        Color LayoutColor = Engine::KnownColor::White;

        LayoutGameObject() = default;
        virtual ~LayoutGameObject() {}

        ENGINE_NOT_COPYABLE(LayoutGameObject);
        ENGINE_NOT_ASSIGNABLE(LayoutGameObject);
    };
}

#endif // __ENGINE_BASICGAMEOBJECT_H__