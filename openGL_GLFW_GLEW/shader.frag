/* 
  shader.frag
  openGL_GLFW_GLEW

  Created by lizhong on 16/9/29.
  Copyright © 2016年 cdlizhong. All rights reserved.
*/
#version 330 core
in vec3 ourColor;

out vec4 color;

void main()
{
    color = vec4(ourColor, 1.0f);
}