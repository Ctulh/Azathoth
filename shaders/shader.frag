#version 330 core

layout(location = 0) out vec4 color;

in vec3 LightIntensivity;

void main() {
   color = vec4(LightIntensivity, 1.0);
}
