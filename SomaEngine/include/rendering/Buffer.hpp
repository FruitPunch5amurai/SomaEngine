#pragma once
#include "core/common.hpp"

namespace SOMA_ENGINE {
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	struct DataTypeSize {
		uint32 elementCount;
		uint32 size;
		DataTypeSize(uint32 s, uint32 ec) :elementCount(ec),size(s){}
	};

	static DataTypeSize ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:	return DataTypeSize(4,1); break;
			case ShaderDataType::Float2:	return DataTypeSize(4 * 2,2); break;
			case ShaderDataType::Float3:	return DataTypeSize(4 * 3,3); break;
			case ShaderDataType::Float4:	return DataTypeSize(4 * 4,4); break;
			case ShaderDataType::Mat3:	return DataTypeSize(4 * 3 * 3,3); break;
			case ShaderDataType::Mat4:	return DataTypeSize(4 * 4 * 4,4); break;
			case ShaderDataType::Int:	return DataTypeSize(4,1); break;
			case ShaderDataType::Int2:	return DataTypeSize(4 * 2,2); break;
			case ShaderDataType::Int3:	return DataTypeSize(4 * 3,3); break;
			case ShaderDataType::Int4:	return DataTypeSize(4 * 4,4); break;
			case ShaderDataType::Bool:	return DataTypeSize(1,1); break;

		}
		SOMA_ASSERT(false, "Unknown ShaderDataType!");
		return DataTypeSize(0,0);
	}

	class BufferElement {
	public:
		SOMA_String name;
		ShaderDataType type;
		uint32 offset;
		uint32 size;
		uint32 elementCount;
		bool normalized;
		BufferElement() {}
		BufferElement(ShaderDataType type, const SOMA_String& name)
		{
			this->name = name;
			this->type = type;
			DataTypeSize dts = ShaderDataTypeSize(type);
			this->size = dts.size;
			this->elementCount = dts.elementCount;
			this->offset = 0;
			this->normalized = false;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_elements(elements)
		{
			CalculateOffsetAndStride();
		}
		inline const SOMA_Array<BufferElement>& GetElements() const { return m_elements; }

		uint32 GetStride() const { return m_stride; }
		SOMA_Array<BufferElement>::iterator begin() { return m_elements.begin(); }
		SOMA_Array<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	private:
		void CalculateOffsetAndStride() {
			uint32 offset = 0;
			m_stride = 0;
			for (auto element : m_elements)
			{
				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
			}
		}
		SOMA_Array<BufferElement> m_elements;
		uint32 m_stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout()const = 0;
		static VertexBuffer* Create(float* vertices, uint32 size);

	};
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind()const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static IndexBuffer* Create(uint32* vertices, uint32 count);
	};
	class UniformBuffer {
	public:
		virtual ~UniformBuffer() {};
		virtual void Bind()const = 0;
		virtual void Unbind() const = 0;
		virtual void Update(const void* data, uintptr dataSize) const = 0;


		static UniformBuffer* Create(const void* data, uintptr dataSize);
	};
}