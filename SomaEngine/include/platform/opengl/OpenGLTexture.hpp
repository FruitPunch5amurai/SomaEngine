#pragma once
#include "rendering/Texture.hpp"
namespace SOMA_ENGINE {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const SOMA_String& path);
		virtual ~OpenGLTexture2D();

		virtual uint32 GetWidth() const override { return m_width; }
		virtual uint32 GetHeight() const override { return m_width; };

		virtual void Bind(uint32 slot = 0) const override;
	private:
		uint32 m_width;
		uint32 m_height;
		uint32 m_id;
		SOMA_String m_path;
		GLenum m_internalFormat;
		GLenum m_dataFormat;
	};
}