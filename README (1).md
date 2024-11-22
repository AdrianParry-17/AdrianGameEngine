
# Tutorial 1 - Game Object/Scene

So, after the first tutorial, you probably want to do something with the game (like adding something, or just change the background color).

Well, here we will talk about the basic of that.

First, in the tutorial code, let's declare a function.

```cpp
// Return false on fail to initialize.
bool InitializeGame();
```

Then, on the main function, we call this function after initialize the Engine but before running.

```cpp
...
if (!Engine::Initialize())
    return false;

// Initialize the game. On success, will start the game.
if (InitializeGame())
    Engine::Application::Start();
...
```

And we moved the definition of the ```InitializeGame``` function to the bottom for easier to look.

Inside the ```InitializeGame``` function is where we'll initialize the game resources (image, font) and components (game objects/scenes, ...).




