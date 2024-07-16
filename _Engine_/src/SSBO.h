#ifndef SSBO_H
#define SSBO_H

#include "sb7.h"

namespace Uncertain
{
	class SSBO
	{
	public:

		enum class Access
		{
			READ_ONLY = GL_READ_ONLY,
			WRITE_ONLY = GL_WRITE_ONLY,
			READ_WRITE = GL_READ_WRITE
		};

		SSBO();
		SSBO(const SSBO&) = delete;
		const SSBO& operator=(const SSBO&) = delete;
		~SSBO();

		void Set(unsigned int elementCount, unsigned int size, void *inData, unsigned int GL_USAGE);

		unsigned int GetLocation() const;
		void Bind(unsigned int bindLocation);

		void* Map(Access accessType);
		void UnMap();
	
	private:
		GLuint ShaderBufferObject;
		unsigned int ElementCount;
		unsigned int ElementSize;
		void* poBuffer;
	};
}


#endif // !SSBO_H
