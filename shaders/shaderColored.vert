#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 cameraView;
uniform mat4 model;


void main() {
    gl_Position = cameraView * model * vec4(a_Position, 1.0);
}
