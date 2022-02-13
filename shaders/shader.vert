#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 LightIntensivity;

uniform mat4 CameraMatrix;
uniform mat4 Model;

uniform vec4 LightPosition;
uniform vec3 Kd;
uniform vec3 Ld;

void main() {
    vec4 eyeCoords = CameraMatrix * vec4(a_Position, 1.0);
    vec3 s = normalize(vec3(LightPosition - eyeCoords));

    LightIntensivity = Ld * Kd * max(dot(s, a_Position), 0.0);
    gl_Position = CameraMatrix * Model * vec4(a_Position, 1.0);
}
