#ifndef __ENGINE_RENDERER_H__
#define __ENGINE_RENDERER_H__

#include "Engine_Window.h"
#include "Engine_Color.h"

#include <SDL2/SDL2_gfxPrimitives.h>

namespace Engine {
    class Texture;

    /// @brief The Renderer class, use for managing and rendering with the renderer of the Window.
    class Renderer final {
    private:
        static SDL_Renderer* __renderer;
    public:
        /// @brief Get the current draw color of the Renderer.
        /// @return The current draw color of the Renderer, or Color::Empty on failed.
        static Color GetDrawColor() {
            if (!Renderer::__renderer) return Color::Empty;
            uint8_t r = 0, g = 0, b = 0, a = 0;
            SDL_GetRenderDrawColor(Renderer::__renderer, &r, &g, &b, &a);
            return Color(r, g, b, a);
        }
        /// @brief Set the current draw color of the Renderer.
        /// @param Red The red channel value of the color to set.
        /// @param Green The green channel value of the color to set.
        /// @param Blue The blue channel value of the color to set.
        /// @param Alpha The alpha channel value of the color to set (default is 255 mean fully opaque).
        static void SetDrawColor(uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t Alpha = 255) {
            if (Renderer::__renderer) SDL_SetRenderDrawColor(Renderer::__renderer, Red, Green, Blue, Alpha);
        }
        /// @brief Set the current draw color of the Renderer.
        /// @param Color The color to set.
        static void SetDrawColor(const Engine::Color& Color) { SetDrawColor(Color.Red, Color.Green, Color.Blue, Color.Alpha); }

        /// @brief Get the current draw blend mode of the Renderer.
        /// @return The current draw blend mode of the Renderer, or Invalid on failed.
        static DrawBlendMode GetDrawBlendMode() {
            if (!Renderer::__renderer) return DrawBlendMode::Invalid;
            SDL_BlendMode tmp = SDL_BLENDMODE_INVALID;
            SDL_GetRenderDrawBlendMode(Renderer::__renderer, &tmp);
            return (DrawBlendMode)tmp;
        }
        /// @brief Set the current draw blend mode of the Renderer.
        /// @param BlendMode The draw blend mode to set.
        static void SetDrawBlendMode(DrawBlendMode BlendMode) {
            if (Renderer::__renderer) SDL_SetRenderDrawBlendMode(Renderer::__renderer, (SDL_BlendMode)BlendMode);
        }

        /// @brief Get the output size of the Renderer.
        /// @return The output size of the Renderer, or Size::Zero on failed.
        static Size GetOutputSize() {
            if (!Renderer::__renderer) return Size::Zero;
            int w = 0, h = 0; SDL_GetRendererOutputSize(Renderer::__renderer, &w, &h);
            return Size(w, h);
        }
        /// @brief Get the current drawing area of the Renderer.
        /// @return The current drawing area of the Renderer, or Rectangle::Empty on failed.
        static Rectangle GetViewport() {
            if (!Renderer::__renderer) return Rectangle::Empty;
            SDL_Rect tmp = { 0, 0, 0, 0 }; SDL_RenderGetViewport(Renderer::__renderer, &tmp);
            return Rectangle(tmp.x, tmp.y, tmp.w, tmp.h);
        }
        /// @brief Set the drawing area of the Renderer.
        /// @param Area The Rectangle represent the drawing area to set, will not set if the area is empty.
        static void SetViewport(const Rectangle& Area) {
            if (!Renderer::__renderer || Area.IsEmptyArea()) return;
            SDL_Rect tmp = { Area.LeftSide(), Area.TopSide(), abs(Area.Width), abs(Area.Height) };
            SDL_RenderSetViewport(Renderer::__renderer, &tmp);
        }
        /// @brief Set the drawing area of the Renderer.
        /// @param Position The position of the drawing area (usually top-left) corner.
        /// @param Size The size of the drawing area, will not set if the area is empty.
        static void SetViewport(const Point& Position, const Engine::Size& Size) { SetViewport(Rectangle(Position, Size)); }
        /// @brief Set the drawing area of the Renderer.
        /// @param X The x position of the drawing area (usually top-left) corner.
        /// @param Y The Y position of the drawing area (usually top-left) corner.
        /// @param Width The width of the drawing area (along the x direction), will not set if this value is 0.
        /// @param Height The height of the drawing area (along the y direction), will not set if this value is 0.
        static void SetViewport(int X, int Y, int Width, int Height) { SetViewport(Rectangle(X, Y, Width, Height)); }
        /// @brief Reset the drawing area to the entire drawing surface.
        static void ResetViewport() { if (Renderer::__renderer) SDL_RenderSetViewport(Renderer::__renderer, nullptr); }

