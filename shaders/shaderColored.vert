#version 330 core

layout(location = 0) in vec3 a_Position;
out vec3 v_Color;

uniform mat4 CameraMatrix;
uniform mat4 Model;


void main() {
    v_Color = a_Position;
    gl_Position = CameraMatrix * Model * vec4(a_Position, 1.0);
}
