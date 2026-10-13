#version 460 core

in vec3 aPos; // (location = 0), declared in main.cpp
in vec3 aColor; // (location = 1), declared in main.cpp

out vec3 col;

void main()
{
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  col = aColor;
}