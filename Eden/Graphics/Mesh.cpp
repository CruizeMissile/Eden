#include "Precompiled.h"
#include "Mesh.h"
#include "Math/Vector.h"

using namespace std;

namespace edn
{
	void WriteCacheFile(String name, string subDir, std::vector<Vertex>& data);

	struct IndexData
	{
		u32 vertex[3];
		u32 normal[3];
		u32 uv[3];
		u32 tangent[3];
		u32 bitangent[3];
	};

	const vec3 CONSTUP(0, 1, 0);

	void Mesh::loadFromFile(String filename)
	{
		vector<vec3> vertices;
		vector<vec3> normals;
		vector<vec2> uvs;
		vector<vec3> tangents;
		vector<vec3> bitangents;
		vector<IndexData> faces;
		vector<Vertex> bufferData;


		// Checking to see what type of file this is
		// loading obj mesh file
		
		ifstream input(filename);

		u32 f = 0;
		char buffer[256];
		while (input.getline(buffer, 256))
		{
			switch (buffer[0])
			{
			case 'v':
			{
				static float x, y, z, u, v;
				switch (buffer[1])
				{
				case ' ': 
				{
					sscanf_s(buffer, "v  %f %f %f", &x, &y, &z);
					vertices.push_back(vec3(x, y, z));
				}break;
				case 'n': 
				{
					sscanf_s(buffer, "v  %f %f %f", &x, &y, &z);
					normals.push_back(vec3(x, y, z));
				} break;
				case 't':
				{
					sscanf_s(buffer, "v  %f %f", &x, &y);
					uvs.push_back(vec2(x, y));
				}break;
				}
			}break;
			case 'f':
			{
				static u32 vi[3], ui[3], ni[3];
				static u8 matches;
				
				matches = sscanf_s(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&vi[0], &ui[0], &ni[0],
					&vi[1], &ui[1], &ni[1],
					&vi[2], &ui[2], &ni[2]);

				assert(("File has either no Normals or UVs", matches == 9));

				IndexData face;
				face.vertex[0] = vi[0] - 1;
				face.vertex[1] = vi[1] - 1;
				face.vertex[2] = vi[2] - 1;
				face.normal[0] = ni[0] - 1;
				face.normal[1] = ni[1] - 1;
				face.normal[2] = ni[2] - 1;
				face.uv[0] = ui[0] - 1;
				face.uv[1] = ui[1] - 1;
				face.uv[2] = ui[2] - 1;

				for (u8 j = 0; j < 3; ++j)
				{
					// tangent calculation
					vec3 t = Cross(CONSTUP, normals[face.normal[j]]);
					t.x = truncf(1000000.0f * t.x) / 1000000.0f;
					t.y = truncf(1000000.0f * t.y) / 1000000.0f;
					t.z = truncf(1000000.0f * t.z) / 1000000.0f;
					tangents.push_back(t);
					face.tangent[j] = (u32)tangents.size() - 1;

					// bitangent calculation
					vec3 b = Cross(t, normals[face.normal[j]]);
					b.x = truncf(1000000.0f * b.x) / 1000000.0f;
					b.y = truncf(1000000.0f * b.y) / 1000000.0f;
					b.z = truncf(1000000.0f * b.z) / 1000000.0f;
					bitangents.push_back(b);
					face.bitangent[j] = (u32)bitangents.size() - 1;
				}
				
				faces.push_back(face);
			}break;
			}
		}

		for (u32 i = 0; i < faces.size(); ++i)
		{
			for (u8 j = 0; j < 3; ++j)
			{
				Vertex vert =
				{
					{ vertices[faces[i].vertex[j]] },
					{ normals[faces[i].normal[j]] },
					{ uvs[faces[i].uv[j]] },
					{ tangents[faces[i].tangent[j]] },
					{ bitangents[faces[i].bitangent[j]] },
				};
				bufferData.push_back(vert);
			}
		}

		u32 bufferSize = sizeof(float) * bufferData.size();

		VAttribute attributes[] =
		{
			{ &m_buffer, VertexAttributeTypes::Float3 }, // Vertex
			{ &m_buffer, VertexAttributeTypes::Float3 }, // Normals
			{ &m_buffer, VertexAttributeTypes::Float2 }, // uvs
			{ &m_buffer, VertexAttributeTypes::Float3 }, // tangent
			{ &m_buffer, VertexAttributeTypes::Float3 }, // bitangent
		};

		m_buffer.Initialize(sizeof(Vertex), sizeof(bufferData), bufferData.data(), GL_STATIC_DRAW);

		m_attributes.Initialize(&attributes[0], StaticArraySize(attributes));

		WriteCacheFile(m_name, m_subDir, bufferData);

		// clearing all of the temp memeory
		ClearContainer(vertices);
		ClearContainer(normals);
		ClearContainer(uvs);
		ClearContainer(tangents);
		ClearContainer(bitangents);
		ClearContainer(faces);

	}

	void Mesh::loadFromCashe(String filename)
	{
		FILE * file = nullptr;
		u32 numVertices = 0;
		fopen_s(&file, filename.c_str(), "rb");
		
		fread(&numVertices, sizeof(u32), 1, file);
		
		Vertex * data = (Vertex*)malloc(sizeof(Vertex) * numVertices);
		fread(data, sizeof(Vertex), numVertices, file);
		fclose(file);

		VAttribute attributes[] =
		{
			{ &m_buffer, VertexAttributeTypes::Float3 }, // Vertex
			{ &m_buffer, VertexAttributeTypes::Float3 }, // Normals
			{ &m_buffer, VertexAttributeTypes::Float2 }, // uvs
			{ &m_buffer, VertexAttributeTypes::Float3 }, // tangent
			{ &m_buffer, VertexAttributeTypes::Float3 }, // bitangent
		};

		m_buffer.Initialize(sizeof(Vertex), numVertices, data, GL_STATIC_DRAW);

		m_attributes.Initialize(&attributes[0], StaticArraySize(attributes));
	}

	void Mesh::writeCacheFile(String filename)
	{

	}

	void WriteCacheFile(String name, string subDir, std::vector<Vertex>& data)
	{
		String path = os::MakePath(AssetManager::CachePath(), subDir, name + ".dat");
		
		u32 numVertex = data.size();
		
		FILE * file = nullptr;
		fopen_s(&file, path.c_str(), "wb");

		fwrite(&numVertex, sizeof(u32), 1, file);
		fwrite(data.data(), sizeof(Vertex), numVertex, file);
		fclose(file);
	}
}