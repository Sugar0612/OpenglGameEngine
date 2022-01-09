#version 330 core		
layout(location = 0) in vec3 aPos;	
layout(location = 1) in vec3 aColor;        
layout(location = 2) in vec2 aTexCoord;

out vec4 color;                             
out vec2 TexCoord;	

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 offsets[10];

void main()									
{										
	TexCoord = aTexCoord;

	gl_Position = projMat * viewMat * offsets[gl_InstanceID] * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = vec4(aColor.x, aColor.y, aColor.z, 1.f);  
}