#pragma once

#include "RenderDevice.hpp"
#include "ArrayBitmap.hpp"
#include "DDSTexture.hpp"

/*TODO: Remove*/
class Texture
{
public:
	inline Texture(RenderDevice& deviceIn, const ArrayBitmap& texData,
		enum RenderDevice::PixelFormat internalPixelFormat,
		bool generateMipmaps, bool shouldCompress) :
		device(&deviceIn),
		texId(device->createTexture2D(texData.getWidth(),
			texData.getHeight(), texData.getPixelArray(),
			RenderDevice::FORMAT_RGBA,
			internalPixelFormat, generateMipmaps, shouldCompress)),
		width((uint32)texData.getWidth()),
		height((uint32)texData.getHeight()),
		compressed(shouldCompress),
		mipmaps(generateMipmaps) {}

	inline Texture(RenderDevice& deviceIn, const DDSTexture& ddsTexture) :
		device(&deviceIn),
		texId(device->createDDSTexture2D(ddsTexture.getWidth(), ddsTexture.getHeight(),
			ddsTexture.getBuffer(), ddsTexture.getFourCC(),
			ddsTexture.getMipMapCount())),
		width(ddsTexture.getWidth()),
		height(ddsTexture.getHeight()),
		compressed(true),
		mipmaps(ddsTexture.getMipMapCount() > 1) {}

	inline ~Texture()
	{
		texId = device->releaseTexture2D(texId);
	}

	inline uint32 getId();
	inline uint32 getWidth() const;
	inline uint32 getHeight() const;
	inline bool isCompressed() const;
	inline bool hasMipmaps() const;
private:
	RenderDevice* device;
	uint32 texId;
	uint32 width;
	uint32 height;
	bool compressed;
	bool mipmaps;
};

inline uint32 Texture::getId()
{
	return texId;
}

inline uint32 Texture::getWidth() const
{
	return width;
}

inline uint32 Texture::getHeight() const
{
	return height;
}

inline bool Texture::isCompressed() const
{
	return compressed;
}

inline bool Texture::hasMipmaps() const
{
	return mipmaps;
}

namespace SOMA_ENGINE {
	class Texture {
	public:
		virtual ~Texture() = default;
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual void Bind(uint32 slot = 0) const = 0;
	};

	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(const SOMA_String& path);
	};
};