#version 330 core	

in vec3 Normal;
in vec3 FragPos;

uniform vec3 ambientColor;
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 eyePos;

out vec4 FragColor;	
void main()								
{					
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDir, Normal);
    vec3 eyeVec = normalize(eyePos - FragPos);

    /* 高光强度 */
    float specularAmount = pow(max(dot(eyeVec, reflectVec), 0.f), 128.0);
    vec3 Specular = specularAmount * lightColor;

    vec3 Diffuse = max(dot(lightDir, Normal), 0.f) * lightColor;
    vec3 resultColor = (Diffuse + Specular + ambientColor) * objColor;
    FragColor = vec4(resultColor, 1.f);
}