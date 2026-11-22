/* Application.cpp */

#include "Application.h"

#include <iostream>
#include <stdexcept>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "components/shared/fonts/Font.h"
#include "components/shared/image/Image.h"
#include "components/shared/constants/Constants.h"
#include "screens/OnBoardingScreen/OnBoardingScreen.h"

Application::Application() = default;

Application::~Application()
{
    Shutdown();
}

bool Application::Initialize()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    // Configure OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    m_Window = glfwCreateWindow(
        Constants::BaseWindowWidth,
        Constants::BaseWindowHeight,
        "Sifu",
        nullptr,
        nullptr
    );


    if (!m_Window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwSetWindowSizeLimits(
        m_Window,
        900, 600,
        GLFW_DONT_CARE,
        GLFW_DONT_CARE
    );

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    // Initialize GLAD 2
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
        glfwTerminate();
        return false;
    }

    // Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    //ImGui::StyleColorsLight();

    if (!ImGui_ImplGlfw_InitForOpenGL(m_Window, true))
    {
        std::cerr << "Failed to initialize ImGui GLFW backend\n";
        ImGui::DestroyContext();
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
        glfwTerminate();
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 330"))
    {
        std::cerr << "Failed to initialize ImGui OpenGL backend\n";
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
        glfwTerminate();
        return false;
    }

    Font::Initialize();

    m_Running = true;

    return true;
}

void Application::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Application::RenderUI()
{
    OnBoardingScreen(this->m_Window);
}

void Application::EndFrame()
{
    ImGui::Render();

    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);

    glViewport(0, 0, width, height);

    glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_Window);
}

void Application::Run()
{
    while (m_Running && !glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();

        BeginFrame();
        RenderUI();
        EndFrame();
    }
}

void Application::Shutdown()
{
    Image::ClearCache();
    if (ImGui::GetCurrentContext())
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    if (m_Window)
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }

    glfwTerminate();

    m_Running = false;
}