        /// @brief Clear the entire drawing area.
        static void Clear() { if (Renderer::__renderer) SDL_RenderClear(Renderer::__renderer); }

        /// @brief Update the drawing area.
        static void Present() { if (Renderer::__renderer) SDL_RenderPresent(Renderer::__renderer); }

        /// @brief Draw a point to the drawing area.
         /// @param X The x position of the point to draw.
         /// @param Y The y position of the point to draw.
        static void DrawPoint(int X, int Y) { if (Renderer::__renderer) SDL_RenderDrawPoint(Renderer::__renderer, X, Y); }
        /// @brief Draw a point at specific position.
        /// @param Position The position of the point to draw.
        static void DrawPoint(const Point& Position) { DrawPoint(Position.X, Position.Y); }

        /// @brief Draw a line to the drawing area.
        /// @param x1 The x position of the start point.
        /// @param y1 The y position of the start point.
        /// @param x2 The x position of the end point.
        /// @param y2 The y position of the end point.
        static void DrawLine(int x1, int y1, int x2, int y2) { if (Renderer::__renderer) SDL_RenderDrawLine(Renderer::__renderer, x1, y1, x2, y2); }
        /// @brief Draw a line to the drawing area.
        /// @param Start The position of the start point.
        /// @param End The position of the end point.
        static void DrawLine(const Point& Start, const Point& End) { DrawLine(Start.X, Start.Y, End.X, End.Y); }

        /// @brief Draw a rectangle to the drawing area.
        /// @param Rectangle The Rectangle to draw, will not draw if the area is empty.
        static void DrawRectangle(const Engine::Rectangle& Rectangle) {
            if (!Renderer::__renderer || Rectangle.IsEmptyArea()) return;
            SDL_Rect tmp = { Rectangle.LeftSide(), Rectangle.TopSide(), abs(Rectangle.Width), abs(Rectangle.Height) };
            SDL_RenderDrawRect(Renderer::__renderer, &tmp);
        }
        /// @brief Draw a rectangle to the drawing area.
        /// @param Position The position of the rectangle.
        /// @param Size The size of the rectangle, will not draw if the area is empty.
        static void DrawRectangle(const Point& Position, const Engine::Size& Size) { DrawRectangle(Rectangle(Position, Size)); }
        /// @brief Draw a rectangle to the drawing area.
        /// @param X The x position of the Rectangle (usually top-left) corner.
        /// @param Y The Y position of the Rectangle (usually top-left) corner.
        /// @param Width The width of the Rectangle (along the x direction), will not draw if this value is 0.
        /// @param Height The height of the Rectangle (along the y direction), will not draw if this value is 0.
        static void DrawRectangle(int X, int Y, int Width, int Height) { DrawRectangle(Rectangle(X, Y, Width, Height)); }

        /// @brief Draw a rounded-corner rectangle to the drawing area.
        /// @param Rectangle The Rectangle to draw, will not draw if the area is empty.
        /// @param Radius The radius of the rounded-corner.
        static void DrawRoundedRectangle(const Engine::Rectangle& Rectangle, uint32_t Radius) {
            if (!Renderer::__renderer || Rectangle.IsEmptyArea()) return;
            if (Radius <= 0) return DrawRectangle(Rectangle);
            Color c = GetDrawColor();
            roundedRectangleRGBA(Renderer::__renderer,
                Rectangle.LeftSide(), Rectangle.TopSide(), Rectangle.RightSide(), Rectangle.BottomSide(), Radius,
                c.Red, c.Green, c.Blue, c.Alpha);
        }
        /// @brief Draw a rounded-corner rectangle to the drawing area.
        /// @param Position The position of the rectangle.
        /// @param Size The size of the rectangle, will not draw if the area is empty.
        /// @param Radius The radius of the rounded-corner.
        static void DrawRoundedRectangle(const Point& Position, const Engine::Size& Size, uint32_t Radius) { DrawRoundedRectangle(Rectangle(Position, Size), Radius); }
        /// @brief Draw a rounded-corner rectangle to the drawing area.
        /// @param X The x position of the Rectangle (usually top-left) corner.
        /// @param Y The Y position of the Rectangle (usually top-left) corner.
        /// @param Width The width of the Rectangle (along the x direction), will not draw if this value is 0.
        /// @param Height The height of the Rectangle (along the y direction), will not draw if this value is 0.
        /// @param Radius The radius of the rounded-corner.
        static void DrawRoundedRectangle(int X, int Y, int Width, int Height, uint32_t Radius) { DrawRoundedRectangle(Rectangle(X, Y, Width, Height), Radius); }

