#ifndef __ENGINE_IMAGING_H__
#define __ENGINE_IMAGING_H__

#include "Engine_Structure.h"
#include "Engine_Renderer.h"

#include <SDL2/SDL_image.h>
#include <unordered_set>
#include <iostream>

namespace Engine {
    class Texture;

    /// @brief The Color Map class, represent an two-dimensional color map.
    class ColorMap {
    private:
        SDL_Surface* data = nullptr;

        static bool __is_destroy_all;
        static std::unordered_set<ColorMap*> __created_color_map;
    protected:
        ColorMap(SDL_Surface* surface) : data(surface) { ColorMap::__created_color_map.insert(this); }
    public:
        /// @brief The name of the Color Map. Default is "Color Map".
        std::string Name = "Color Map";

        /// @brief Create a new Color Map with the given Size.
        /// @param Size The Size to of the Color Map. If this size has empty area, the Color Map will be not avaliable.
        ColorMap(const Engine::Size& Size)
            : data(Size.IsEmptyArea() ? SDL_CreateRGBSurfaceWithFormat(0, abs(Size.Width), abs(Size.Height), 32, SDL_PIXELFORMAT_RGBA8888) : nullptr) {}
        /// @brief Create a new Color Map with the given Size.
        /// @param Width The width of the Color Map. If this value is 0, the Color Map will be not avaliable.
        /// @param Height The height of the Color Map. If this value is 0, the Color Map will be not avaliable.
        ColorMap(int Width, int Height) : ColorMap(Size(Width, Height)) {}

        virtual ~ColorMap() {
            if (data) SDL_FreeSurface(data);
            data = nullptr;
            if (!__is_destroy_all)
                __created_color_map.erase(this);
        }

        ENGINE_NOT_COPYABLE(ColorMap)
        ENGINE_NOT_ASSIGNABLE(ColorMap)

        /// @brief Get the SDL_Surface that allocated to this Color Map instance.
        /// @return The SDL_Surface that allocated to this Color Map instance, or nullptr if there's none.
        SDL_Surface* GetSDLSurface() const { return data; }

        /// @brief Check if the data use by this Color Map is avaliable.
        /// @return true if the data is avaliable (not null), false otherwise.
        bool IsAvaliable() const { return (bool)data; }

        /// @brief Check if the Color Map must be locked before accessing it pixels.
        /// @return true if the Color Map must be locked, false otherwise.
        bool IsMustLock() const { return data ? SDL_MUSTLOCK(data) : false; }
        /// @brief Get the number of bytes that the Color Map is using per pixels.
        /// @return The number of bytes that the Color Map is using per pixels.
        int GetBytesPerPixel() const { return data ? data->format->BytesPerPixel : 0; }
        /// @brief Get the number of bits that the Color Map is using per pixels.
        /// @return The number of bits that the Color Map is using per pixels.
        int GetBitsPerPixel() const { return data ? data->format->BitsPerPixel : 0; }

        /// @brief Lock the Color Map so it pixel can be accessed directly through SetPixel and GetPixel.
        void Lock() { if (data) SDL_LockSurface(data); }
        /// @brief Unlock the Color Map.
        void Unlock() { if (data) SDL_UnlockSurface(data); }

        /// @brief Get the size of the Color Map.
        /// @return The size of the Color Map, or Size::Zero on failed.
        Size GetSize() const {
            if (!data) return Size::Zero;
            return Size(data->w, data->h);
        }

        /// @brief Set the color of a specific pixel of the Color Map. You may need to lock the
        /// Color Map before doing this if the Color Map is must lock (use IsMustLock to check).
        /// @param X The x position of the pixel, will not set if not in range [0, width) with 'width' is the Color Map width.
        /// @param Y The y position of the pixel, will not set if not in range [0, height) with 'height' is the Color Map height.
        /// @param Color The color to set.
        void SetPixel(int X, int Y, const Engine::Color& Color) {
            if (!data) return;
            if (X < 0 || X >= data->w || Y < 0 || Y >= data->h) return;
            uint32_t* target_pixel = (uint32_t*)(
                (uint8_t*)data->pixels + Y * data->pitch + X * data->format->BytesPerPixel);
            uint32_t color32 = SDL_MapRGBA(data->format, Color.Red, Color.Green, Color.Blue, Color.Alpha);
            SDL_memcpy(target_pixel, &color32, data->format->BytesPerPixel);
        }
        /// @brief Get the color of a specific pixel of the Color Map. You need to lock the
        /// Color Map before doing this if the Color Map is must lock, or this will caused undefined behavior.
        /// @param X The x position of the pixel.
        /// @param Y The y position of the pixel.
        /// @return The color of the pixel at the given coordinate. Will return Color::Empty if the given pixel coordinate
        /// is not belong to the Color Map or on failed.
        Color GetPixel(int X, int Y) const {
            if (!data) return Color::Empty;
            if (X < 0 || X >= data->w || Y < 0 || Y >= data->h) return Color::Empty;
            Uint32* target_pixel = (Uint32*)(
                (Uint8*)data->pixels + Y * data->pitch + X * data->format->BytesPerPixel);
            Uint8 r = 0, g = 0, b = 0, a = 0;
            SDL_GetRGBA(*target_pixel, data->format, &r, &g, &b, &a);
            return Color(r, g, b, a);
        }

