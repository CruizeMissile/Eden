#ifndef H_GRAPHICS_BUFFER_H
#define H_GRAPHICS_BUFFER_H

#include "Precompiled.h"

namespace edn
{
	class Buffer
	{
	protected:
		Buffer(u32 type);
		virtual ~Buffer();

	public:
		bool Initialize(u32 elementSize, u32 elementCount, const void * data, u32 usage);

		void Cleanup();

		void Update(const void * data, s32 count = -1);

		bool Valid() const;

		void * Data() { return m_data; }

		virtual bool IsInstanced() { return false; }
		virtual u32 ElementType() const { return GL_INVALID_ENUM; }

		u32 Type() const { return m_type; }
		u32 Handle() const { return m_handle; }
		u32 ElementSize() const { return m_elementSize; }
		u32 ElementCount() const { return m_elementCount; }

	protected:
		u32 m_type;
		u32 m_handle;

		u32 m_elementSize;
		u32 m_elementCount;

		void * m_data;
	};

	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer()
			: Buffer(GL_ARRAY_BUFFER)
		{}
	};

	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer()
			: Buffer(GL_ELEMENT_ARRAY_BUFFER)
		{ }
		virtual u32 getElementType() const;
	};

	class InstanceBuffer : public Buffer
	{
	public: 
		InstanceBuffer()
			: Buffer(GL_ARRAY_BUFFER)
		{}

		virtual bool IsInstance() const { return true; }
	};
}

#endif