#include "window.h"
#include <iostream>

namespace Penguin
{

Window::Window() : window(nullptr), width(0), height(0), title(nullptr) {}

Window::~Window() {
    cleanup();
}

bool Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Error: No se pudo inicializar GLFW" << std::endl;
        return false;
    }
    
    // Configurar propiedades de contexto OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    return true;
}

bool Window::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error: No se pudo inicializar GLAD" << std::endl;
        return false;
    }
    return true;
}

bool Window::createWindow(int w, int h, const char* t) {
    width = w;
    height = h;
    title = t;

    if (!initGLFW()) {
        return false;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Error: No se pudo crear la ventana" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    
    if (!initGLAD()) {
        return false;
    }

    // Configurar viewport
    glViewport(0, 0, width, height);

    return true;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::renderLoop() {
    if (!shouldClose())
    {
        Window::isOpen = true;
    }
}

void Window::cleanup()
    {
        // Destruye la ventana y limpia GLFW al cerrar el juego
        if (window)
        {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
        isOpen = false;
    }

}
   