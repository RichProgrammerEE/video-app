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

    for(size_t y = 25; y < 75; ++y) {
        for(size_t x = 25; x < 75; ++x) {
            data[y * 100 * 3 + x * 3    ] = 0x00; // R
            data[y * 100 * 3 + x * 3 + 1] = 0x00; // G
            data[y * 100 * 3 + x * 3 + 2] = 0xff; // B
        }
    }

    glfwMakeContextCurrent(window);

    GLuint texHandle;
    int texWidth = 100;
    int texHeight = 100;
    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle); // Make this the texture we are working on.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Load data into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up orthographic projection
        int windowWidth, windowHeight;
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        // Render our texture
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texHandle);
        glBegin(GL_QUADS);
            glTexCoord2d(0,0); glVertex2i(0,0);
            glTexCoord2d(1,0); glVertex2i(texWidth,0);
            glTexCoord2d(1,1); glVertex2i(texWidth,texHeight);
            glTexCoord2d(0,1); glVertex2i(0,texHeight);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        // Raw drawing of pixels
        // glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    return 0;
}