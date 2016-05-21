#ifndef H_GRAPHICS_MESH_H
#define H_GRAPHICS_MESH_H

#include "Precompiled.h"
#include "Core/AssetManager.h"
#include "Buffer.h"
#include "VertexAttribute.h"
#include "Math/Vector.h"

namespace edn
{
	struct Vertex
	{
		vec3 vertex;
		vec3 normal;
		vec2 uv;
		vec3 tangent;
		vec3 bitangent;
	};

	class Mesh : public Asset
	{
	public:
		Mesh()
		{
			m_subDir = "Mesh";
		}

		// Overloading Assets Pure virtual functions
		virtual void loadFromFile(String filename) override;
		virtual void loadFromCashe(String filename) override;
		virtual void writeCacheFile(String filename) override;

	private:
		VertexAttribute m_attributes;
		VertexBuffer m_buffer;
	};
}

#endif