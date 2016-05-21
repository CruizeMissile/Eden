#ifndef H_GRAPHICS_BINDONG_DESCRIPTOR_H
#define H_GRAPHICS_BINDONG_DESCRIPTOR_H



namespace edn
{
	class VertexBuffer;

	enum class VertexAttributeTypes
	{
		INVALID,

		Float1,
		Float2,
		Float3,
		Float4,

		Float4x4,

		UInt1,
		UInt2,
		UInt3,
		UInt4,

		UInt4x4,

		Count,
	};

	struct VAttribute
	{
		VertexBuffer * buffer;
		VertexAttributeTypes type;
	};

	class VertexAttribute
	{
	public:
		VertexAttribute();
		~VertexAttribute();

		bool Initialize(VAttribute * descriptorList, u32 count);
		void Cleanup();

		u32 Handle() { return m_handle; };
	private:
		u32 m_handle;
	};
}

#endif