#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 texCoord;


out vec2 v_TexCoord;


uniform mat4 ProjectionView;
uniform mat4 Model;

void main() {
    gl_Position = ProjectionView * Model * vec4(a_Position,1.0);
    v_TexCoord = texCoord;
}
