#version 400 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 LightPos;   // extra in variable, since we need the light position in view space we calculate this in the vertex shader
in vec2 TexCoords;
in mat3 TBN;

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   sampler2D normal;
   float shininess;
};

struct Light {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
   vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));

   // diffuse

   vec3 normal = texture(material.normal, TexCoords).rgb;
   normal = normal * 2.0 - 1.0;
   normal = normalize(TBN * normal);

   vec3 lightDir = normalize(LightPos - FragPos);
   float diff = max(dot(normal, lightDir), 0.0);
   vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));

   // specular
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

   vec3 result = ambient + diffuse;
   FragColor = vec4(ambient + diffuse + specular, 1.0);
}