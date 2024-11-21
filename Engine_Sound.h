#ifndef __ENGINE_SOUND_H__
#define __ENGINE_SOUND_H__

#include "Engine_Define.h"

#include <unordered_set>
#include <string>
#include <functional>
#include <SDL2/SDL_mixer.h>

namespace Engine {
    /// @brief The Sound class, represent a sound object. This can be use to managing and play sound (usually for sound
    /// effect).
    class Sound {
    private:
        Mix_Chunk* __data = nullptr;

        static bool __is_destroy_all;
        static std::unordered_set<Sound*> __created_sounds;
    protected:
        Sound(Mix_Chunk* chunk) : __data(chunk) { Sound::__created_sounds.insert(this); }
    public:
        /// @brief The name of the Sound object. Default is "Sound".
        std::string Name = "Sound";

        virtual ~Sound() {
            if (__data)
                Mix_FreeChunk(__data);
            __data = nullptr;
            if (!Sound::__is_destroy_all)
                Sound::__created_sounds.erase(this);
        }

        ENGINE_NOT_COPYABLE(Sound)
        ENGINE_NOT_ASSIGNABLE(Sound)

        /// @brief Check if the data of the Sound is avaliable.
        /// @return true if the data is avaliable, false otherwise.
        bool IsAvaliable() const { return (bool)__data; }


        /// @brief Play the given sound on a channel.
        /// @param sound The Sound to play.
        /// @param loop_count The number of loop to play (default is 0 mean not looping), or -1 to loop (not actually)
        /// infinitely.
        /// @param channel The channel to play. If -1 (default), will play on the first free channel.
        /// @return The channel that the sound is play, or -1 on failed.
        static int PlaySound(Sound* sound, int loop_count = 0, int channel = -1) {
            if (!sound) return -1;
            if (!sound->__data) return -1;
            return Mix_PlayChannel(channel, sound->__data, loop_count);
        }

        /// @brief Pause a channel.
        /// @param channel The channel to pause, or -1 to pause all channel.
        static void PauseChannel(int channel) { Mix_Pause(channel); }
        /// @brief Resume a channel.
        /// @param channel The channel to resume, or -1 to resume all channel.
        static void ResumeChannel(int channel) { Mix_Resume(channel); }
        /// @brief Check if a channel is paused.
        /// @param channel The channel to check, or -1 to check all channel.
        /// @return 1 if the given channel is pause, 0 if not. Will return the number of paused channel if -1 is given.
        static int IsChannelPaused(int channel) { return Mix_Paused(channel); }
        /// @brief Check if a channel is playing.
        /// @param channel The channel to check, or -1 to check all channel.
        /// @return 1 if the given channel is pause, 0 if not. Will return the number of playing channel if -1 is given.
        static int IsChannelPlaying(int channel) { return Mix_Playing(channel); }
        /// @brief Halt/stop a channel from playing.
        /// @param channel The channel to halt, or -1 to halt all channel.
        static void HaltChannel(int channel) { Mix_HaltChannel(channel); }

        /// @brief Load a Sound from a file.
        /// @param file_path The file path of the sound file to load.
        /// @return The newly created Sound, or nullptr on failed.
        static Sound* FromFile(const char* file_path) { return FromMixChunk(Mix_LoadWAV(file_path)); }
        /// @brief Create a new Sound from the given Mix_Chunk.
        /// @param chunk The Mix_Chunk to create.
        /// @return The newly created Sound, or nullptr if the given Mix_Chunk is null.
        static Sound* FromMixChunk(Mix_Chunk* chunk) { return chunk ? new Sound(chunk) : nullptr; }

