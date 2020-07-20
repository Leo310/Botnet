#pragma once

#include "src/Base.h"

class Texture
{
public:
	Texture()
		: m_Id(0), m_Width(0), m_Height(0), m_NrChannels(0), data(0) {}
	Texture(const char* path, unsigned int format);
	~Texture();

	void loadTexture(const char* path, unsigned int format);

	void bind();
	void unbind();

	inline unsigned int getId() const { return m_Id; };
private:
	unsigned int m_Id;
	int m_Width, m_Height, m_NrChannels;	//nrChannels = number of color Channels
	unsigned char* data;

};