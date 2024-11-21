
# Adrian Game Engine

A basic game engine that can be use to make game. Mainly use SDL2 and other SDL library such as SDL2_image, SDL2_ttf, SDL2_gfx and SDL2 mixer.
## How to install

Firstly, you need to install all required library, which is:

+ SDL2
+ SDL2_image  (For rendering image)
+ SDL2_ttf    (For rendering text)
+ SDL2_gfx    (For drawing primitive)
+ SDL2_mixer  (For sound/music)

And to install these library, there's a lot of tutorial on the internet for that. For example, with msys2-gcc, you can just simply use ```pacman```

On MSYS2 UCRT64 terminal.

```bash
    pacman -S mingw-w64-ucrt-x86_64-SDL2
    pacman -S mingw-w64-ucrt-x86_64-SDL2_image
    pacman -S mingw-w64-ucrt-x86_64-SDL2_ttf
    pacman -S mingw-w64-ucrt-x86_64-SDL2_gfx
    pacman -S mingw-w64-ucrt-x86_64-SDL2_mixer
```

After that, you can download the zip file you download from the Release. Just extract all file into a folder named ```Engine``` in the same directory of your source file and you're ready to go.


## Tutorial

Firstly, you need to include the main file of the library (which is ```Engine.h```), your code should be look like this:

```cpp
#include "Engine/Engine.h"

int main(int argc, char* argv[]) {

    return 0;
}
```

Then, you MUST initialize the library (otherwise you can't use it!). But before that, you may want to set the properties in the ```Engine::Application``` class before using it.

```cpp
// Set to false if you want to render the window manually.
Engine::Application::RenderingScene = true;
// Limiting the FPS that match the vertical refresh rate.
Engine::Application::EnableVSyncPresent = true;

// The name of the Application (also the title of the Window)
// when creating it.
Engine::Application::Name = "Game";
// The flags of the Window when create, OR's together.
// In this case, the window is hidden and resizable.
Engine::Application::WindowFlags = 
    Engine::WindowFlags::Hidden | Engine::WindowFlags::Resizable;
// The size of the Window when create.
Engine::Application::DefaultWindowSize = Engine::Size(800, 500);
```

And now you can finally initialize and start the game.

```cpp
// Initialize, and also return 1 (EXIT_FAILURE) on failed.
if (!Engine::Initialize())
    return 1;

// Start the application.
Engine::Application::Start();

// Deinitialize the Engine, this will also destroyed all created Engine object.
Engine::Deinitialize();
```

But wait! When you run the code, the window didn't appear and you can't stop the application!

This is when the event came! Basically, you need to make custom event actions for that, let's create some event actions.

```cpp
// This will be called when the application is about to run (before enter the main loop).
void OnLoad(Engine::EventArgs *args)
{
    // Make the window visible.
    Engine::Window::Show();
}
// This will be called when the application is about to stop running (after exiting the main loop).
void OnUnload(Engine::EventArgs *args)
{
    // Make the window not visible.
    Engine::Window::Hide();
}
// This will be called on every frame when the application is updating (before updating the Game Scene).
void OnUpdate(Engine::EventArgs *args)
{
    // Global updating for every frame goes here...
}
```

Now, let's register these event actions. You can register an event action in various ways.

```cpp
// Register the 'OnLoad' event functions.
Engine::Application::LoadEvent += OnLoad;
// Register the 'OnUnload' event functions.
Engine::Application::UnloadEvent += OnUnload;
// Register the 'OnUpdate' event functions.
Engine::Application::UpdateEvent.Register(OnUpdate);

// For stoping the Application when user request close. Of course,
// you can also use lambda function as soon as it match the event
// function type.
Engine::Window::RequestCloseEvent += [](Engine::EventArgs* args) {
    // Signal the Application to stop on next update.
    Engine::Application::Stop();
};
```

Now, let's try to run the code again. And finally, an empty window popup and now we can close it.

Here is the code of the tutorial.

```cpp
#include "Engine/Engine.h"

// This will be called when the application is about to run (before enter the main loop).
void OnLoad(Engine::EventArgs *args)
{
    // Make the window visible.
    Engine::Window::Show();
}
// This will be called when the application is about to stop running (after exiting the main loop).
void OnUnload(Engine::EventArgs *args)
{
    // Make the window not visible.
    Engine::Window::Hide();
}
// This will be called on every frame when the application is updating (before updating the Game Scene).
void OnUpdate(Engine::EventArgs *args)
{
    // Global updating for every frame goes here...
}

int main(int argc, char* argv[]) {
    // Set to false if you want to render the window manually.
    Engine::Application::RenderingScene = true;
    // Limiting the FPS that match the vertical refresh rate.
    Engine::Application::EnableVSyncPresent = true;

    // The name of the Application (also the title of the Window)
    // when creating it.
    Engine::Application::Name = "Game";
    // The flags of the Window when create, OR's together.
    // In this case, the window is hidden and resizable.
    Engine::Application::WindowFlags = 
        Engine::WindowFlags::Hidden | Engine::WindowFlags::Resizable;
    // The size of the Window when create.
    Engine::Application::DefaultWindowSize = Engine::Size(800, 500);

    // Register the 'OnLoad' event functions.
    Engine::Application::LoadEvent += OnLoad;
    // Register the 'OnUnload' event functions.
    Engine::Application::UnloadEvent += OnUnload;
    // Register the 'OnUpdate' event functions.
    Engine::Application::UpdateEvent.Register(OnUpdate);
    // For stoping the Application when user request close. Of course,
    // you can also use lambda function as soon as it match the event
    // function type.
    Engine::Window::RequestCloseEvent += [](Engine::EventArgs* args) {
        // Signal the Application to stop on next update.
        Engine::Application::Stop();
    };


    // Initialize, and also return 1 (EXIT_FAILURE) on failed.
    if (!Engine::Initialize())
        return 1;

    // Start the application.
    Engine::Application::Start();

    // Deinitialize the Engine, this will also destroyed all created Engine object.
    Engine::Deinitialize();

    return 0;
}

```


## Lessons Learned

While the Engine is still unfinished, I realized making an Engine is really hard!

