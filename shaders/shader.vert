#version 400 core

// Vertex attribute for position
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
out vec2 TexCoords;
out mat3 TBN;

uniform vec3 lightPos; // we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 T = normalize(vec3(model * vec4(in_tangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(in_normal, 0.0)));
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

    TBN = mat3(T, B, N);
    TexCoords = in_uv;
    gl_Position = projection * view * model * vec4(in_position, 1.0);
    FragPos = vec3(view * model * vec4(in_position, 1.0));
    Normal = mat3(transpose(inverse(view * model))) * in_normal;
    LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position
}