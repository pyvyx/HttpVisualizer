#include <iostream>

#include "GLFW/glfw3.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "Window.h"
#include "Arial.h"


//public
Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    glfwSetErrorCallback([](int error, const char* description) { fprintf(stderr, "Glfw Error %d: %s\n", error, description); });

    if (!glfwInit())
    {
        std::cout << "[ERROR] Glfw Init failed\n";
        return;
    }

    // Create window with graphics context
    m_Window = glfwCreateWindow(width, height, title, monitor, share);
    if (m_Window == NULL)
    {
        std::cout << "[ERROR] glfwCreateWindow failed\n";
        return;
    }

    // center the window
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(m_Window, (mode->width - width) / 2, (mode->height - height) / 2);

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1); // Enable vsync
    glClearColor(0.27f, 0.27f, 0.27f, 1.0f);
    glfwSetWindowSizeLimits(m_Window, 400, 300, GLFW_DONT_CARE, GLFW_DONT_CARE);
}


Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}


ImVec2 Window::GetSize() const
{
    int width, height;
    glfwGetWindowSize(m_Window, &width, &height);
    return { static_cast<float>(width), static_cast<float>(height) };
}


void Window::imGuiInit(const char* iniFileName) const
{
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiPopupFlags;
    io.Fonts->AddFontFromMemoryCompressedTTF(sg_ArialCompressedData, sg_ArialCompressedSize, 19);
    io.IniFilename = iniFileName;

    ImGuiStyle& style = ImGui::GetStyle();
    //style.FrameRounding = 5.f; --
    //style.WindowRounding = 5.f;

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();
}


void Window::imGuiStartFrame() const
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}


void Window::imGuiRender() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}