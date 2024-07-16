#include "ShaderObject.h"
#include "MathEngine.h"
#include "File.h"
#include "Game.h"
#include "GameObject.h"

using namespace Uncertain;


const char* ShaderObject::SHADER_DIR			= "../Shaders/";
const char* ShaderObject::COMPUTE_EXTENSION		= ".cs.glsl\0";
const char* ShaderObject::FRAGMENT_EXTENSION	= ".fs.glsl\0";
const char* ShaderObject::VERTEX_EXTENSION		= ".vs.glsl\0";


ShaderObject::ShaderObject()
	:Name(ShaderName::UNINITIALIZED), ProgramObject(0), Type(ShaderType::UNINITIALIZED), FS(0), VS(0), CS(0)
{
}

ShaderObject::ShaderObject(ShaderType type, ShaderName shaderName, const char* const shaderBaseFileName)
	:Name(shaderName), ProgramObject(0), Type(type), FS(0), VS(0), CS(0)
{
	assert(shaderBaseFileName);

	switch (type)
	{
	case ShaderObject::ShaderType::GRAPHICS:
		CreateGraphicsShader(this->ProgramObject, shaderBaseFileName);
		break;
	case ShaderObject::ShaderType::COMPUTE:
		CreateComputeShader(this->ProgramObject, shaderBaseFileName);
		break;
	case ShaderObject::ShaderType::UNINITIALIZED:
		break;
	default:
		break;
	}

}

ShaderObject::~ShaderObject()
{
	this->Clear();
}

GLint ShaderObject::GetLocation(const char* const uniformName) const
{
	assert(uniformName);

	GLint loc = glGetUniformLocation(this->ProgramObject, uniformName);
	assert(loc != -1);

	return loc;
}

void ShaderObject::Set(ShaderType type, ShaderName shaderName, const char* const shaderBaseFileName)
{
	this->Type = type;
	this->Name = shaderName;

	switch (type)
	{
	case ShaderObject::ShaderType::GRAPHICS:
		CreateGraphicsShader(this->ProgramObject, shaderBaseFileName);
		break;
	case ShaderObject::ShaderType::COMPUTE:
		CreateComputeShader(this->ProgramObject, shaderBaseFileName);
		break;
	case ShaderObject::ShaderType::UNINITIALIZED:
	default:
		assert(false);
		break;
	}

}

void ShaderObject::SetActive() const
{
	glUseProgram(this->ProgramObject);
}

void ShaderObject::Dispatch(unsigned int work_group_x, unsigned int work_group_y, unsigned int work_group_z)
{
	if (this->Type == ShaderType::COMPUTE)
	{
		glDispatchCompute(work_group_x, work_group_y, work_group_z);
	}
}

bool ShaderObject::CreateGraphicsShader(GLuint& programObject, const char* const shaderBaseFileName)
{
	bool status;
	assert(shaderBaseFileName != 0);

	size_t vsLength = strlen(SHADER_DIR) + strlen(shaderBaseFileName) + strlen(VERTEX_EXTENSION) + 1;
	size_t fsLength = strlen(SHADER_DIR) + strlen(shaderBaseFileName) + strlen(FRAGMENT_EXTENSION) + 1;

	char* vsBuff = new char[vsLength]();
	char* fsBuff = new char[fsLength]();

	strcpy_s(fsBuff, fsLength, SHADER_DIR);
	strcat_s(fsBuff, fsLength, shaderBaseFileName);
	strcat_s(fsBuff, fsLength, FRAGMENT_EXTENSION);

	status = LoadAndCompile(this->FS, fsBuff, GL_FRAGMENT_SHADER);
	assert(status);

	strcpy_s(vsBuff, vsLength, SHADER_DIR);
	strcat_s(vsBuff, vsLength, shaderBaseFileName);
	strcat_s(vsBuff, vsLength, VERTEX_EXTENSION);

	status = LoadAndCompile(this->VS, vsBuff, GL_VERTEX_SHADER);
	assert(status);

	programObject = glCreateProgram();

	glAttachShader(programObject, this->VS);
	glAttachShader(programObject, this->FS);

	glLinkProgram(programObject);

	delete[] vsBuff;
	delete[] fsBuff;

	return true;
}

