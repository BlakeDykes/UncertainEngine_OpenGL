#include "ProtoToOpenGL.h"

GLenum ProtoToOpenGL::Get(TextureData::TEXTURE_WRAP t)
{
	GLenum res;

	switch (t)
	{
	case TextureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE:
		res = GL_CLAMP_TO_EDGE;
		break;

	case TextureData::TEXTURE_WRAP::WRAP_MIRRORED_REPEAT:
		res = GL_MIRRORED_REPEAT;
		break;

	case TextureData::TEXTURE_WRAP::WRAP_REPEAT:
		res = GL_REPEAT;
		break;

	default:
		assert(false);
		res = GL_CLAMP_TO_EDGE;
	}

	return res;
}

GLenum ProtoToOpenGL::Get(TextureData::TEXTURE_MAG_FILTER t)
{
	GLenum res;

	switch (t)
	{
	case TextureData::TEXTURE_MAG_FILTER::MAG_NEAREST:
		res = GL_NEAREST;
		break;

	case TextureData::TEXTURE_MAG_FILTER::MAG_LINEAR:
		res = GL_LINEAR;
		break;

	default:
		res = GL_LINEAR;
		break;
	}

	return res;
}

GLenum ProtoToOpenGL::Get(TextureData::TEXTURE_MIN_FILTER t)
{
	GLenum res;

	switch (t)
	{
	case TextureData::TEXTURE_MIN_FILTER::MIN_NEAREST:
		res = GL_NEAREST;
		break;

	case TextureData::TEXTURE_MIN_FILTER::MIN_LINEAR:
		res = GL_LINEAR;
		break;

	case TextureData::TEXTURE_MIN_FILTER::MIN_NEAREST_MIPMAP_NEAREST:
		res = GL_NEAREST_MIPMAP_NEAREST;
		break;

	case TextureData::TEXTURE_MIN_FILTER::MIN_LINEAR_MIPMAP_NEAREST:
		res = GL_LINEAR_MIPMAP_NEAREST;
		break;

	case TextureData::TEXTURE_MIN_FILTER::MIN_NEAREST_MIPMAP_LINEAR:
		res = GL_NEAREST_MIPMAP_LINEAR;
		break;

	case TextureData::TEXTURE_MIN_FILTER::MIN_LINEAR_MIPMAP_LINEAR:
		res = GL_LINEAR_MIPMAP_LINEAR;
		break;

	default:
		res = GL_LINEAR;
		break;
	}

	return res;
}


GLenum ProtoToOpenGL::Get(TextureData::TEXTURE_EFORMAT t)
{
	GLenum val = 0;

	switch (t)
	{
	case TextureData::TEXTURE_EFORMAT::EFORMAT_BGR:
		val = GL_BGR;
		break;

	case TextureData::TEXTURE_EFORMAT::EFORMAT_BGRA:
		val = GL_BGRA;
		break;

	case TextureData::TEXTURE_EFORMAT::EFORMAT_RGB:
		val = GL_RGB;
		break;

	case TextureData::TEXTURE_EFORMAT::EFORMAT_RGBA:
		val = GL_RGBA;
		break;

	default:
		assert(false);
	}

	return val;
}

GLint ProtoToOpenGL::Get(TextureData::TEXTURE_NCOMPONENT t)
{
	GLint val = 0;

	switch (t)
	{
	case TextureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR:
		val = GL_BGR;
		break;

	case TextureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA:
		val = GL_BGRA;
		break;

	case TextureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB:
		val = GL_RGB;
		break;

	case TextureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA:
		val = GL_RGBA;
		break;

	default:
		assert(false);
	}

	return val;
}

