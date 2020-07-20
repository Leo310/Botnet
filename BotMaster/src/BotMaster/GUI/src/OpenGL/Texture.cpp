#include "Texture.h"

Texture::Texture(const char* path, unsigned int format)
	: m_Id(0), m_Width(0), m_Height(0), m_NrChannels(0), data(0)
{
	if(path != "")
	loadTexture(path, format);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_Id));
}

void Texture::loadTexture(const char* path, unsigned int format)
{
	GLCall(glGenTextures(1, &m_Id));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &m_Width, &m_Height, &m_NrChannels, 0);
	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else {
		std::cout << "couldnt load texture at " << path << std::endl;
	}

	stbi_image_free(data);
}

void Texture::bind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Id));
}

void Texture::unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
