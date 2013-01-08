#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H


#include <GL/glut.h>


// TODO (Viet Nguyen): BAD NEWS! This development environment doesn't support shaders!
class VertexShader
{
public:

	VertexShader(const char* fileName);
	~VertexShader();

	GLuint GetCompileStatus();
	bool IsCompiled();
	GLbyte* GetInfoLog();
	unsigned int GetInfoLogLength();

private:

	char*			_fileName;
	unsigned int	_fileLength;
	GLbyte*			_shaderSource;
	
	GLuint			_compileStatus;
	bool			_isCompiled;
	GLbyte*			_infoLog;
	unsigned int	_infoLogLength;

	GLuint			_shaderObject;
	GLuint			_programObject;
};


#endif // VERTEX_SHADER_H