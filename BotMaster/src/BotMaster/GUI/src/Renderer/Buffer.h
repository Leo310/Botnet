#pragma once

namespace GUI
{
	enum class ShaderDataType
	{
		NONE = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3: return 4 * 3 * 3;
		case ShaderDataType::Mat4: return 4 * 4 * 4;
		case ShaderDataType::Int: return 4;
		case ShaderDataType::Int2: return 4 * 2;
		case ShaderDataType::Int3: return 4 * 3;
		case ShaderDataType::Int4: return 4 * 4;
		case ShaderDataType::Bool: return 1;
		}
		assert(false, "Unknown ShaderDataType!");

		return 0;
	}

	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		bool Normalized;
		unsigned int Size;
		unsigned int Offset;

		BufferElement()
			: Type(ShaderDataType::NONE), Name(""), Normalized(false), Size(0), Offset(0) {}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			:	Type(type), Name(name), Normalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0) {}

		unsigned int GetElementCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3; // 3* float3
			case ShaderDataType::Mat4:    return 4; // 4* float4
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			assert(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements) // cant do vector because to use this constructor in a nice way we need to do 2 implicit conversions.This doesnt work so we use an initializer_list
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}	

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; };
		inline unsigned int GetStride() const { return m_Stride; };

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); };	//dont completly understand
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); };
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); };	//dont completly understand
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); };
	private:
		void CalculateOffsetsAndStride()
		{
			m_Stride = 0;
			for (BufferElement& element : m_Elements)
			{
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, int size);
	};


	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;

		static IndexBuffer* Create(unsigned int* indices, int count);
	};
}