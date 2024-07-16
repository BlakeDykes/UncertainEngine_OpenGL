#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "sb7.h"
#include "EngineNames.h"
#include "DLink.h"

class ShaderObject : public DLink
{
public:

	static const char* SHADER_DIR;
	static const char* COMPUTE_EXTENSION;
	static const char* FRAGMENT_EXTENSION;
	static const char* VERTEX_EXTENSION;

	enum class ShaderType
	{
		GRAPHICS,
		COMPUTE,
		UNINITIALIZED
	};

	ShaderName Name;
	GLuint ProgramObject;
	ShaderType Type;
	GLuint FS;
	GLuint VS;
	GLuint CS;

	ShaderObject();
	ShaderObject(const ShaderObject&) = delete;
	ShaderObject& operator=(const ShaderObject&) = delete;
	virtual ~ShaderObject();

	ShaderObject(ShaderType type, ShaderName shaderName, const char* const shaderBaseFileName);

	void Set(ShaderType type, ShaderName shaderName, const char* const shaderBaseFileName);
	void SetActive() const;
	void Dispatch(unsigned int work_group_x, unsigned int work_group_y, unsigned int work_group_z);
	GLint GetLocation(const char* const uniformName) const;

	virtual const char* GetName() override;
	virtual bool Compare(NodeBase& pNode) override;
	virtual void Print() override;
	virtual void Wash() override;

protected:
	bool CreateGraphicsShader(GLuint& programObject, const char* const shaderBaseFileName);
	bool CreateComputeShader(GLuint& programObject, const char* const shaderBaseFileName);
	bool LoadAndCompile(GLuint& shaderObject, const char* const shaderFileName, GLenum shaderType);
	void Clear();
};



#endif // !SHADER_OBJECT_H

