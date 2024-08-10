#include "utils.hpp"
#include <thread>
#include <chrono>
#undef APIENTRY

constexpr int FPS_LIMIT = 144;

void wait() {
    std::this_thread::sleep_for(std::chrono::microseconds(1000000 + FPS_LIMIT) / FPS_LIMIT);
}

int WinMain() {
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "icosahedron", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwSetWindowPos(window, 0, 30);

    glfwMakeContextCurrent(window);
    gladLoadGL(); // it took 5 hours to find out that it need to be added here.
    
    utils::initializeScene();

    while (!glfwWindowShouldClose(window)) {
        std::thread limiter(wait);
        utils::frameHandler(window, glfwGetTime());
        limiter.join();
    }

    utils::destroyScene(window);
    return 0;
}