        /// @brief Execute an action for each created Sound.
        /// @param action The action to execute.
        /// @return The number of Sound that called with the given action.
        static size_t ForEachSound(const std::function<void(Sound*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (Sound* sound : Sound::__created_sounds)
                if (sound) { action(sound); count++; }

            return count;
        }
        /// @brief Execute an action for each created Sound, if the Sound is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Sound that called with the given action.
        static size_t ForEachSoundIf(const std::function<void(Sound*)>& action, const std::function<bool(Sound*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachSound(action);
            size_t count = 0;
            for (Sound* sound : Sound::__created_sounds) {
                if (!sound) continue;
                if (!predicate(sound)) continue;
                action(sound); count++;
            }

            return count;
        }
        /// @brief Find the first created Sound with the given name.
        /// @param name The name to find.
        /// @return The first Sound with the given name, or nullptr if not found.
        static Sound* FindSound(const std::string& name) {
            for (Sound* obj : Sound::__created_sounds) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first created Sound that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Sound that satisfied the given predicate, or nullptr if no Sound satisfied.
        static Sound* FindSoundIf(const std::function<bool(Sound*)>& predicate) {
            if (!predicate) return nullptr;
            for (Sound* obj : Sound::__created_sounds) {
                if (!obj) continue;
                if (predicate(obj)) return obj;
            }
            return nullptr;
        }

        /// @brief Destroy all created Sounds. This will be called on Engine::Deinitialize().
        static void DestroyAllCreatedSounds() {
            Sound::__is_destroy_all = true;
            for (Sound* sound : Sound::__created_sounds)
                if (sound) delete sound;
            Sound::__created_sounds.clear();
            Sound::__is_destroy_all = false;
        }
    };
    /// @brief The Music class, represent a music object. This can also be use to managing and play music.
    class Music {
    private:
        Mix_Music* __data = nullptr;

        static bool __is_destroy_all;
        static std::unordered_set<Music*> __created_musics;
    protected:
        Music(Mix_Music* music) : __data(music) { Music::__created_musics.insert(this); }
    public:
        /// @brief The name of the Music object. Default to "Music".
        std::string Name = "Music";

        virtual ~Music() {
            if (__data) Mix_FreeMusic(__data);
            __data = nullptr;
            if (!Music::__is_destroy_all) Music::__created_musics.erase(this);
        }

        ENGINE_NOT_ASSIGNABLE(Music)
        ENGINE_NOT_COPYABLE(Music)



        //TODO: Continue on music.
        
        /// @brief Load a Music from a file.
        /// @param file_path The file path of the sound file to load.
        /// @return The newly created Music, or nullptr on failed.
        static Music* FromFile(const char* file_path) { return FromMixChunk(Mix_LoadWAV(file_path)); }
        /// @brief Create a new Music from the given Mix_Chunk.
        /// @param chunk The Mix_Chunk to create.
        /// @return The newly created Music, or nullptr if the given Mix_Chunk is null.
        static Music* FromMixChunk(Mix_Chunk* chunk) { return chunk ? new Music(chunk) : nullptr; }

        /// @brief Execute an action for each created Music.
        /// @param action The action to execute.
        /// @return The number of Music that called with the given action.
        static size_t ForEachMusic(const std::function<void(Music*)>& action) {
            if (!action) return 0;
            size_t count = 0;
            for (Music* music : Music::__created_musics)
                if (music) { action(music); count++; }

            return count;
        }
        /// @brief Execute an action for each created Music, if the Music is satisfied the given predicate.
        /// @param action The action to execute.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The number of Music that called with the given action.
        static size_t ForEachMusicIf(const std::function<void(Music*)>& action, const std::function<bool(Music*)>& predicate) {
            if (!action) return 0;
            if (!predicate) return ForEachMusic(action);
            size_t count = 0;
            for (Music* music : Music::__created_musics) {
                if (!music) continue;
                if (!predicate(music)) continue;
                action(music); count++;
            }

            return count;
        }
        /// @brief Find the first created Music with the given name.
        /// @param name The name to find.
        /// @return The first Music with the given name, or nullptr if not found.
        static Music* FindMusic(const std::string& name) {
            for (Music* obj : Music::__created_musics) {
                if (!obj) continue;
                if (obj->Name == name)
                    return obj;
            }
            return nullptr;
        }
        /// @brief Find the first created Music that satisfied the given predicate.
        /// @param predicate The predicate to check (return true if satisfy).
        /// @return The first Music that satisfied the given predicate, or nullptr if no Music satisfied.
        static Music* FindMusicIf(const std::function<bool(Music*)>& predicate) {
            if (!predicate) return nullptr;
            for (Music* obj : Music::__created_musics) {
                if (!obj) continue;
                if (predicate(obj)) return obj;
            }
            return nullptr;
        }

        /// @brief Destroy all created Music objects. This will be called on Engine::Deinitialize().
        static void DestroyAllCreatedMusics() {
            Music::__is_destroy_all = true;
            for (Music* music : Music::__created_musics)
                if (music) delete music;
            Music::__created_musics.clear();
            Music::__is_destroy_all = false;
        }
    };
}

bool Engine::Sound::__is_destroy_all = false;
std::unordered_set<Engine::Sound*> Engine::Sound::__created_sounds = std::unordered_set<Engine::Sound*>();

#endif // __ENGINE_SOUND_H__