        /// @brief Save the Color Map as an PNG file. If the file was already exist, will
        /// overwrite it.
        /// @param file_path The path of the file to save.
        /// @return true on success, false on failure.
        bool SaveAsPng(const char* file_path) const {
            if (!file_path || !data) return false;
            return IMG_SavePNG(data, file_path) == 0;
        }
        /// @brief Save the Color Map as an JPG file. If the file was already exist, will
        /// overwrite it.
        /// @param file_path The path of the file to save.
        /// @param quality The quality of the compression ([0, 33] for low quality,
        /// [34, 66] for medium quality, [67, 100] for high quality). Default is 90.
        /// @return true on success, false on failure.
        bool SaveAsJpg(const char* file_path, int quality = 90) const {
            if (!file_path || !data) return false;
            return IMG_SaveJPG(data, file_path, ENGINE_FAST_CLAMP(0, 100, quality)) == 0;
        }

        /// @brief Duplicate this Color Map, notice that you also need to destroy the result Color Map.
        /// @return A newly created Color Map that's identical to this Color Map, or nullptr on failed.
        ColorMap* Duplicate() const {
            if (!data) return nullptr;
            SDL_Surface* result_surface = SDL_DuplicateSurface(data);
            if (!result_surface) return nullptr;
            return new ColorMap(result_surface);
        }

        /// @brief Get the current blend mode of the Color Map, use for copying (bliting) operation.
        /// @return The current blend mode of the Color Map, or Invalid on failed.
        DrawBlendMode GetBlendMode() const {
            if (!data) return DrawBlendMode::Invalid;
            SDL_BlendMode tmp = SDL_BLENDMODE_INVALID;
            SDL_GetSurfaceBlendMode(data, &tmp);
            return (DrawBlendMode)tmp;
        }
        /// @brief Set the current blend mode of the Color Map, use for copying (bliting) operation.
        /// @param BlendMode The blend mode to set.
        void SetBlendMode(DrawBlendMode BlendMode) {
            if (data) SDL_SetSurfaceBlendMode(data, (SDL_BlendMode)BlendMode);
        }
        /// @brief Set the additional color value that will be multiply for each pixel copied of the Color Map for copying (bliting)
        /// operation (draw_color = source_color * (mod_color / 255)).
        /// @param ModColor The mod color to set.
        void SetColorMod(const Color& ModColor) {
            if (!data) return;
            SDL_SetSurfaceColorMod(data, ModColor.Red, ModColor.Green, ModColor.Blue);
            SDL_SetSurfaceAlphaMod(data, ModColor.Alpha);
        }
        /// @brief Get the current mod color that will be multiply for each pixel copied of the Color Map for copying (bliting)
        /// operation (draw_color = source_color * (mod_color / 255)).
        /// @return The current mod color of the Color Map, or Color::Empty on failed.
        Color GetColorMod() const {
            if (!data) return Color::Empty;
            uint8_t r = 0, g = 0, b = 0, a = 0;
            SDL_GetSurfaceColorMod(data, &r, &g, &b);
            SDL_GetSurfaceAlphaMod(data, &a);
            return Color(r, g, b, a);
        }

        /// @brief Create a new Texture that it texture is the same as the Color Map, notice that you also need to destroy the result Texture after.
        /// @return The result Texture that have this Color Map data, or nullptr on failed.
        Texture* CreateTexture() const;

