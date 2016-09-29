/* 
  shader.vs
  openGL_GLFW_GLEW

  Created by lizhong on 16/9/29.
  Copyright © 2016年 cdlizhong. All rights reserved.
*/
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;
uniform float offx;

void main()
{
//    gl_Position = vec4(position, 1.0f);
//    gl_Position = vec4(position.x,-position.y,position.z,1.0f);
    gl_Position = vec4(position.x+offx,position.y,position.z,1.0f);
    ourColor = color;
//    ourColor = vec3(offx,offx,offx);
}