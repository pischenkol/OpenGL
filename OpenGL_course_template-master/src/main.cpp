#include <glwrapper.h>
#include "glfw3.h"
#include <thread>
#include <iostream>
#include "ShadersLoader.h"

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    auto window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);

    if (window == NULL) {
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

    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSource = shaders::loadShaderSourceFromFile("resources/shaders/vertex.glsl");
    const char* vertextShaderSourseNative = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertextShaderSourseNative, nullptr);
    glCompileShader(vertexShader);

    GLint successVertextCompilation;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertextCompilation);

    if (!successVertextCompilation) {
        GLchar info[512];
        glGetShaderInfoLog(vertexShader, sizeof(info), NULL, info);
        std::cerr << "ERROR::SHADER LINK_FAILED\n" << info;
        return 0;
    }

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSource = shaders::loadShaderSourceFromFile("resources/shaders/fragment.glsl");
    const char* fragmentShaderSourseNative = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourseNative, nullptr);
    glCompileShader(fragmentShader);

    GLint successFragmentCompilation;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragmentCompilation);

    if (!successFragmentCompilation) {
        GLchar info[512];
        glGetShaderInfoLog(fragmentShader, sizeof(info), NULL, info);
        std::cerr << "ERROR::SHADER LINK_FAILED\n" << info;
        return 0;
    }

    auto program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);


    GLint successProgramtCompilation;
    glGetProgramiv(program, GL_LINK_STATUS, &successProgramtCompilation);
    if (!successProgramtCompilation) {
        GLchar info[512];
        glGetProgramInfoLog(program, sizeof(info), NULL, info);
        std::cerr << "ERROR::PROGRAM LINK_FAILED\n" << info;

        glDeleteProgram(program);
        glfwTerminate();
        return 0;
    }
    glViewport(0, 0, width, height);

    GLfloat coordinate[]= {
            //платье
            0.0f, 0.5f,
            -0.5f, - 0.5f,
            0.5f, -0.5f,
            // левая рука
            -0.5f, 0.5f,
            -0.5f,  0.20f,
            0.0f, 0.5f,
            -0.5f,  0.20f,
            0.0f,  0.20f,
            0.0f, 0.5f,
            //правая рука
            0.0f, 0.2f,
            0.5f, 0.2f,
            0.5f, 0.5f,
            0.0f, 0.5f,
            0.0f, 0.2f,
            0.5f, 0.5f,
            //левая нога
            -0.1f, -0.0f,
            -0.1f, -1.0f,
            -0.2f, 0.0f,
            -0.2f, 0.0f,
            -0.1f, -1.0f,
            -0.2f, -1.0f,
            //правая нога
            0.1f, 0.0f,
            0.1f, -1.0f,
            0.2f, 0.0f,
            0.1f, -1.0f,
            0.2f, -1.0f,
            0.2f, 0.0f,
            //голова
            0.000000,0.750000,
            0.147721,0.776047,
            0.140954,0.801303,
            0.129904,0.825000,
            0.114907,0.846418,
            0.096418,0.864907,
            0.075000,0.879904,
            0.051303,0.890954,
            0.026047,0.897721,
            -0.000000,0.900000,
            -0.026047,0.897721,
            -0.051303,0.890954,
            -0.075000,0.879904,
            -0.096418,0.864907,
            -0.114907,0.846418,
            -0.129904,0.825000,
            -0.140954,0.801303,
            -0.147721,0.776047,
            -0.150000,0.750000,
            -0.147721,0.723953,
            -0.140954,0.698697,
            -0.129904,0.675000,
            -0.114907,0.653582,
            -0.096418,0.635093,
            -0.075000,0.620096,
            -0.051303,0.609046,
            -0.026047,0.602279,
            0.000000,0.600000,
            0.026047,0.602279,
            0.051303,0.609046,
            0.075000,0.620096,
            0.096418,0.635093,
            0.114907,0.653582,
            0.129904,0.675000,
            0.140954,0.698697,
            0.147721,0.723953,
            0.150000,0.750000,
            0.147721,0.776047,
            0.000000,0.750000
    };

    GLuint indexes[] ={
            0, 1, 2, 3,4,5,6,7,8,9,10,
            11,12,13,14,15,16,17,18,19,20,
            21,22,23,24, 25, 26, 27, 28, 29, 30,
            31, 32, 33, 34 ,35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
            51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
    };
    GLuint vbo;
    GLuint ebo;
    GLuint vao;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinate)*2, coordinate, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glfwMakeContextCurrent( window );



    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.4f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 27);
        glDrawArrays(GL_TRIANGLE_FAN, 27, 63);
        glfwSwapBuffers( window );

        glfwPollEvents( );
        std::this_thread::sleep_for(std::chrono::nanoseconds(15000));
    }
    glfwTerminate();
    return 0;
}