        /// @brief Copy the entire Color Map to the entire area of another Color Map.
        /// @param Source The Color Map to copy from, must not null and avaliable.
        /// @param Destination The Color Map to copy to, must not null and avaliable.
        static void Copy(ColorMap* Source, ColorMap* Destination) {
            if (!Source || !Destination) return;
            if (!Source->IsAvaliable() || !Destination->IsAvaliable()) return;

            Size src_size = Source->GetSize(), dest_size = Destination->GetSize();
            if (src_size.IsEmptyArea() || dest_size.IsEmptyArea()) return;
            
            SDL_Rect src_r = {0, 0, src_size.Width, src_size.Height};
            SDL_Rect dest_r = {0, 0, dest_size.Width, dest_size.Height};

            SDL_BlitScaled(Source->data, &src_r, Destination->data, &dest_r);
        }
        /// @brief Copy the entire Color Map to a specific area in another Color Map.
        /// @param Source The Color Map to copy from, must not null and avaliable.
        /// @param Destination The Color Map to copy to, must not null and avaliable.
        /// @param DestinationArea The area to copy to the destination Color Map, must not have empty area.
        /// Also, will only target the intersection part of this area and the Color Map area.
        static void Copy(ColorMap* Source, ColorMap* Destination, const Rectangle& DestinationArea) {
            if (!Source || !Destination || DestinationArea.IsEmptyArea()) return;
            if (!Source->IsAvaliable() || !Destination->IsAvaliable()) return;

            Size src_size = Source->GetSize();
            Rectangle dest_target = Rectangle::Intersect(Rectangle(Point::Zero, Destination->GetSize()), DestinationArea);
            if (src_size.IsEmptyArea() || dest_target.IsEmptyArea()) return;
            
            SDL_Rect src_r = {0, 0, src_size.Width, src_size.Height};
            SDL_Rect dest_r = {dest_target.X, dest_target.Y, dest_target.Width, dest_target.Height};

            SDL_BlitScaled(Source->data, &src_r, Destination->data, &dest_r);            
        }
        /// @brief Copy a portion of a Color Map to a specific area in another Color Map.
        /// @param Source The Color Map to copy from, must not null and avaliable.
        /// @param SourceArea The area to copy from the source Color Map, must not have empty area.
        /// Also, will only copy the intersection part of this area and the Color Map area.
        /// @param Destination The Color Map to copy to, must not null and avaliable.
        /// @param DestinationArea The area to copy to the destination Color Map, must not have empty area.
        /// Also, will only target the intersection part of this area and the Color Map area.
        static void Copy(ColorMap* Source, const Rectangle& SourceArea, ColorMap* Destination, const Rectangle& DestinationArea) {
            if (!Source || SourceArea.IsEmptyArea() || !Destination || DestinationArea.IsEmptyArea()) return;
            if (!Source->IsAvaliable() || !Destination->IsAvaliable()) return;

            Rectangle src_target = Rectangle::Intersect(Rectangle(Point::Zero, Source->GetSize()), SourceArea);
            Rectangle dest_target = Rectangle::Intersect(Rectangle(Point::Zero, Destination->GetSize()), DestinationArea);
            if (src_target.IsEmptyArea() || dest_target.IsEmptyArea()) return;
            
            SDL_Rect src_r = {src_target.X, src_target.Y, src_target.Width, src_target.Height};
            SDL_Rect dest_r = {dest_target.X, dest_target.Y, dest_target.Width, dest_target.Height};

            SDL_BlitScaled(Source->data, &src_r, Destination->data, &dest_r);            
        }

