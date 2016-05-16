#ifndef H_GRAPHICS_BUFFER_H
#define H_GRAPHICS_BUFFER_H

#include "Precompiled.h"

namespace edn
{
	struct BindingDesciptor;

	//
	// Buffer
	//
	class Buffer
	{
	public:
		Buffer() { };
		~Buffer() { Cleanup(); };
		bool Initialize(u32 type, u32 elementSize, u32 elementCount, void * data, u32 usage);
		void Cleanup();

		void * MapData();
		void UnMapData();

		
		u32 m_type; // GL_VERTEX_BUFFER, GL_UNIFORM_BUFFER etc...
		u32 m_size;
		u32 m_count;
		u32 m_handle;
		u32 m_usage;
		void * m_data;
	};

	//
	// Binding Descriptors
	//
	struct BindingDesciptor
	{
		u32 m_startOffset;
		u32 m_stride;
		u32 m_instanceDivisor;
		u32 m_elementSize;
		u32 m_location;
	};

	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer() { m_type = GL_ARRAY_BUFFER; }

		void AddBindingDescriptor(BindingDesciptor bd)
		{
			m_binding.push_back(bd);
		}

	private:
		std::vector<BindingDesciptor> m_binding;
	};

	class UnformBuffer : public Buffer
	{
	public:
		UnformBuffer() { m_type = GL_UNIFORM_BUFFER; }

	};

	//
	// Buffer Implementation
	//
	bool Buffer::Initialize(u32 type, u32 size, u32 count, void * data, u32 usage)
	{
		ASSERT(size != 0, "Invalid argument size is 0");
		ASSERT(count != 0, "Invalid argument count is 0");

		m_size = size;
		m_count = count;
		m_usage = usage;

		glGenBuffers(1, &m_handle);

		assert(m_handle != 0);

		u32 buffre_size = m_size * m_count;

		glBindBuffer(m_type, m_handle);
		glBufferData(m_type, buffre_size, data, usage);
		glBindBuffer(m_type, 0);
		return true;
	}

	void * Buffer::MapData()
	{
		if (m_usage == GL_DYNAMIC_DRAW)
			return m_data;

		return glMapBuffer(m_handle, GL_WRITE_ONLY);
	}

	void Buffer::UnMapData()
	{
		if (m_usage == GL_STATIC_DRAW)
			glUnmapBuffer(m_handle);
	}

	void Buffer::Cleanup()
	{
		if (m_handle != 0)
		{
			glDeleteBuffers(1, &m_handle);
			m_handle = 0;
		}
		m_size = 0;
		m_count = 0;
	}
}

#endif