        /// @brief Fill a rectangle to the drawing area.
        /// @param Rectangle The Rectangle to fill, will not fill if the area is empty.
        static void FillRectangle(const Engine::Rectangle& Rectangle) {
            if (!Renderer::__renderer) return;
            SDL_Rect tmp = { Rectangle.LeftSide(), Rectangle.TopSide(), abs(Rectangle.Width), abs(Rectangle.Height) };
            SDL_RenderFillRect(Renderer::__renderer, &tmp);
        }
        /// @brief Fill a rectangle to the drawing area.
        /// @param Position The position of the rectangle.
        /// @param Size The size of the rectangle, will not fill if the area is empty.
        static void FillRectangle(const Point& Position, const Engine::Size& Size) { FillRectangle(Rectangle(Position, Size)); }
        /// @brief Fill a rectangle to the drawing area.
        /// @param X The x position of the Rectangle (usually top-left) corner.
        /// @param Y The Y position of the Rectangle (usually top-left) corner.
        /// @param Width The width of the Rectangle (along the x direction), will not draw if this value is 0.
        /// @param Height The height of the Rectangle (along the y direction), will not draw if this value is 0.
        static void FillRectangle(int X, int Y, int Width, int Height) { FillRectangle(Rectangle(X, Y, Width, Height)); }

        /// @brief Fill a rounded-corner rectangle to the drawing area.
        /// @param Rectangle The Rectangle to fill, will not fill if the area is empty.
        /// @param Radius The radius of the rounded-corner.
        static void FillRoundedRectangle(const Engine::Rectangle& Rectangle, uint32_t Radius) {
            if (!Renderer::__renderer) return;
            if (Radius <= 0) return FillRectangle(Rectangle);
            Color c = GetDrawColor();
            roundedBoxRGBA(Renderer::__renderer,
                Rectangle.LeftSide(), Rectangle.TopSide(), Rectangle.RightSide(), Rectangle.BottomSide(), Radius,
                c.Red, c.Green, c.Blue, c.Alpha);
        }
        /// @brief Fill a rounded-corner rectangle to the drawing area.
        /// @param Position The position of the rectangle.
        /// @param Size The size of the rectangle, will not fill if the area is empty.
        /// @param Radius The radius of the rounded-corner.
        static void FillRoundedRectangle(const Point& Position, const Engine::Size& Size, uint32_t Radius) { FillRoundedRectangle(Rectangle(Position, Size), Radius); }
        /// @brief Fill a rounded-corner rectangle to the drawing area.
        /// @param X The x position of the Rectangle (usually top-left) corner.
        /// @param Y The Y position of the Rectangle (usually top-left) corner.
        /// @param Width The width of the Rectangle (along the x direction), will not draw if this value is 0.
        /// @param Height The height of the Rectangle (along the y direction), will not draw if this value is 0.
        /// @param Radius The radius of the rounded-corner.
        static void FillRoundedRectangle(int X, int Y, int Width, int Height, uint32_t Radius) { FillRoundedRectangle(Rectangle(X, Y, Width, Height), Radius); }

        /// @brief Draw a circle to the drawing area.
        /// @param X The x position of the center of the circle.
        /// @param Y The y position of the center of the circle.
        /// @param Radius The radius of the circle, will not draw if this value is 0.
        static void DrawCircle(int X, int Y, uint32_t Radius) {
            if (!Renderer::__renderer) return;
            if (Radius == 0) return;
            Color c = GetDrawColor();
            circleRGBA(Renderer::__renderer, X, Y, Radius, c.Red, c.Green, c.Blue, c.Alpha);
        }
        /// @brief Draw a circle to the drawing area.
        /// @param Position The position of the center of the circle.
        /// @param Radius The radius of the circle, will not draw if this value is 0.
        static void DrawCircle(const Point& Position, uint32_t Radius) { DrawCircle(Position.X, Position.Y, Radius); }

