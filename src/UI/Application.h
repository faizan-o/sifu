
#pragma once

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <string>

using std::string;

class Application
{
public:
    Application();
    ~Application();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    void BeginFrame();
    void RenderUI();
    void EndFrame();

private:
    GLFWwindow* m_Window = nullptr;
    bool m_Running = false;
    string name;
};
