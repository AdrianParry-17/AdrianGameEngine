#ifndef __ENGINE_FONT_H__
#define __ENGINE_FONT_H__

#include "Engine_Imaging.h"
#include "Engine_Renderer.h"

#include <SDL2/SDL_ttf.h>
#include <unordered_map>

namespace Engine {
    /// @brief The Font class, provide a base class to create an Engine font.
    class Font {
    private:
        int __min_line_height = 0;
        int __letter_spacing = 0;

        static bool __is_destroy_all;
        static std::unordered_set<Font*> __created_fonts;
    protected:
        /// @brief Get the texture of a single character.
        /// @param character The character to query.
        /// @return The texture of the given character, or nullptr if there's none.
        /// @note On overriding, this should return an grayscale texture 
        virtual Texture* GetCharacterTexture(char character) = 0;
        /// @brief Get the texture size of a single character.
        /// @param character The character to query.
        /// @return The texture size of the given character, or Size::Zero if there's none.
        virtual Size GetCharacterTextureSize(char character) {
            Texture* text = GetCharacterTexture(character);
            return text ? text->GetSize() : Size::Zero;
        }
    public:
        /// @brief The name of the Font. Default is "Font".
        std::string Name = "Font";

        Font() { Font::__created_fonts.insert(this); }
        virtual ~Font() {
            if (!Font::__is_destroy_all)
                Font::__created_fonts.erase(this);
        }

        ENGINE_NOT_COPYABLE(Font)
        ENGINE_NOT_ASSIGNABLE(Font)

        //TODO: Probably add render with wrapping (on newline and reach max width).

        /// @brief Get the minimum height in pixels of a line when rendering with this Font.
        /// @return The minimum height of a line when rendering with this Font. 0 on default.
        int GetLineMinimumHeight() const { return __min_line_height; }
        /// @brief Set the minimum height in pixels of a line when rendering with this Font.
        /// @param min_line_height The minimum height to set, will clamped to be at least 0.
        void SetLineMinimumHeight(int min_line_height) { __min_line_height = min_line_height < 0 ? 0 : min_line_height; }

        /// @brief Get the distance in pixels between two consecutive letter when rendering with this Font.
        /// @return The distance in pixels between two consecutive letter when rendering with this Font. 0 on default.
        int GetLetterSpacing() const { return __letter_spacing; }
        /// @brief Get the distance in pixels between two consecutive letter when rendering with this Font.
        /// @param spacing The spacing distance to set, will be clamped to be at least 0.
        void SetLetterSpacing(int spacing) { __letter_spacing = spacing < 0 ? 0 : spacing; }

        /// @brief Calculate the possible output size when rendering the given text with this Font on a single line (meaning
        /// will not go to newline when met the newline '\n' character).
        /// @param Text The text to calculate the output size.
        /// @return The result of the calculation. Or Size::Zero if the given text is empty.
        virtual Size CalculateOutputSizeSingleLine(const std::string& Text) {
            if (Text.empty())
                return Size::Zero;
            int res_w = 0, res_h = __min_line_height;

            for (char c : Text) {
                Size c_size = GetCharacterTextureSize(c);
                res_w += c_size.Width + __letter_spacing;
                res_h = ENGINE_MAX(res_h, c_size.Height);
            }

            return Size(res_w - __letter_spacing, res_h);
        }
        /// @brief Calculate the possible output size when rendering the given text with newline wrapping (meaning will go to newline
        /// when met the newline '\n' character).
        /// @param Text The text to calculate the output size.
        /// @return The result of the calculation. Or Size::Zero if the given text is empty.
        virtual Size CalculateOutputSizeMultiline(const std::string& Text) {
            if (Text.empty())
                return Size::Zero;
            int res_w = 0, res_h = __min_line_height;
            int curr_x = 0, curr_y = 0;

            for (char c : Text) {
                if (c == '\n') {
                    curr_x = 0; curr_y = res_h;
                    res_h += __min_line_height;
                    continue;
                }
                Size c_size = GetCharacterTextureSize(c);
                curr_x += c_size.Width + __letter_spacing;
                if (res_w < curr_x)
                    res_w = curr_x;
                res_h = ENGINE_MAX(res_h, curr_y + c_size.Height);
            }
            res_w -= __letter_spacing;
            return Size(res_w < 0 ? 0 : res_w, res_h);
        }