bool ShaderObject::CreateComputeShader(GLuint& programObject, const char* const shaderBaseFileName)
{
	bool status;
	assert(shaderBaseFileName != 0);

	size_t computeLength = strlen(SHADER_DIR) + strlen(shaderBaseFileName) + strlen(COMPUTE_EXTENSION) + 1;

	char* computeBuff = new char[computeLength]();

	strcpy_s(computeBuff, computeLength, SHADER_DIR);
	strcat_s(computeBuff, computeLength, shaderBaseFileName);
	strcat_s(computeBuff, computeLength, COMPUTE_EXTENSION);

	status = LoadAndCompile(this->CS, computeBuff, GL_COMPUTE_SHADER);
	assert(status);

	programObject = glCreateProgram();

	glAttachShader(programObject, this->CS);
	glLinkProgram(programObject);

	delete[] computeBuff;

	return true;
}

bool ShaderObject::LoadAndCompile(GLuint& shaderObject, const char* const shaderFileName, GLenum shaderType)
{
	File::Handle fh;
	File::Error fError;

	fError = File::Open(fh, shaderFileName, File::Mode::READ);
	assert(fError == File::Error::SUCCESS);

	fError = File::Seek(fh, File::Position::END, 0);
	assert(fError == File::Error::SUCCESS);

	DWORD numBytes;
	fError = File::Tell(fh, numBytes);
	assert(fError == File::Error::SUCCESS);
	assert(numBytes > 0);

	fError = File::Seek(fh, File::Position::BEGIN, 0);
	assert(fError == File::Error::SUCCESS);

	char* data = new char[numBytes + 1];
	assert(data != 0);

	fError = File::Read(fh, data, numBytes);
	assert(fError == File::Error::SUCCESS);

	data[numBytes] = 0x0;

	fError = File::Close(fh);
	assert(fError == File::Error::SUCCESS);

	shaderObject = glCreateShader(shaderType);
	assert(shaderObject != 0);

	glShaderSource(shaderObject, 1, &data, 0);
	delete[] data;

	glCompileShader(shaderObject);

	GLint status = 0;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		char buffer[4096];
		glGetShaderInfoLog(shaderObject, 40996, NULL, buffer);

		Trace::out("Error Compiling Shader -  %s: %s", shaderFileName, buffer);

		glDeleteShader(shaderObject);
		assert(false);
		return false;
	}
	else
	{
		return true;
	}

}

const char* ShaderObject::GetName()
{
	return Stringify(this->Name);
}

bool ShaderObject::Compare(NodeBase& pNode)
{
	ShaderObject* pComp = (ShaderObject*)&pNode;

	return this->Name == pComp->Name;
}

void ShaderObject::Print()
{
	const char* programCreated = 
		(this->ProgramObject != 0 && 
		(
		(this->FS != 0 && 
		this->VS != 0) 
		|| this->CS != 0)
		) 
		? "true" : "false";
	
	Trace::out("ShaderObject ------ 0x%p\n", this);
	Trace::out("---Name:			%s\n", Stringify(this->Name));
	Trace::out("---Program Created: %s\n", programCreated);
	
	DLink::Print();
}

void ShaderObject::Wash()
{
	this->Clear();
}

void ShaderObject::Clear()
{
	if (this->ProgramObject)
	{
		glUseProgram(0);
		glDeleteProgram(this->ProgramObject);
		glDeleteShader(this->FS);
		glDeleteShader(this->VS);
		glDeleteShader(this->CS);
	}

	this->Name = ShaderName::UNINITIALIZED;
	this->Type = ShaderType::UNINITIALIZED;
	this->ProgramObject = 0;
	this->FS = 0;
	this->VS = 0;
	this->CS = 0;
}
