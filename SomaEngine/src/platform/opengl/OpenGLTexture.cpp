#include "somapch.hpp"
#include "platform/opengl/OpenGLTexture.hpp"
#include "stb_image.h"


#include <glad/glad.h>

namespace SOMA_ENGINE {
	OpenGLTexture2D::OpenGLTexture2D(const SOMA_String& path)
	{
		m_path = path;
		int width, height, channels;
		//stbi_set_flip_vertically_on_load(1);

		stbi_uc* data =  stbi_load(path.c_str(),&width,&height,&channels,0);
		SOMA_ASSERT(data, "Failed to load image!");

		m_width = width;
		m_height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}


		m_internalFormat = internalFormat;
		m_dataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
		glTextureStorage2D(m_id, 1, internalFormat, m_width, m_height);

		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_id);
	}
	void OpenGLTexture2D::Bind(uint32 slot) const
	{
		glBindTextureUnit(slot, m_id);
	}
}