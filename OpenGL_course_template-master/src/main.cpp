
#include <glwrapper.h>
#include "glfw3.h"
#include <thread>
#include <iostream>
#include "ShadersLoader.h"
#include <stb_image.h>

    int main() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        auto window = glfwCreateWindow(1280, 720, "OpenGL", nullptr, nullptr);

        if (window == nullptr) {
            std::cerr << "Can not create glfw window! \n";
            glfwTerminate();
            return -1;
        }

        int width;
        int height;
        glfwGetFramebufferSize(window, &width, &height);
        glfwMakeContextCurrent(window);

#ifndef __APPLE__
        glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing glew. Exiting.\n";
        return -1;
    }
#endif

        auto sourceFromFileVertex = shaders::loadShaderSourceFromFile("resources/shaders/vertex.glsl");
        auto vertexShaderCode = sourceFromFileVertex.c_str();
        auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
        glCompileShader(vertexShader);

        GLint vertexShaderStatus;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderStatus);
        if (!vertexShaderStatus) {
            char info[512];
            glGetShaderInfoLog(vertexShader, sizeof(info), nullptr, info);

            std::cerr << info << std::endl;
        }

        stbi_set_flip_vertically_on_load(GL_TRUE);

        auto sourceFromFileFragment = shaders::loadShaderSourceFromFile("resources/shaders/fragment.glsl");
        auto fragmentShaderCode = sourceFromFileFragment.c_str();
        auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
        glCompileShader(fragmentShader);

        GLint fragmentShaderStatus;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderStatus);
        if (!fragmentShaderStatus) {
            char info[512];
            glGetShaderInfoLog(fragmentShader, sizeof(info), nullptr, info);

            std::cerr << info << std::endl;
        }


        auto program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        if (!status) {
            char info[512];
            glGetProgramInfoLog(program, sizeof(info), nullptr, info);

            std::cerr << info << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        GLfloat coordinates[] = {
                //backgroung
                -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                //left hand
                -0.5f, 0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                -0.5f, 0.20f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.5f, 0.20f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.20f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                0.0f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                //right hand
                0.0f, 0.2f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                0.5f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                0.5f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.0f, 0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 0.2f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                0.5f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                //left leg
                -0.1f, -0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.1f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                -0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                -0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                -0.1f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                -0.2f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                //right leg
                0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                0.1f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.1f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                0.2f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                //dress
                0.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f,
                -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                //head
                0.00000f, 0.75000f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f,
                0.14772f, 0.77604f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.14095f, 0.80130f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.12990f, 0.82500f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.11490f, 0.84641f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.09641f, 0.86490f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.07500f, 0.87990f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.05130f, 0.89095f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.02604f, 0.89772f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.00000f, 0.90000f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.02604f, 0.89772f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.05130f, 0.89095f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.07500f, 0.87990f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.09641f, 0.86490f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.11490f, 0.84641f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.12990f, 0.82500f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.14095f, 0.80130f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.14772f, 0.77604f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.15000f, 0.75000f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.14772f, 0.72395f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.14095f, 0.69869f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.12990f, 0.67500f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.11490f, 0.65358f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.09641f, 0.63509f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.07500f, 0.62009f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.05130f, 0.60904f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.02604f, 0.60227f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.00000f, 0.60000f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.02604f, 0.60227f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.05130f, 0.60904f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.07500f, 0.62009f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.09641f, 0.63509f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.11490f, 0.65358f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.12990f, 0.67500f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.14095f, 0.69869f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.14772f, 0.72395f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.15000f, 0.75000f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.14772f, 0.77604f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.00000f, 0.75000f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
        };

        GLuint indexes[] ={
                0, 1,2,3,4,5,6,7,8,9,10,
                11,12,13,14,15,16,17,18,19,20,
                21,22,23,24, 25, 26, 27, 28, 29, 30,
                31, 32, 33, 34 ,35, 36, 37, 38, 39, 40,
                41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
                51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62
        };


        GLuint vbo;
        GLuint ebo;
        GLuint vao;

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, reinterpret_cast<void *>(sizeof(GLfloat) * 0));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, reinterpret_cast<void *>(sizeof(GLfloat) * 2));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, reinterpret_cast<void *>(sizeof(GLfloat) * 5));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        GLint textureWidth;
        GLint textureHeight;
        GLint textureChannelsCount;
        auto data = stbi_load("resources/kletka3.jpg", &textureWidth, &textureHeight, &textureChannelsCount, STBI_rgb);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        GLuint texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        textureWidth;
        textureHeight;
        textureChannelsCount;
        data = stbi_load("resources/dress.jpg", &textureWidth, &textureHeight, &textureChannelsCount, STBI_rgb);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        GLuint texture3;
        glGenTextures(1, &texture3);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        textureWidth;
        textureHeight;
        textureChannelsCount;
        data = stbi_load("resources/background.jpg", &textureWidth, &textureHeight, &textureChannelsCount, STBI_rgb);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        GLuint texture4;
        glGenTextures(1, &texture4);
        glBindTexture(GL_TEXTURE_2D, texture4);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        textureWidth;
        textureHeight;
        textureChannelsCount;
        data = stbi_load("resources/face.jpg", &textureWidth, &textureHeight, &textureChannelsCount, STBI_rgb);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(program);
//fon
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture3);
            glUniform1i(glGetUniformLocation(program, "sampler"), 0);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i(glGetUniformLocation(program, "sampler"), 0);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 6, 30);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glUniform1i(glGetUniformLocation(program, "sampler"), 0);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 30, 33);
            glDrawArrays(GL_TRIANGLE_FAN, 33, 63);


            glEnableVertexAttribArray(1);
            glfwSwapBuffers( window );

            glfwPollEvents( );
            std::this_thread::sleep_for(std::chrono::nanoseconds(15000));

        }

        glfwTerminate();
        return 0;
    }
