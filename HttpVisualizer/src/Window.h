#pragma once
#include <string>
#include <utility>

#include "GLFW/glfw3.h"
#include "ImGui/imgui.h"

#define IMGUI_WINDOW_FLAGS ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar

class Window
{
private:
	GLFWwindow* m_Window = nullptr;
	bool m_Resized = true;
public:
	// 1280 720 / 700 650
	Window(int width = 930, int height = 650, const char* title = "HttpVisualizer", GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);
	~Window();

	inline void vsync(bool state) const { glfwSwapInterval(state); }
	inline bool hasResized()	  const { return m_Resized; }
	inline void resized(bool state) { m_Resized = state; }

	// loop
	inline bool isOpen()     const { return !glfwWindowShouldClose(m_Window); }
	inline void swap()       const { glfwSwapBuffers(m_Window); }
	inline void clear()      const { glClear(GL_COLOR_BUFFER_BIT); }
	inline void pollEvents() const { glfwPollEvents(); }
	inline void waitEvents() const { glfwWaitEvents(); }

	ImVec2 GetSize() const;

	// ImGui
	void imGuiInit(const char* iniFileName = NULL) const;
	void imGuiStartFrame() const;
	void imGuiRender() const;
};

Window* GetWindowPtr();
bool StartWindow(const std::string& filePath);