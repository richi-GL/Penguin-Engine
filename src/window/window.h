#pragma once

#include "gfx/gfx.h"

namespace Penguin
{

class Window {
private:
    GLFWwindow* window;
    
    
    int width;
    int height;
    const char* title;

    bool initGLFW();
    bool initGLAD();

public:
    bool isOpen;
    Window();
    ~Window();


    bool createWindow(int width, int height, const char* title);
    GLFWwindow* GetNativeWindow() const { return window; }
    void renderLoop();
    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();
    void cleanup();
};

}