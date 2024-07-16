#ifndef MESH_FILE_HDR_H
#define MESH_FILE_HDR_H

namespace Uncertain
{
	struct MeshFileHdr
	{
	public:
		static const unsigned int OBJECT_NAME_SIZE = 32;
		static const unsigned int TEXTURE_NAME_SIZE = 32;

		char ObjName[OBJECT_NAME_SIZE];
		int numVerts;
		int numTriList;
		
		DWORD vertexBufferOffset;
		DWORD normsBufferOffset;
		DWORD textsBufferOffset;
		DWORD triListBufferdOffset;

		MeshFileHdr();
		MeshFileHdr(const MeshFileHdr&) = delete;
		MeshFileHdr& operator=(const MeshFileHdr&) = delete;
		virtual ~MeshFileHdr() = default;
	};
}

#endif // !MESH_FILE_HDR_H
