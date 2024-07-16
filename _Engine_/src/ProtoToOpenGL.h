#ifndef PROTO_TO_OPEN_GL
#define PROTO_TO_OPEN_GL

#include "TextureData.h"
#include "sb7.h"

class ProtoToOpenGL
{
public:
	static GLenum Get(TextureData::TEXTURE_WRAP t);
	static GLenum Get(TextureData::TEXTURE_MAG_FILTER t);
	static GLenum Get(TextureData::TEXTURE_MIN_FILTER t);
	static GLenum Get(TextureData::TEXTURE_EFORMAT t);
	static GLint Get(TextureData::TEXTURE_NCOMPONENT t);

};

#endif // !PROTO_TO_OPEN_GL
