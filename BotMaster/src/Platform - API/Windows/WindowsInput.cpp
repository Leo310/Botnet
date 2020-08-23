#include "BMpch.h"
#include "WindowsInput.h"

#include "src/GUI.h"

namespace GUI
{
    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(KeyCode keyCode)
    {
        auto window = static_cast<GLFWwindow*>(GUI::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int>(keyCode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    bool WindowsInput::IsMouseButtonPressedImpl(MouseCode mouseCode)
    {
        auto window = static_cast<GLFWwindow*>(GUI::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int>(mouseCode));
        return state == GLFW_PRESS;
    }
    std::pair<float, float> WindowsInput::GetMousePosImpl()
    {
        auto window = static_cast<GLFWwindow*>(GUI::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return std::pair<float, float>(xpos, ypos);
    }
    bool WindowsInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePosImpl();
        return x;
    }
    bool WindowsInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePosImpl();
        return y;
    }
}