        /// @brief Copy the entire Color Map to the entire area of another Color Map, without perform scaling.
        /// @param Source The Color Map to copy from, must not null and avaliable.
        /// @param Destination The Color Map to copy to, must not null and avaliable.
        static void CopyUnscaled(ColorMap* Source, ColorMap* Destination) {
            if (!Source || !Destination) return;
            if (!Source->IsAvaliable() || !Destination->IsAvaliable()) return;

            Size src_size = Source->GetSize(), dest_size = Destination->GetSize();
            if (src_size.IsEmptyArea() || dest_size.IsEmptyArea()) return;

            int target_width = ENGINE_MIN(src_size.Width, dest_size.Width), target_height = ENGINE_MIN(src_size.Height, dest_size.Height);
            
            SDL_Rect src_r = {0, 0, target_width, target_height};
            SDL_Rect dest_r = {0, 0, target_width, target_height};

            SDL_BlitSurface(Source->data, &src_r, Destination->data, &dest_r);            
        }
        /// @brief Copy the entire Color Map to a specific area in another Color Map, without perform scaling.
        /// @param Source The Color Map to copy from, must not null and avaliable.
        /// @param Destination The Color Map to copy to, must not null and avaliable.
        /// @param DestinationArea The area to copy to the destination Color Map, must not have empty area.
        /// Also, will only target the intersection part of this area and the Color Map area.
        static void CopyUnscaled(ColorMap* Source, ColorMap* Destination, const Rectangle& DestinationArea) {
            if (!Source || !Destination || DestinationArea.IsEmptyArea()) return;
            if (!Source->IsAvaliable() || !Destination->IsAvaliable()) return;

            Size src_size = Source->GetSize();
            Rectangle dest_target = Rectangle::Intersect(Rectangle(Point::Zero, Destination->GetSize()), DestinationArea);
            if (src_size.IsEmptyArea() || dest_target.IsEmptyArea()) return;

            int target_width = ENGINE_MIN(src_size.Width, dest_target.Width), target_height = ENGINE_MIN(src_size.Height, dest_target.Height);
            
            SDL_Rect src_r = {0, 0, target_width, target_height};
            SDL_Rect dest_r = {dest_target.X, dest_target.Y, target_width, target_height};

            SDL_BlitSurface(Source->data, &src_r, Destination->data, &dest_r);            
        }
        /// @brief Copy a portion of a Color Map to a specific area in another Color Map, without perform scaling.
        /// @param Source The Color Map to copy from, must not null and avaliable.
        /// @param SourceArea The area to copy from the source Color Map, must not have empty area.
        /// Also, will only copy the intersection part of this area and the Color Map area.
        /// @param Destination The Color Map to copy to, must not null and avaliable.
        /// @param DestinationArea The area to copy to the destination Color Map, must not have empty area.
        /// Also, will only target the intersection part of this area and the Color Map area.
        static void CopyUnscaled(ColorMap* Source, const Rectangle& SourceArea, ColorMap* Destination, const Rectangle& DestinationArea) {
            if (!Source || SourceArea.IsEmptyArea() || !Destination || DestinationArea.IsEmptyArea()) return;
            if (!Source->IsAvaliable() || !Destination->IsAvaliable()) return;

            Rectangle src_target = Rectangle::Intersect(Rectangle(Point::Zero, Source->GetSize()), SourceArea);
            Rectangle dest_target = Rectangle::Intersect(Rectangle(Point::Zero, Destination->GetSize()), DestinationArea);
            if (src_target.IsEmptyArea() || dest_target.IsEmptyArea()) return;

            int target_width = ENGINE_MIN(src_target.Width, dest_target.Width), target_height = ENGINE_MIN(src_target.Height, dest_target.Height);
            
            SDL_Rect src_r = {src_target.X, src_target.Y, target_width, target_height};
            SDL_Rect dest_r = {dest_target.X, dest_target.Y, target_width, target_height};

            SDL_BlitSurface(Source->data, &src_r, Destination->data, &dest_r);            
        }

        /// @brief Create a new Color Map from an image file.
        /// @param file_path The path of the image file to create.
        /// @return The Color Map from the given image file, or nullptr on failed.
        static ColorMap* FromFile(const char* file_path) {
            if (!file_path) return nullptr;
            SDL_Surface* result = IMG_Load(file_path);
            if (!result) return nullptr;
            return new ColorMap(result);
        }
        /// @brief Create a new Color Map from the given Surface.
        /// @param surface The surface to create.
        /// @return The result Color Map that allocated the given surface to, or nullptr if the given
        /// surface is null or failed.
        static ColorMap* FromSDLSurface(SDL_Surface* surface) {
            if (!surface) return nullptr;
            return new ColorMap(surface);
        }