        /// @brief Fill a circle to the drawing area.
        /// @param X The x position of the center of the circle.
        /// @param Y The y position of the center of the circle.
        /// @param Radius The radius of the circle, will not fill if this value is 0.
        static void FillCircle(int X, int Y, uint32_t Radius) {
            if (!Renderer::__renderer) return;
            if (Radius == 0) return;
            Color c = GetDrawColor();
            circleRGBA(Renderer::__renderer, X, Y, Radius, c.Red, c.Green, c.Blue, c.Alpha);
        }
        /// @brief Fill a circle to the drawing area.
        /// @param Position The position of the center of the circle.
        /// @param Radius The radius of the circle, will not fill if this value is 0.
        static void FillCircle(const Point& Position, uint32_t Radius) { FillCircle(Position.X, Position.Y, Radius); }

        /// @brief Draw an ellipse to the drawing area.
        /// @param X The x position of the center of the ellipse.
        /// @param Y The y position of the center of the ellipse.
        /// @param RadiusX The radius of the ellipse in the x direction, will not draw if this value is 0.
        /// @param RadiusY The radius of the ellipse in the y direction, will not draw if this value is 0.
        static void DrawEllipse(int X, int Y, uint32_t RadiusX, uint32_t RadiusY) {
            if (!Renderer::__renderer) return;
            if (RadiusX == 0 || RadiusY == 0) return;
            Color c = GetDrawColor();
            ellipseRGBA(Renderer::__renderer, X, Y, RadiusX, RadiusY, c.Red, c.Green, c.Blue, c.Alpha);
        }
        /// @brief Draw an ellipse to the drawing area.
        /// @param Position The position of the center of the ellipse.
        /// @param RadiusX The radius of the ellipse in the x direction, will not draw if this value is 0.
        /// @param RadiusY The radius of the ellipse in the y direction, will not draw if this value is 0.
        static void DrawEllipse(const Point& Position, uint32_t RadiusX, uint32_t RadiusY) { DrawEllipse(Position.X, Position.Y, RadiusX, RadiusY); }

        /// @brief Fill an ellipse to the drawing area.
        /// @param X The x position of the center of the ellipse.
        /// @param Y The y position of the center of the ellipse.
        /// @param RadiusX The radius of the ellipse in the x direction, will not fill if this value is 0.
        /// @param RadiusY The radius of the ellipse in the y direction, will not fill if this value is 0.
        static void FillEllipse(int X, int Y, uint32_t RadiusX, uint32_t RadiusY) {
            if (!Renderer::__renderer) return;
            if (RadiusX == 0 || RadiusY == 0) return;
            Color c = GetDrawColor();
            ellipseRGBA(Renderer::__renderer, X, Y, RadiusX, RadiusY, c.Red, c.Green, c.Blue, c.Alpha);
        }
        /// @brief Fill an ellipse to the drawing area.
        /// @param Position The position of the center of the ellipse.
        /// @param RadiusX The radius of the ellipse in the x direction, will not fill if this value is 0.
        /// @param RadiusY The radius of the ellipse in the y direction, will not fill if this value is 0.
        static void FillEllipse(const Point& Position, uint32_t RadiusX, uint32_t RadiusY) { DrawEllipse(Position.X, Position.Y, RadiusX, RadiusY); }

        /// @brief Fill a Texture to the entire drawing area.
        /// @param Texture The texture to fill.
        static void FillTexture(Engine::Texture* Texture);

        /// @brief Draw a Texture to the drawing area.
        /// @param Position The target position of the top-left corner of the target area to draw.
        /// @param Texture The texture to draw.
        /// @param RotationAngle The angle to rotate the texture when drawing, in degrees.
        /// @param HorizontalFlip If this true, will flipped output texture horizontally when drawing.
        /// @param VerticalFlip If this true, will flipped output texture vertically when drawing.
        static void DrawTexture(const Point& Position, Engine::Texture* Texture, double RotationAngle = 0,
            bool HorizontalFlip = false, bool VerticalFlip = false);
        /// @brief Draw a Texture to the drawing area.
        /// @param Area The target area to draw (will scaled the Texture to fit).
        /// @param Texture The texture to draw.
        /// @param RotationAngle The angle to rotate the texture when drawing, in degrees.
        /// @param HorizontalFlip If this true, will flipped output texture horizontally when drawing.
        /// @param VerticalFlip If this true, will flipped output texture vertically when drawing. 
        static void DrawTexture(const Rectangle& Area, Engine::Texture* Texture, double RotationAngle = 0,
            bool HorizontalFlip = false, bool VerticalFlip = false);
        /// @brief Draw a Texture to the drawing area.
        /// @param Position The target position of the top-left corner of the target area to draw.
        /// @param Texture The texture to draw.
        /// @param Center The center Point of the rotation when drawing.
        /// @param RotationAngle The angle to rotate the texture when drawing, in degrees.
        /// @param HorizontalFlip If this true, will flipped output texture horizontally when drawing.
        /// @param VerticalFlip If this true, will flipped output texture vertically when drawing.
        static void DrawTexture(const Point& Position, Engine::Texture* Texture, const Point& Center, double RotationAngle = 0,
            bool HorizontalFlip = false, bool VerticalFlip = false);
        /// @brief Draw a Texture to the drawing area.
        /// @param Area The target area to draw (will scaled the Texture to fit).
        /// @param Texture The texture to draw.
        /// @param Center The center Point of the rotation when drawing.
        /// @param RotationAngle The angle to rotate the texture when drawing, in degrees.
        /// @param HorizontalFlip If this true, will flipped output texture horizontally when drawing.
        /// @param VerticalFlip If this true, will flipped output texture vertically when drawing. 
        static void DrawTexture(const Rectangle& Area, Engine::Texture* Texture, const Point& Center, double RotationAngle = 0,
            bool HorizontalFlip = false, bool VerticalFlip = false);

