#include "SSBO.h"

Uncertain::SSBO::SSBO()
	:ShaderBufferObject(), ElementCount(0), ElementSize(0), poBuffer(nullptr)
{
	glGenBuffers(1, &ShaderBufferObject);
}

Uncertain::SSBO::~SSBO()
{
	glDeleteBuffers(1, &ShaderBufferObject);
}

void Uncertain::SSBO::Set(unsigned int elementCount, unsigned int elementSize, void* inData, unsigned int GL_USAGE)
{
	this->ElementCount = elementCount;
	this->ElementSize = elementSize;
	this->poBuffer = inData;

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ShaderBufferObject);
	glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)(ElementCount * ElementSize), poBuffer, GL_USAGE);
}

unsigned int Uncertain::SSBO::GetLocation() const
{
	return this->ShaderBufferObject;
}

void Uncertain::SSBO::Bind(unsigned int bindLocation)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindLocation, this->ShaderBufferObject);
}

void* Uncertain::SSBO::Map(Access accessType)
{
	void *res = glMapNamedBuffer(this->ShaderBufferObject, GLenum(accessType));
	assert(res);

	return res;
}

void Uncertain::SSBO::UnMap()
{
	glUnmapNamedBuffer(this->ShaderBufferObject);
}
