#pragma once
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "shader.h"

class Texture
{
public:
	Texture(const char* filename, std::string image_type, GLenum port);
	~Texture();

public:
	unsigned int texBuffer;
	Shader* Texshader;

private:
	const char* _filename;
	std::string _image_type;

private:
	int width, height, Channel;
	unsigned char* data;
	GLenum _port;

public:
	void BindTexture();
	void SetUniform(unsigned int ID, int num, const GLchar* name);

private:
	void CreateTextureAndLoadImage(GLenum port);
};

