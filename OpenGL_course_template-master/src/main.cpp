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

    auto window = glfwCreateWindow(720, 720, "OpenGL", NULL, NULL);

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
            //платье
            0.0f, 0.5f,
            -0.5f, - 0.5f,
            0.5f, -0.5f,
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

    static const GLfloat g_color_buffer_data[] = {

            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            0.822f,  0.569f,  0.201f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
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

//    glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    glfwMakeContextCurrent( window );
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.4f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 27);
        glDrawArrays(GL_TRIANGLE_FAN, 27, 63);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );
        glfwSwapBuffers( window );

        glfwPollEvents( );
        std::this_thread::sleep_for(std::chrono::nanoseconds(15000));
    }
    glfwTerminate();
    return 0;
}