        /// @brief Execute an action for each created Color Map.
        /// @param action The action to execute.
        /// @return The number of Color Map that called with the given action.
        static size_t ForEachColorMap(const std::function<void(ColorMap*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (ColorMap* scene : ColorMap::__created_color_map)
                if (scene) { action(scene); count++; }

            return count;
        }
        /// @brief Execute an action for each created Color Map, if the Color Map is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Color Map that called with the given action.
        static size_t ForEachColorMapIf(const std::function<void(ColorMap*)>& action, const std::function<bool(ColorMap*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachColorMap(action);
            size_t count = 0;
            for (ColorMap* scene : ColorMap::__created_color_map) {
                if (!scene) continue;
                if (!predicate(scene)) continue;
                action(scene); count++;
            }

            return count;
        }
        /// @brief Find the first created Color Map with the given name.
        /// @param name The name to find.
        /// @return The first Color Map with the given name, or nullptr if not found.
        static ColorMap* FindColorMap(const std::string& name) {
            for (ColorMap* obj : ColorMap::__created_color_map) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first created Color Map that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Color Map that satisfied the given predicate, or nullptr if no Color Map satisfied.
        static ColorMap* FindColorMapIf(const std::function<bool(ColorMap*)>& predicate) {
            if (!predicate) return nullptr;
            for (ColorMap* obj : ColorMap::__created_color_map) {
                if (!obj) continue;
                if (predicate(obj)) return obj;
            }
            return nullptr;
        }

        /// @brief Destroy all created Color Maps, this will be called on Engine::Deinitialize().
        static void DestoryAllCreatedColorMaps() {
            ColorMap::__is_destroy_all = true;
            for (ColorMap* color_map : ColorMap::__created_color_map)
                if (color_map) delete color_map;
            ColorMap::__created_color_map.clear();
            ColorMap::__is_destroy_all = false;
        }
    };

    /// @brief The Texture class, represent a texture that can be render using Renderer.
    class Texture {
    private:
        SDL_Texture* data = nullptr;

        static bool __is_destroy_all;
        static std::unordered_set<Texture*> __created_textures;
    protected:
        Texture(SDL_Texture* texture) : data(texture) { Texture::__created_textures.insert(this); }
    public:
        /// @brief The name of the Texture. Default is "Texture".
        std::string Name = "Texture";

        virtual ~Texture() {
            if (data) SDL_DestroyTexture(data);
            data = nullptr;
            if (!Texture::__is_destroy_all)
                Texture::__created_textures.erase(this);
        }

        ENGINE_NOT_COPYABLE(Texture)
        ENGINE_NOT_ASSIGNABLE(Texture)

        /// @brief Get the SDL_Texture that allocated with the Texture.
        /// @return The SDL_Texture that allocated with the Texture, or nullptr if there's none.
        SDL_Texture* GetSDLTexture() const { return data; }

        /// @brief Check if the data use by this Texture is avaliable.
        /// @return true if the data is avaliable (not null), false otherwise.
        bool IsAvaliable() const { return (bool)data; }

        /// @brief Get the size of the Texture.
        /// @return The size of the texture, or Size::Zero on failed.
        Size GetSize() const {
            if (!data) return Size::Zero;
            int w = 0, h = 0; SDL_QueryTexture(data, nullptr, nullptr, &w, &h);
            return Size(w, h);
        }

        /// @brief Set the current blend mode of the Texture, use for rendering operation.
        /// @param BlendMode The blend mode to set.
        void SetBlendMode(DrawBlendMode BlendMode) {
            if (data) SDL_SetTextureBlendMode(data, (SDL_BlendMode)BlendMode);
        }
        /// @brief Set the additional color value that will be multiply for each pixel copied of the Texture for rendering
        /// operation (draw_color = source_color * (mod_color / 255)).
        /// @param ModColor The mod color to set.
        void SetColorMod(const Color& ModColor) {
            if (!data) return;
            SDL_SetTextureColorMod(data, ModColor.Red, ModColor.Green, ModColor.Blue);
            SDL_SetTextureAlphaMod(data, ModColor.Alpha);
        }
        /// @brief Get the current mod color that will be multiply for each pixel copied of the Texture for rendering
        /// operation (draw_color = source_color * (mod_color / 255)).
        /// @return The current mod color of the Texture, or Color::Empty on failed.
        Color GetColorMod() const {
            if (!data) return Color::Empty;
            uint8_t r = 0, g = 0, b = 0, a = 0;
            SDL_GetTextureColorMod(data, &r, &g, &b);
            SDL_GetTextureAlphaMod(data, &a);
            return Color(r, g, b, a);
        }

        /// @brief Create a new Texture (require both Window and Renderer to be initialized successfully).
        /// @param Size The Size of the Texture, must not has empty area.
        /// @return The newly created Texture, or nullptr on failed.
        static Texture* Create(const Engine::Size& Size) {
            if (Size.IsEmptyArea()) return nullptr;
            if (!Window::IsInitialized()) return nullptr;
            if (!Renderer::IsInitialized()) return nullptr;
            
            SDL_Window* window = SDL_GetWindowFromID(Window::GetID());
            if (!window) return nullptr;
            SDL_Renderer* renderer = SDL_GetRenderer(window);
            if (!renderer) return nullptr;

            SDL_Texture* texture = SDL_CreateTexture(renderer,
                SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, abs(Size.Width), abs(Size.Height));

            return FromSDLTexture(texture);
        }
        /// @brief Create a new Texture (require both Window and Renderer to be initialized successfully).
        /// @param Width The width of the Texture, must not be 0.
        /// @param Height The height of the Texture, must not be 0.
        /// @return The newly created Texture, or nullptr on failed.
        static Texture* Create(int Width, int Height) { return Create(Size(Width, Height)); }

        /// @brief Create a new Texture from an image file (require both Window and Renderer to be initialized successfully).
        /// @param file_path The path of the image file to create.
        /// @return The newly created Texture from the image file, or nullptr on failed.
        static Texture* FromFile(const char* file_path) {
            if (!file_path) return nullptr;
            if (!Window::IsInitialized()) return nullptr;
            if (!Renderer::IsInitialized()) return nullptr;
            
            SDL_Window* window = SDL_GetWindowFromID(Window::GetID());
            if (!window) return nullptr;
            SDL_Renderer* renderer = SDL_GetRenderer(window);
            if (!renderer) return nullptr;

            return FromSDLTexture(IMG_LoadTexture(renderer, file_path));
        }
        /// @brief Create a new Texture from the given SDL_Texture.
        /// @param texture The texture to create.
        /// @return The result Texture that allocated the given texture to, or nullptr if the given
        /// texture is null or failed.
        static Texture* FromSDLTexture(SDL_Texture* texture) { return texture ? new Texture(texture) : nullptr; }


        /// @brief Execute an action for each created Texture.
        /// @param action The action to execute.
        /// @return The number of Texture that called with the given action.
        static size_t ForEachTexture(const std::function<void(Texture*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (Texture* scene : Texture::__created_textures)
                if (scene) { action(scene); count++; }

            return count;
        }
        /// @brief Execute an action for each created Texture, if the Texture is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Texture that called with the given action.
        static size_t ForEachTextureIf(const std::function<void(Texture*)>& action, const std::function<bool(Texture*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachTexture(action);
            size_t count = 0;
            for (Texture* scene : Texture::__created_textures) {
                if (!scene) continue;
                if (!predicate(scene)) continue;
                action(scene); count++;
            }

            return count;
        }
        /// @brief Find the first created Texture with the given name.
        /// @param name The name to find.
        /// @return The first Texture with the given name, or nullptr if not found.
        static Texture* FindTexture(const std::string& name) {
            for (Texture* obj : Texture::__created_textures) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first created Texture that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Texture that satisfied the given predicate, or nullptr if no Texture satisfied.
        static Texture* FindTextureIf(const std::function<bool(Texture*)>& predicate) {
            if (!predicate) return nullptr;
            for (Texture* obj : Texture::__created_textures) {
                if (!obj) continue;
                if (predicate(obj)) return obj;
            }
            return nullptr;
        }

        /// @brief Destroy all created Textures, this will be called on Engine::Deinitialize().
        static void DestoryAllCreatedTextures() {
            Texture::__is_destroy_all = true;
            for (Texture* texture : Texture::__created_textures)
                if (texture) delete texture;
            Texture::__created_textures.clear();
            Texture::__is_destroy_all = false;
        }
    };
}

bool Engine::ColorMap::__is_destroy_all = false;
std::unordered_set<Engine::ColorMap*> Engine::ColorMap::__created_color_map = std::unordered_set<Engine::ColorMap*>();

bool Engine::Texture::__is_destroy_all = false;
std::unordered_set<Engine::Texture*> Engine::Texture::__created_textures = std::unordered_set<Engine::Texture*>();


Engine::Texture* Engine::ColorMap::CreateTexture() const {
    if (!IsAvaliable()) return nullptr;
    if (!Window::IsInitialized()) return nullptr;
    if (!Renderer::IsInitialized()) return nullptr;
            
    SDL_Window* window = SDL_GetWindowFromID(Window::GetID());
    if (!window) return nullptr;
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    if (!renderer) return nullptr;

    return Engine::Texture::FromSDLTexture(SDL_CreateTextureFromSurface(renderer, data));
}

void Engine::Renderer::Deinitialize() {
    if (Renderer::__renderer) {
        SDL_DestroyRenderer(Renderer::__renderer);
        Renderer::__renderer = nullptr;
    }
    Texture::DestoryAllCreatedTextures();
}

//* Engine_Rendering.h


void Engine::Renderer::FillTexture(Engine::Texture* Texture) {
    if (!Texture || !Renderer::__renderer) return;
    if (!Texture->IsAvaliable()) return;
    SDL_RenderCopy(Renderer::__renderer, Texture->GetSDLTexture(), nullptr, nullptr);
}

void Engine::Renderer::DrawTexture(const Engine::Point& Position, Engine::Texture* Texture, double RotationAngle,
    bool HorizontalFlip, bool VerticalFlip) {

    if (!Texture || !Renderer::__renderer) return;
    if (!Texture->IsAvaliable()) return;

    Size tex_size = Texture->GetSize();
    if (tex_size.IsEmptyArea()) return;

    SDL_Rect dst_rect = {Position.X, Position.Y, tex_size.Width, tex_size.Height};
    SDL_RenderCopyEx(Renderer::__renderer, Texture->GetSDLTexture(), nullptr, &dst_rect, RotationAngle, nullptr,
        (SDL_RendererFlip)(((uint32_t)HorizontalFlip * SDL_FLIP_HORIZONTAL) | ((uint32_t)VerticalFlip * SDL_FLIP_VERTICAL)));
}
void Engine::Renderer::DrawTexture(const Engine::Rectangle& Area, Engine::Texture* Texture, double RotationAngle,
    bool HorizontalFlip, bool VerticalFlip) {
    
    if (!Texture || !Renderer::__renderer || Area.IsEmptyArea()) return;
    if (!Texture->IsAvaliable()) return;

    SDL_Rect dst_rect = {Area.LeftSide(), Area.TopSide(), abs(Area.Width), abs(Area.Height)};
    SDL_RenderCopyEx(Renderer::__renderer, Texture->GetSDLTexture(), nullptr, &dst_rect, RotationAngle, nullptr,
        (SDL_RendererFlip)(((uint32_t)HorizontalFlip * SDL_FLIP_HORIZONTAL) | ((uint32_t)VerticalFlip * SDL_FLIP_VERTICAL)));
}
void Engine::Renderer::DrawTexture(const Engine::Point& Position, Engine::Texture* Texture, const Engine::Point& Center, double RotationAngle,
    bool HorizontalFlip, bool VerticalFlip) {
        
    if (!Texture || !Renderer::__renderer) return;
    if (!Texture->IsAvaliable()) return;

    Size tex_size = Texture->GetSize();
    if (tex_size.IsEmptyArea()) return;

    SDL_Rect dst_rect = {Position.X, Position.Y, tex_size.Width, tex_size.Height};
    SDL_Point center = {Center.X, Center.Y};
    SDL_RenderCopyEx(Renderer::__renderer, Texture->GetSDLTexture(), nullptr, &dst_rect, RotationAngle, &center,
        (SDL_RendererFlip)(((uint32_t)HorizontalFlip * SDL_FLIP_HORIZONTAL) | ((uint32_t)VerticalFlip * SDL_FLIP_VERTICAL)));
}

void Engine::Renderer::DrawTexture(const Engine::Rectangle& Area, Engine::Texture* Texture, const Engine::Point& Center, double RotationAngle,
    bool HorizontalFlip, bool VerticalFlip) {
    
    if (!Texture || !Renderer::__renderer || Area.IsEmptyArea()) return;
    if (!Texture->IsAvaliable()) return;

    SDL_Rect dst_rect = {Area.LeftSide(), Area.TopSide(), abs(Area.Width), abs(Area.Height)};
    SDL_Point center = {Center.X, Center.Y};
    SDL_RenderCopyEx(Renderer::__renderer, Texture->GetSDLTexture(), nullptr, &dst_rect, RotationAngle, &center,
        (SDL_RendererFlip)(((uint32_t)HorizontalFlip * SDL_FLIP_HORIZONTAL) | ((uint32_t)VerticalFlip * SDL_FLIP_VERTICAL)));
}


void Engine::Renderer::DrawTextureUnscaled(const Engine::Rectangle& Area, Engine::Texture* Texture, const Engine::Point& Center, double RotationAngle,
    bool HorizontalFlip, bool VerticalFlip, Engine::RectangleAlignment Alignment) {

    if (!Texture || !Renderer::__renderer) return;
    if (!Texture->IsAvaliable()) return;

    Size tex_size = Texture->GetSize(), dest_size = Area.GetAbsoluteSize();
    if (tex_size.IsEmptyArea()) return;

    int target_x = Area.LeftSide(), target_y = Area.TopSide();

    switch (Alignment)
    {
    case Engine::RectangleAlignment::TopRight:
        target_x += abs(dest_size.Width) - abs(tex_size.Width);
        break;
    case Engine::RectangleAlignment::TopCenter:
        target_x += (abs(dest_size.Width) - abs(tex_size.Width)) / 2;
        break;
    case Engine::RectangleAlignment::MiddleLeft:
        target_y += (abs(dest_size.Height) - abs(tex_size.Height)) / 2;
        break;
    case Engine::RectangleAlignment::MiddleCenter:
        target_y += (abs(dest_size.Height) - abs(tex_size.Height)) / 2;
        target_x += (abs(dest_size.Width) - abs(tex_size.Width)) / 2;
        break;
    case Engine::RectangleAlignment::MiddleRight:
        target_y += (abs(dest_size.Height) - abs(tex_size.Height)) / 2;
        target_x += abs(dest_size.Width) - abs(tex_size.Width);
        break;
    case Engine::RectangleAlignment::BottomLeft:
        target_y += abs(dest_size.Height) - abs(tex_size.Height);
        break;
    case Engine::RectangleAlignment::BottomCenter:
        target_y += abs(dest_size.Height) - abs(tex_size.Height);
        target_x += (abs(dest_size.Width) - abs(tex_size.Width)) / 2;
        break;
    case Engine::RectangleAlignment::BottomRight:
        target_y += abs(dest_size.Height) - abs(tex_size.Height);
        target_x += abs(dest_size.Width) - abs(tex_size.Width);
        break;
    default:
        break;
    }

    Rectangle target_area = Rectangle(
        dest_size.Width <= tex_size.Width ? Area.LeftSide() : target_x,
        dest_size.Height <= tex_size.Height ? Area.TopSide() : target_y,
        ENGINE_MIN(dest_size.Width, tex_size.Width),
        ENGINE_MIN(dest_size.Height, tex_size.Height));

    dest_size = target_area.GetAbsoluteSize();

    int target_width = ENGINE_MIN(tex_size.Width, dest_size.Width), target_height = ENGINE_MIN(tex_size.Height, dest_size.Height);

    SDL_Rect src_rect = {0, 0, target_width, target_height};
    SDL_Rect dst_rect = {target_area.LeftSide(), target_area.TopSide(), target_width, target_height};
    SDL_Point center = {Center.X, Center.Y};

    SDL_RenderCopyEx(Renderer::__renderer, Texture->GetSDLTexture(), &src_rect, &dst_rect, RotationAngle, &center,
        (SDL_RendererFlip)(((uint32_t)HorizontalFlip * SDL_FLIP_HORIZONTAL) | ((uint32_t)VerticalFlip * SDL_FLIP_VERTICAL)));
}

void Engine::Renderer::DrawTextureUnscaled(const Engine::Rectangle& Area, Engine::Texture* Texture, double RotationAngle,
    bool HorizontalFlip, bool VerticalFlip, Engine::RectangleAlignment Alignment) {

    if (!Texture || !Renderer::__renderer) return;
    if (!Texture->IsAvaliable()) return;

    Size tex_size = Texture->GetSize(), dest_size = Area.GetAbsoluteSize();
    if (tex_size.IsEmptyArea()) return;

    int target_x = Area.LeftSide(), target_y = Area.TopSide();

    switch (Alignment)
    {
    case Engine::RectangleAlignment::TopRight:
        target_x += abs(dest_size.Width) - abs(tex_size.Width);
        break;
    case Engine::RectangleAlignment::TopCenter:
        target_x += (abs(dest_size.Width) - abs(tex_size.Width)) / 2;
        break;
    case Engine::RectangleAlignment::MiddleLeft:
        target_y += (abs(dest_size.Height) - abs(tex_size.Height)) / 2;
        break;
    case Engine::RectangleAlignment::MiddleCenter:
        target_y += (abs(dest_size.Height) - abs(tex_size.Height)) / 2;
        target_x += (abs(dest_size.Width) - abs(tex_size.Width)) / 2;
        break;
    case Engine::RectangleAlignment::MiddleRight:
        target_y += (abs(dest_size.Height) - abs(tex_size.Height)) / 2;
        target_x += abs(dest_size.Width) - abs(tex_size.Width);
        break;
    case Engine::RectangleAlignment::BottomLeft:
        target_y += abs(dest_size.Height) - abs(tex_size.Height);
        break;
    case Engine::RectangleAlignment::BottomCenter:
        target_y += abs(dest_size.Height) - abs(tex_size.Height);
        target_x += (abs(dest_size.Width) - abs(tex_size.Width)) / 2;
        break;
    case Engine::RectangleAlignment::BottomRight:
        target_y += abs(dest_size.Height) - abs(tex_size.Height);
        target_x += abs(dest_size.Width) - abs(tex_size.Width);
        break;
    default:
        break;
    }

    Rectangle target_area = Rectangle(
        dest_size.Width <= tex_size.Width ? Area.LeftSide() : target_x,
        dest_size.Height <= tex_size.Height ? Area.TopSide() : target_y,
        ENGINE_MIN(dest_size.Width, tex_size.Width),
        ENGINE_MIN(dest_size.Height, tex_size.Height));

    dest_size = target_area.GetAbsoluteSize();

    int target_width = ENGINE_MIN(tex_size.Width, dest_size.Width), target_height = ENGINE_MIN(tex_size.Height, dest_size.Height);

    SDL_Rect src_rect = {0, 0, target_width, target_height};
    SDL_Rect dst_rect = {target_area.LeftSide(), target_area.TopSide(), target_width, target_height};
    
    SDL_RenderCopyEx(Renderer::__renderer, Texture->GetSDLTexture(), &src_rect, &dst_rect, RotationAngle, nullptr,
        (SDL_RendererFlip)(((uint32_t)HorizontalFlip * SDL_FLIP_HORIZONTAL) | ((uint32_t)VerticalFlip * SDL_FLIP_VERTICAL)));
}

#endif // __ENGINE_IMAGING_H__