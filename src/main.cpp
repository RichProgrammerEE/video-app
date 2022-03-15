#include <GLFW/glfw3.h>

#include <iostream>

int main(int argc, const char** argv)
{
    GLFWwindow* window;

    if(!glfwInit()) {
        std::cout << "Couldn't init GLFW" << std::endl;
        return 1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window) {
        std::cout << "Couldn't open window" << std::endl;
        return 1;
    }

    unsigned char* data = new unsigned char[100*100*3];
    for(size_t y = 0; y < 100; ++y) {
        for(size_t x = 0; x < 100; ++x) {
            data[y * 100 * 3 + x * 3    ] = 0xff; // R
            data[y * 100 * 3 + x * 3 + 1] = 0x00; // G
            data[y * 100 * 3 + x * 3 + 2] = 0x00; // B
        }
    }
    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    return 0;
}