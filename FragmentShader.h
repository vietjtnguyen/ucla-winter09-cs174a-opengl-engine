#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H


#include <GL/glut.h>


class FragmentShader
{
public:

	FragmentShader(const char* fileName);
	~FragmentShader();

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


#endif // FRAGMENT_SHADER_H