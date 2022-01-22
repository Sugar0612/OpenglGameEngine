#version 330 core	

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
  vec3 ambient;
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct LightPoint {
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 ambientColor;
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 eyePos;
uniform Material material;
uniform LightPoint lightPtr;
out vec4 FragColor;	
void main()								
{				
    float dist = length(lightPos - FragPos);
    float attenuation = 1.f / (lightPtr.constant + lightPtr.linear * (dist) + lightPtr.quadratic * (dist * dist));

    vec3 lightDir = normalize(lightPos - FragPos);

    vec3 reflectVec = reflect(-lightDir, Normal);
    vec3 eyeVec = normalize(eyePos - FragPos);

    /* 高光强度 */
    float specularAmount = pow(max(dot(eyeVec, reflectVec), 0.f), material.shininess);

    vec3 Specular = specularAmount * lightColor * texture(material.specular, TexCoords).rgb;
    vec3 Diffuse = texture(material.diffuse, TexCoords).rgb * max(dot(lightDir, Normal), 0.f) * lightColor;
    //vec3 Diffuse = texture(material.diffuse, TexCoords).rgb;
    vec3 Ambient = texture(material.diffuse, TexCoords).rgb * ambientColor * material.ambient;

    vec3 resultColor = (attenuation * (Diffuse + Specular) + Ambient) * objColor;
    FragColor = vec4(resultColor, 1.f);
}