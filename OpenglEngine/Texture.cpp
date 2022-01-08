#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include <iostream>

Texture::Texture(const char* filename, std::string image_type, GLenum port): _filename(filename), _image_type(image_type), _port(port)
{
	CreateTextureAndLoadImage(port);
}

void Texture::CreateTextureAndLoadImage(GLenum port)
{
	glActiveTexture(port);
	glGenTextures(1, &texBuffer);
	glBindTexture(GL_TEXTURE_2D, texBuffer);
	data = stbi_load(_filename, &width, &height, &Channel, 0);

	/* ·­×ªÍ¼Æ¬ */
	stbi_set_flip_vertically_on_load(true);

	if (data)
	{
		if (_image_type == "JPG")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		/* Open Mipmap */
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "faild of image!" << std::endl;
	}
}

void Texture::BindTexture() 
{
	glActiveTexture(_port);
	glBindTexture(GL_TEXTURE_2D, texBuffer);
}

void Texture::SetUniform(unsigned int ID, int num, const GLchar* name) 
{
	glUniform1i(glGetUniformLocation(ID, name), num);
}

Texture::~Texture()
{

}