        /// @brief Render the given text with this Font on a single line (meaning will not go to newline when met the newline '\n'
        /// character).
        /// @param Text The text to render.
        /// @param Position The position of the top-left corner of the text area to render.
        /// @param ModColor The additional color value that will be multiply for each pixel from the original character texture on
        /// rendering operation (draw_color = source_color * (mod_color / 255)). This can be treated as foreground color of the text
        /// if the texture of each character of the text is grayscale texture. Default is White (255, 255, 255, 255).
        virtual void RenderSingleLine(const std::string& Text, const Point& Position, Color ModColor = KnownColor::White) {
            if (Text.empty()) return;
            
            int target_height = __min_line_height;
            std::unordered_map<char, Texture*> __textures;
            // Initial char Texture required to render the line, also calculate the height.

            for (char c : Text) {
                if (__textures.count(c) != 0)
                    continue;
                Texture* c_texture = GetCharacterTexture(c);
                if (!c_texture) continue;
                if (!c_texture->IsAvaliable()) continue;
                
                Size c_tex_size = c_texture->GetSize();
                if (c_tex_size.Height > target_height)
                    target_height = c_tex_size.Height;
                
                __textures[c] = c_texture;
            }

            // Drawing text

            int curr_x = Position.X;

            for (char c : Text) {
                if (__textures.count(c) == 0)
                    continue;
                Texture* c_texture = __textures[c];
                Size c_tex_size = c_texture->GetSize();

                Color curr_mod = c_texture->GetColorMod();
                c_texture->SetColorMod(ModColor);

                Renderer::DrawTexture(
                    Point(curr_x, Position.Y + (target_height - c_tex_size.Height)),
                    c_texture);

                c_texture->SetColorMod(curr_mod);
                
                curr_x += c_tex_size.Width + __letter_spacing;
            }
        }

        virtual void RenderMultiline(const std::string& Text, const Point& Position, Color ModColor = KnownColor::White) {
            if (Text.empty()) return;

            int curr_y = Position.Y;

            std::unordered_map<char, Texture*> __textures;

            auto ptr = Text.begin();
            while (ptr != Text.end()) {
                int target_height = __min_line_height;
                // Calculate line height (also initialize required character Texture).
                for (auto p = ptr; p != Text.end() && *p != '\n'; ++p) {
                    char c = *p;
                    Texture* c_texture = nullptr;
                    if (__textures.count(c) != 0) {
                        c_texture = __textures[c];
                        if (!c_texture) __textures.erase(c);
                        else if (!c_texture->IsAvaliable()) {
                            delete c_texture;
                            c_texture = nullptr;
                            __textures.erase(c);
                        }
                    }
                    if (!c_texture) {
                        c_texture = GetCharacterTexture(c);
                        if (!c_texture) continue;
                        if (!c_texture->IsAvaliable()) continue;
                    }

                    Size c_tex_size = c_texture->GetSize();
                    if (c_tex_size.Height > target_height)
                        target_height = c_tex_size.Height;

                    __textures[c] = c_texture;
                }

                // Drawing line text

                int curr_x = Position.X;
                for (; ptr != Text.end() && *ptr != '\n'; ++ptr) {
                    char c = *ptr;
                    if (__textures.count(c) == 0)
                        continue;
                    Texture* c_texture = __textures[c];
                    Size c_tex_size = c_texture->GetSize();

                    Color curr_mod = c_texture->GetColorMod();
                    c_texture->SetColorMod(ModColor);

                    Renderer::DrawTexture(Point(curr_x, curr_y + (target_height - c_tex_size.Height)), c_texture);

                    c_texture->SetColorMod(curr_mod);

                    curr_x += c_tex_size.Width + __letter_spacing;
                }

                if (ptr != Text.end()) {
                    ++ptr;
                    curr_y += target_height;
                }
            }
        }

