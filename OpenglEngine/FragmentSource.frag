#version 330 core	

in vec4 color;                          
in vec2 TexCoord;

uniform vec4 vertexColor;   

uniform sampler2D aTexture;
uniform sampler2D aFace;

uniform vec3 ambientColor;
uniform vec3 objColor;

out vec4 FragColor;	
void main()								
{					
    //FragColor = mix(texture(aTexture, TexCoord), texture(aFace, TexCoord), 0.2);				
    FragColor = mix(texture(aTexture, TexCoord), texture(aFace, TexCoord), 0.2) * vec4(objColor * ambientColor, 1.f);
}										