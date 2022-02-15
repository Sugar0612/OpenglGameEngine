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

struct LightSpot {
    float cosPhy;
};

uniform vec3 ambientColor;
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 eyePos;
uniform Material material;
uniform LightPoint lightPtr;
uniform LightSpot lightSpot;
out vec4 FragColor;	

void main()								
{				
    float dist = length(lightPos - FragPos);
    //float attenuation = 1.f / (lightPtr.constant + lightPtr.linear * (dist) + lightPtr.quadratic * (dist * dist));

    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDir, Normal);
    vec3 eyeVec = normalize(eyePos - FragPos);

    /* 高光强度 */
    float specularAmount = pow(max(dot(reflectVec, eyeVec), 0), material.shininess);

    vec3 Specular = texture(material.specular, TexCoords).rgb * specularAmount * lightColor;
    vec3 Diffuse = texture(material.diffuse, TexCoords).rgb * max(dot(lightDir, Normal), 0) * lightColor;
    //vec3 Diffuse = texture(material.diffuse, TexCoords).rgb;
    vec3 Ambient = texture(material.diffuse, TexCoords).rgb * ambientColor;

    float cosTheta = dot(normalize(FragPos - lightPos), -1 * lightDir);
    if(cosTheta > lightSpot.cosPhy) {
         //resultColor = (Diffuse + Specular + Ambient) * objColor;
         FragColor = vec4((Ambient + Diffuse + Specular) * objColor, 1.f);
    } else {
         //resultColor = Ambient * objColor;
         FragColor = vec4((Ambient) * objColor, 1.f);
    }   

    //vec3 resultColor = (attenuation * (Diffuse + Specular) + Ambient) * objColor;
    //FragColor = vec4(resultColor, 1.f);
}