#include "Precompiled.h"
#include "Buffer.h"

using namespace edn;
using namespace std;

namespace
{
	#define LogInitializeError() "Failed to initialize a buffer! "
}

Buffer::Buffer(u32 type)
	:m_type(type)
	, m_handle(GL_NONE)
	, m_elementSize(0)
	, m_elementCount(0)
{}

Buffer::~Buffer()
{
	Cleanup();
}

bool Buffer::Initialize(u32 elementSize, u32 elementCount, const void * data, u32 usage = GL_STATIC_DRAW)
{
	Cleanup();

	// Valid argument
	if (elementSize == 0)
	{
		Log() << LogInitializeError() << "Invalid argument - \"elementSize\" is 0." << endl;
		return false;
	}

	// Valid arguments
	if (elementCount == 0)
	{
		Log() << LogInitializeError() << "Invalid argument - \"elementCount\" is 0." << endl;
		return false;
	}

	m_elementSize = elementSize;
	m_elementCount = elementCount;

	glGenBuffers(1, &m_handle);

	if (m_handle == GL_NONE)
	{
		Log() << LogInitializeError() << "Couldn't create a buffer" << endl;
		Cleanup();
		return false;
	}

	// Copy data to the buffer.
	u32 bufferSize = m_elementSize * m_elementCount;

	glBindBuffer(m_type, m_handle);
	glBufferData(m_type, bufferSize, data, usage);
	glBindBuffer(m_type, 0);

	Log() << "Created a buffer. (Size: " << bufferSize << " bytes)" << endl;
	return true;
}

void Buffer::Cleanup()
{
	if (m_handle != GL_NONE)
	{
		glDeleteBuffers(1, &m_handle);
		m_handle = GL_NONE;
	}
	m_elementSize = 0;
	m_elementCount = 0;
}

void Buffer::Update(const void * data, s32 count)
{
	if (m_handle == GL_NONE)
		return;

	if (data == nullptr)
		return;

	if (count == 0)
		return;

	// check if to update the whole buffer
	if (count < 0)
		count = m_elementCount;

	glBindBuffer(m_type, m_handle);
	glBufferSubData(m_type, 0, m_elementSize * count, data);
	glBindBuffer(m_type, 0);
}

bool Buffer::Valid() const
{
	return m_handle != GL_NONE;
}

u32 IndexBuffer::getElementType() const
{
	if (m_type == GL_ELEMENT_ARRAY_BUFFER)
	{
		switch (m_elementSize)
		{
		case 1: return GL_UNSIGNED_BYTE;
		case 2: return GL_UNSIGNED_SHORT;
		case 4: return GL_UNSIGNED_INT;
		}
	}
	return GL_INVALID_ENUM;
}



