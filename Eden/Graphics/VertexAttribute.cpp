#include "Precompiled.h"
#include "VertexAttribute.h"
#include "Buffer.h"

using namespace std;

// Log error messages.
#define LogInitializeError() "Failed to initialize a vertex input! "

namespace edn
{
	int GetVertexAttributeTypeSize(VertexAttributeTypes d)
	{
		switch (d)
		{
		case VertexAttributeTypes::Float1:
		case VertexAttributeTypes::UInt1:
			return 1;

		case VertexAttributeTypes::Float2:
		case VertexAttributeTypes::UInt2:
			return 2;

		case VertexAttributeTypes::Float3:
		case VertexAttributeTypes::UInt3:
			return 3;

		case VertexAttributeTypes::Float4:
		case VertexAttributeTypes::Float4x4:
		case VertexAttributeTypes::UInt4:
		case VertexAttributeTypes::UInt4x4:
			return 4;
		}
		return 0;
	}

	int GetVertexAttributeTypeRows(VertexAttributeTypes d)
	{
		switch (d)
		{
		case VertexAttributeTypes::Float1:
		case VertexAttributeTypes::Float2:
		case VertexAttributeTypes::Float3:
		case VertexAttributeTypes::Float4:
		case VertexAttributeTypes::UInt1:
		case VertexAttributeTypes::UInt2:
		case VertexAttributeTypes::UInt3:
		case VertexAttributeTypes::UInt4:
			return 1;

		case VertexAttributeTypes::Float4x4:
		case VertexAttributeTypes::UInt4x4:
			return 4;
		}
		return 0;
	}

	GLenum GetVertexAttributeTypeEnum(VertexAttributeTypes d)
	{
		switch (d)
		{
		case VertexAttributeTypes::Float1:
		case VertexAttributeTypes::Float2:
		case VertexAttributeTypes::Float3:
		case VertexAttributeTypes::Float4:
		case VertexAttributeTypes::Float4x4:
			return GL_FLOAT;

		case VertexAttributeTypes::UInt1:
		case VertexAttributeTypes::UInt2:
		case VertexAttributeTypes::UInt3:
		case VertexAttributeTypes::UInt4:
		case VertexAttributeTypes::UInt4x4:
			return GL_UNSIGNED_INT;
		}
		return GL_INVALID_ENUM;
	}

	int GetVertexAttributeTypeOffset(VertexAttributeTypes d)
	{
		switch (d)
		{
		case VertexAttributeTypes::Float1:
			return sizeof(float);
		
		case VertexAttributeTypes::Float2:
			return sizeof(float) * 2;
		
		case VertexAttributeTypes::Float3:
			return sizeof(float) * 3;
		
		case VertexAttributeTypes::Float4:
		case VertexAttributeTypes::Float4x4:
			return sizeof(float) * 4;

		case VertexAttributeTypes::UInt1:
			return sizeof(u32);
		case VertexAttributeTypes::UInt2:
			return sizeof(u32) * 2;
		case VertexAttributeTypes::UInt3:
			return sizeof(u32) * 3;
		case VertexAttributeTypes::UInt4:
		case VertexAttributeTypes::UInt4x4:
			return sizeof(u32) * 4;
		}
	}

	VertexAttribute::VertexAttribute()
		: m_handle(GL_NONE)
	{
	}

	VertexAttribute::~VertexAttribute()
	{
		Cleanup();
	}

	bool VertexAttribute::Initialize(VAttribute * attributes, u32 count)
	{
		Cleanup();

		// Validate arguments.
		if (attributes == nullptr)
		{
			Log() << LogInitializeError() << "Invalid argument - \"attributes\" is null.";
			return false;
		}

		if (count <= 0)
		{
			Log() << LogInitializeError() << "Invalid argument - \"count\" is 0.";
			return false;
		}

		for (u32 i = 0; i < count; ++i)
		{
			VAttribute & attribute = attributes[i];
			if (attribute.buffer == nullptr)
			{
				Log() << LogInitializeError() << "Invalid argument - \"attribute[" << i << "].buffer\" is null.";
				return false;
			}

			if (attribute.buffer->Type() != GL_ARRAY_BUFFER)
			{
				Log() << LogInitializeError() << "Invalid argument - \"attribute[" << i << "].buffer\" is not a vertex or instance buffer.";
				return false;
			}

			if (!attribute.buffer->Valid())
			{
				Log() << LogInitializeError() << "Invalid argument - \"attribute[" << i << "].buffer\" is invalid.";
				return false;
			}

			if (attribute.type == VertexAttributeTypes::INVALID)
			{
				Log() << LogInitializeError() << "Invalid argument - \"attribute[" << i << "].type\" is invalid.";
				return false;
			}
		}
		// Create a vertex array object.
		glGenVertexArrays(1, &m_handle);

		if (m_handle == 0)
		{
			cout << LogInitializeError() << "Couldn't create a vertex array object.";
			Cleanup();
			return false;
		}

		// Bind the vertex array.
		glBindVertexArray(m_handle);

		// Set the vertex array state.
		Buffer* currentBuffer = nullptr;

		int currentLocation = 0;
		int currentOffset = 0;

		for (int i = 0; i < count; ++i)
		{
			VAttribute& attribute = attributes[i];

			// Bind the vertex buffer.
			if (currentBuffer != attribute.buffer)
			{
				glBindBuffer(GL_ARRAY_BUFFER, attribute.buffer->Handle());

				currentBuffer = attribute.buffer;
				currentOffset = 0;
			}

			// Setup vertex attributes for each used vertex location.
			for (int l = 0; l < GetVertexAttributeTypeRows(attribute.type); ++l)
			{
				// Enable vertex attribute.
				glEnableVertexAttribArray(currentLocation);

				// Set vertex attribute pointer.
				glVertexAttribPointer(
					currentLocation,
					GetVertexAttributeTypeSize(attribute.type),
					GetVertexAttributeTypeEnum(attribute.type),
					GL_FALSE,
					attribute.buffer->ElementSize(),
					(GLvoid*)currentOffset
					);

				// Make vertex location instanced.
				if (attribute.buffer->IsInstanced())
				{
					glVertexAttribDivisor(currentLocation, 1);
				}

				// Increment current location.
				currentLocation += 1;

				// Increment current offset.
				currentOffset += GetVertexAttributeTypeOffset(attribute.type);
			}
		}

		// Restore default state.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}

	void VertexAttribute::Cleanup()
	{
		if (m_handle != GL_NONE)
		{
			glDeleteVertexArrays(1, &m_handle);
			m_handle = GL_NONE;
		}
	}


}