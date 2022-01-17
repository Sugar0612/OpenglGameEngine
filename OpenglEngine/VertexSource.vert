#version 330 core		
layout(location = 0) in vec3 aPos;	
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec4 color;                             
out vec2 TexCoord;	

uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 offsets[10];

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()									
{	
	Normal = mat3(transpose(inverse(offsets[gl_InstanceID]))) * aNormal;
	FragPos = vec3(offsets[gl_InstanceID] * vec4(aPos, 1.f)).xyz;
	TexCoords = aTexCoords;
	gl_Position = projMat * viewMat * offsets[gl_InstanceID] * vec4(aPos.x, aPos.y, aPos.z, 1.0); 
}