        /// @brief Execute an action for each created Font.
        /// @param action The action to execute.
        /// @return The number of Font that called with the given action.
        static size_t ForEachFont(const std::function<void(Font*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (Font* scene : Font::__created_fonts)
                if (scene) { action(scene); count++; }

            return count;
        }
        /// @brief Execute an action for each created Font, if the Font is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Font that called with the given action.
        static size_t ForEachFontIf(const std::function<void(Font*)>& action, const std::function<bool(Font*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachFont(action);
            size_t count = 0;
            for (Font* scene : Font::__created_fonts) {
                if (!scene) continue;
                if (!predicate(scene)) continue;
                action(scene); count++;
            }

            return count;
        }
        /// @brief Find the first created Font with the given name.
        /// @param name The name to find.
        /// @return The first Font with the given name, or nullptr if not found.
        static Font* FindFont(const std::string& name) {
            for (Font* obj : Font::__created_fonts) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first created Font that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Font that satisfied the given predicate, or nullptr if no Font satisfied.
        static Font* FindFontIf(const std::function<bool(Font*)>& predicate) {
            if (!predicate) return nullptr;
            for (Font* obj : Font::__created_fonts) {
                if (!obj) continue;
                if (predicate(obj)) return obj;
            }
            return nullptr;
        }

        /// @brief Destroy all created Fonts, this will be called on Engine::Deinitialize().
        static void DestroyAllCreatedFonts() {
            Font::__is_destroy_all = true;
            for (Font* font : Font::__created_fonts)
                if (font) delete font;
            Font::__created_fonts.clear();
            Font::__is_destroy_all = false;
        }
    };

    /// @brief The Textured Font class, provide a Font where each character of the font is supplied by a Texture.
    class TexturedFont : public Font {
    private:
        std::unordered_map<char, Texture*> __char_textures;
    protected:
        Texture* GetCharacterTexture(char character) override {
            if (__char_textures.count(character) == 0)
                return nullptr;
            return __char_textures[character];
        }
    public:
        /// @brief If this true, will destroy all allocated textures of the Textured Font when the Textured Font is destroyed.
        /// Default is false.
        bool DestroyAllTexturesOnDestroyed = false;

        /// @brief Create a new empty Textured Font with no texture allocated.
        TexturedFont() = default;
        virtual ~TexturedFont() {
            if (DestroyAllTexturesOnDestroyed) {
                for (auto pair : __char_textures)
                    if (pair.second) delete pair.second;
                __char_textures.clear();
            }
            Font::~Font();
        }

        ENGINE_NOT_COPYABLE(TexturedFont)
        ENGINE_NOT_ASSIGNABLE(TexturedFont)

        /// @brief Get the number of texture allocated to this Textured Font.
        /// @return The number of texture allocated to this Textured Font.
        size_t Count() const { return __char_textures.size(); }

        /// @brief Set the texture use to render the given character.
        /// @param character The character to set.
        /// @param texture The texture to set, should be grayscale. If this null or not avaliable, will just only
        /// remove the texture that allocated with the given character.
        void SetCharacterTexture(char character, Texture* texture) {
            if (texture) {
                if (texture->IsAvaliable()) { __char_textures[character] = texture; return; }
            }
            __char_textures.erase(character);
        }
        /// @brief Check if there's a texture use to render the given character.
        /// @param character The characted to check.
        /// @return true if there's a texture use to render the given character, or false if there isn't.
        bool IsHasTextureFor(char character) const { return __char_textures.count(character) != 0; }
    };

    /// @brief Usually for define hinting for a TTFFont (FreeType hinting).
    enum class TTFFontHinting {
        /// @brief No hinting.
        None = TTF_HINTING_NONE,
        Normal = TTF_HINTING_NORMAL,
        Light = TTF_HINTING_LIGHT,
        Mono = TTF_HINTING_MONO,
        LightSubpixel = TTF_HINTING_LIGHT_SUBPIXEL
    };

    /// @brief Usually for define the method that used for rendering with a TTFFont.
    enum class TTFFontRenderMethod {
        /// @brief Solid rendering, fast quality method.
        Soild = 0,
        /// @brief Blended rendering, high quality method.
        Blended = 1
    };

    /// @brief Usually for define one or more (or'd together) TTFFont style.
    enum class TTFFontStyle {
        /// @brief Normal font style.
        Normal = TTF_STYLE_NORMAL,
        /// @brief Bold font style.
        Bold = TTF_STYLE_BOLD,
        /// @brief Italic font style.
        Italic = TTF_STYLE_ITALIC,
        /// @brief Underline font style.
        Underline = TTF_STYLE_UNDERLINE,
        /// @brief Strikethrough font style.
        Strikethrough = TTF_STYLE_STRIKETHROUGH
    };

    /// @brief The TTFFont class, provide a Font that using a true type font.
    class TTFFont : public Font {
    private:
        TTF_Font* __font = nullptr;
        std::unordered_map<char, Texture*> __char_textures;
        TTFFontRenderMethod __render_method = TTFFontRenderMethod::Soild;
    protected:
        Texture* GetCharacterTexture(char character) override {
            if (character == '\n') return nullptr;
            Texture* res_tex = nullptr;
            if (__char_textures.count(character) != 0) {
                res_tex = __char_textures[character];
                if (res_tex)
                    if (res_tex->IsAvaliable()) return res_tex;
            }

            if (res_tex)
                delete res_tex;
            if (!__font) return nullptr;
            if (!Window::IsInitialized()) return nullptr;
            if (!Renderer::IsInitialized()) return nullptr;
            
            SDL_Window* window = SDL_GetWindowFromID(Window::GetID());
            if (!window) return nullptr;
            SDL_Renderer* renderer = SDL_GetRenderer(window);
            if (!renderer) return nullptr;

            SDL_Surface* c_surface = nullptr;
            switch (__render_method)
            {
            case TTFFontRenderMethod::Blended:
                c_surface = TTF_RenderGlyph_Blended(__font, character, SDL_Color{255, 255, 255, 255});
                break;
            
            default:
                c_surface = TTF_RenderGlyph_Solid(__font, character, SDL_Color{255, 255, 255, 255});
                break;
            }

            if (!c_surface) return nullptr;

            Texture* c_texture = Texture::FromSDLTexture(SDL_CreateTextureFromSurface(renderer, c_surface));
            SDL_FreeSurface(c_surface);

            if (!c_texture) return nullptr;
            __char_textures[character] = c_texture;
            return c_texture;
        }
        Size GetCharacterTextureSize(char character) override {
            if (character == '\n') return Size::Zero;
            Texture* tex = nullptr;
            if (__char_textures.count(character) != 0) {
                tex = __char_textures[character];
                if (tex)
                    if (tex->IsAvaliable()) return tex->GetSize();
            }
            if (tex) { delete tex; __char_textures.erase(character); }
            if (!__font) return Size::Zero;
            Size res = Size::Zero;
            if (TTF_SizeUTF8(__font, std::string(1, character).c_str(), &res.Width, &res.Height) != 0)
                return Size::Zero;
            return res;
        }

        TTFFont(TTF_Font* font) : __font(font) {}
    public:
        virtual ~TTFFont() {
            for (auto& pair : __char_textures)
                if (pair.second) delete pair.second;
            __char_textures.clear();
            if (__font) TTF_CloseFont(__font);
            Font::~Font();
        }

        ENGINE_NOT_COPYABLE(TTFFont)
        ENGINE_NOT_ASSIGNABLE(TTFFont)

        /// @brief Check if the data of the TTFFont is avaliable.
        /// @return true if the data is avaliable, false otherwise.
        bool IsAvaliable() const { return (bool)__font; }

        /// @brief Destroy all generated glyphs of the TTFFont.
        void DestroyAllGeneratedGlyphs() {
            for (auto& pair : __char_textures)
                if (pair.second) delete pair.second;
            __char_textures.clear();
        }

        /// @brief Get the family name of the font.
        /// @return The family name of the font, will return empty string ("") on failed.
        /// Notice that the returned string will become invalid once the Font is released.
        const char* GetFontFamilyName() const { return __font ? TTF_FontFaceFamilyName(__font) : ""; }
        /// @brief Get the style name of the font.
        /// @return The style name of the font, will return empty string ("") on failed.
        /// Notice that the returned string will become invalid once the Font is released.
        const char* GetFontStyleName() const { return __font ? TTF_FontFaceStyleName(__font) : ""; }
        /// @brief Get the number of FreeType font faces of the font.
        /// @return The number of font faces, will return 0 on failed.
        uint32_t CountFaces() const { return __font ? TTF_FontFaces(__font) : 0; }
        /// @brief Check if the font is fixed-width (mean all glyphs are the same width).
        /// @return true if the font is fixed-width, false otherwise.
        bool IsFixedWidth() const { return __font ? TTF_FontFaceIsFixedWidth(__font) != 0 : false; }
        /// @brief Get the total height of the font.
        /// @return The height of the font, usually equal to point size.
        uint32_t GetFontHeight() const { return __font ? TTF_FontHeight(__font) : 0; }
        /// @brief Get the hinting of the font.
        /// @return The hinting of the font, will return None on failed.
        TTFFontHinting GetFontHinting() const {
            return __font ? (TTFFontHinting)TTF_GetFontHinting(__font) : TTFFontHinting::None;
        }
        /// @brief Get the render method of the font.
        /// @return The current render method of the font.
        TTFFontRenderMethod GetRenderMethod() const { return __render_method; }

        /// @brief Get the hinting of the font. This will destroy all generated glyphs.
        /// @param hinting The hinting of the font to set
        void SetFontHinting(TTFFontHinting hinting) { 
            if (__font) TTF_SetFontHinting(__font, (uint32_t)hinting);
            DestroyAllGeneratedGlyphs();
        }
        /// @brief Set the style of the font. This will destroy all generated glyphs.
        /// @param style One or more value of FontStyle or'd together to set.
        void SetFontStyle(TTFFontStyle style) {
            if (__font) TTF_SetFontStyle(__font, (int)style);
            DestroyAllGeneratedGlyphs();
        }
        /// @brief Set the current font size. This will destroy all generated glyphs.
        /// @param size The font size to set.
        void SetFontSize(uint32_t size) {
            if (__font) TTF_SetFontSize(__font, (int)size);
            DestroyAllGeneratedGlyphs();
        }
        /// @brief Set the render method of the font. This will destroy all generated glyphs.
        /// @param method The render method to set.
        void SetRenderMethod(TTFFontRenderMethod method) {
            __render_method = method;
            DestroyAllGeneratedGlyphs();
        }

        /// @brief Render the given text to a Color Map, this will only wrapped on newline.
        /// @param Text The text to render. If this empty, will return nullptr.
        /// @param Color The foreground color of the text to render.
        /// @return The result Color Map, or nullptr on failed.
        ColorMap* RenderToColorMap(const std::string& Text, const Engine::Color& Color) {
            if (!__font) return nullptr;
            if (Text.empty()) return nullptr;

            SDL_Surface* result = nullptr;
            switch (__render_method)
            {
            case TTFFontRenderMethod::Blended:
                result = TTF_RenderUTF8_Blended_Wrapped(__font, Text.c_str(),
                    SDL_Color{Color.Red, Color.Green, Color.Blue, Color.Alpha}, 0);
                break;
            
            default:
                result = TTF_RenderUTF8_Solid_Wrapped(__font, Text.c_str(),
                    SDL_Color{Color.Red, Color.Green, Color.Blue, Color.Alpha}, 0);
                break;
            }

            if (!result) return nullptr;
            return ColorMap::FromSDLSurface(result);
        }

        /// @brief Render the given text to a Texture, this will only wrapped on newline.
        /// @param Text The text to render. If this empty, will return nullptr.
        /// @param Color The foreground color of the text to render.
        /// @return The result Texture, or nullptr on failed.
        Texture* RenderToTexture(const std::string& Text, const Engine::Color& Color) {
            if (!__font) return nullptr;
            if (Text.empty()) return nullptr;
            if (!Window::IsInitialized()) return nullptr;
            if (!Renderer::IsInitialized()) return nullptr;

            SDL_Surface* result = nullptr;
            switch (__render_method)
            {
            case TTFFontRenderMethod::Blended:
                result = TTF_RenderUTF8_Blended_Wrapped(__font, Text.c_str(),
                    SDL_Color{Color.Red, Color.Green, Color.Blue, Color.Alpha}, 0);
                break;
            
            default:
                result = TTF_RenderUTF8_Solid_Wrapped(__font, Text.c_str(),
                    SDL_Color{Color.Red, Color.Green, Color.Blue, Color.Alpha}, 0);
                break;
            }

            if (!result) return nullptr;

            SDL_Window* window = SDL_GetWindowFromID(Window::GetID());
            if (!window) return nullptr;
            SDL_Renderer* renderer = SDL_GetRenderer(window);
            if (!renderer) return nullptr;

            SDL_Texture* result_tex = SDL_CreateTextureFromSurface(renderer, result);
            SDL_FreeSurface(result);

            return Texture::FromSDLTexture(result_tex);
        }

        /// @brief Create a new TTFFont from a ttf file.
        /// @param file_path The path of the ttf file to create.
        /// @param ptsize The font size to create.
        /// @return The newly created TTFFont from the ttf file, or nullptr on failed.
        static TTFFont* FromFile(const char* file_path, int ptsize) {
            if (!file_path) return nullptr;

            return FromTTFFont(TTF_OpenFont(file_path, ptsize));
        }
        /// @brief Create a new TTFFont from the given TTF_Font.
        /// @param font The font to create.
        /// @return The result TTFFont that allocated the given font to, or nullptr if the given
        /// font is null or failed.
        static TTFFont* FromTTFFont(TTF_Font* font) { return font ? new TTFFont(font) : nullptr; }
    };
}

bool Engine::Font::__is_destroy_all = false;
std::unordered_set<Engine::Font*> Engine::Font::__created_fonts = std::unordered_set<Engine::Font*>();

#endif // __ENGINE_FONT_H__