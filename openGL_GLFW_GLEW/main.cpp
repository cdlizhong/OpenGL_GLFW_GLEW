//
//  main.cpp
//  openGL_GLFW_GLEW
//
//  Created by cdlizhong on 16/9/28.
//  Copyright © 2016年 cdlizhong. All rights reserved.
//

//#include <iostream>
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}

/*
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow *window;
    // init the library
    if ( !glfwInit())
    {
        return -1;
    }
    // create a windowed mode window and its OpenGl Context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    // make the windows's context current
    glfwMakeContextCurrent(window);
    // loop unitl the user close the windows
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        //render the OpenGL ,put all you OpenGL code here
        // swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}*/




#include <iostream>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include "Shader.hpp"

#define SHADER_VS "/Users/lizhong/Documents/OpenGL_GLFW_GLEW/openGL_GLFW_GLEW/shader.vs"
#define SHADER_FRAG "/Users/lizhong/Documents/OpenGL_GLFW_GLEW/openGL_GLFW_GLEW/shader.frag"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
//    GLFWwindow *window = glfwCreateWindow(640, 480, "lizhong", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();
    
    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    // Build and compile our shader program
    Shader ourShader(SHADER_VS, SHADER_FRAG);
    
    // Set up vertex data (and buffer(s)) and attribute pointers
//    GLfloat vertices[] = {
//      // First triangle
//       0.5f,  0.5f,  // Top Right
//       0.5f, -0.5f,  // Bottom Right
//      -0.5f,  0.5f,  // Top Left
//      // Second triangle
//       0.5f, -0.5f,  // Bottom Right
//      -0.5f, -0.5f,  // Bottom Left
//      -0.5f,  0.5f   // Top Left
//    };
//    GLfloat vertices[] = {
//        0.5f,  0.5f, 0.0f,  // Top Right
//        0.5f, -0.5f, 0.0f,  // Bottom Right
//        -0.5f, -0.5f, 0.0f,  // Bottom Left
//        -0.5f,  0.5f, 0.0f   // Top Left
//    };
//    GLfloat vertices[] = {
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        0.0f,  0.5f, 0.0f
//    };
    GLfloat vertices[] = {
        // 位置          // 颜色
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // 上
    };
//    GLuint indices[] = {  // Note that we start from 0!
//        0, 1, 3,  // First Triangle
//        1, 2, 3   // Second Triangle
//    };
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
    
    
    // Uncommenting this call will result in wireframe polygons.
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        
        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw our first triangle
        ourShader.Use();
//        // 更新uniform颜色
        GLfloat timeValue = glfwGetTime();
        GLfloat offx = (sin(timeValue) / 2) + 0.5;
        GLint offxLocation = glGetUniformLocation(ourShader.Program, "offx");
        glUniform1f(offxLocation,offx);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    printf("key_callback:%d",key);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