        /// @brief Draw a Texture to the drawing area without perform scaling.
        /// @param Area The target area to draw.
        /// @param Texture The texture to draw.
        /// @param RotationAngle The angle to rotate the texture when drawing, in degrees. Default is 0 mean not rotating.
        /// @param HorizontalFlip If this true, will flipped output texture horizontally when drawing. Default is false.
        /// @param VerticalFlip If this true, will flipped output texture vertically when drawing. Default is false.
        /// @param Alignment The alignment of the texture when drawing. Default is TopLeft.
        static void DrawTextureUnscaled(const Rectangle& Area, Engine::Texture* Texture, double RotationAngle = 0,
            bool HorizontalFlip = false, bool VerticalFlip = false, RectangleAlignment Alignment = RectangleAlignment::TopLeft);
        /// @brief Draw a Texture to the drawing area without perform scaling.
        /// @param Area The target area to draw.
        /// @param Texture The texture to draw.
        /// @param Center The center Point of the rotation when drawing.
        /// @param RotationAngle The angle to rotate the texture when drawing, in degrees. Default is 0 mean not rotating.
        /// @param HorizontalFlip If this true, will flipped output texture horizontally when drawing. Default is false.
        /// @param VerticalFlip If this true, will flipped output texture vertically when drawing. Default is false.
        /// @param Alignment The alignment of the texture when drawing. Default is TopLeft.
        static void DrawTextureUnscaled(const Rectangle& Area, Engine::Texture* Texture, const Point& Center, double RotationAngle = 0,
            bool HorizontalFlip = false, bool VerticalFlip = false, RectangleAlignment Alignment = RectangleAlignment::TopLeft);

        /// @brief Check if the Renderer is initialized successfully (notice that the Renderer will only usable
        /// if both the Renderer and Window have initialized successfully).
        /// @return true if the Renderer is initialized successfully, false otherwise.
        static bool IsInitialized() { return (bool)Renderer::__renderer; }
        /// @brief Initialize (or re-initialize) the Renderer (the Window must be initialized successfully),
        /// this should be called on Engine::Initialize() after successfully initialized the Window.
        /// @return true on success, false on failure.
        static bool Initialize() {
            if (Renderer::__renderer)
                Deinitialize();
            if (!Window::IsInitialized())
                return false;
            SDL_Window* window = SDL_GetWindowFromID(Window::GetID());
            if (!window)
                return false;
            
            Renderer::__renderer = SDL_CreateRenderer(
                window, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE |
                    (Application::EnableVSyncPresent ? SDL_RENDERER_PRESENTVSYNC : 0));
            if (!Renderer::__renderer)
                return false;
            SDL_SetRenderDrawBlendMode(Renderer::__renderer, SDL_BLENDMODE_BLEND);
            return true;
        }
        /// @brief Deinitialize the Renderer, this should be called on Engine::Deinitialize().
        /// This will also destroy all created Textures.
        /// After calling this, the Renderer will be unusable.
        static void Deinitialize();
    };

    /// @brief The Render Event Args struct, use for rendering event.
    struct RenderEventArgs : public EventArgs {
    public:
        /// @brief The target area of the rendering event.
        Rectangle TargetArea = Rectangle::Empty;
    };
}

SDL_Renderer* Engine::Renderer::__renderer = nullptr;

#endif // __ENGINE_RENDERER_H__