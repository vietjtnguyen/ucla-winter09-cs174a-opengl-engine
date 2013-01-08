#include <fstream>

#include "VertexShader.h"


using namespace std;


VertexShader::VertexShader(const char *fileName)
:_fileName(NULL)
,_fileLength(0)
,_shaderSource(NULL)
,_compileStatus(0)
,_isCompiled(false)
,_infoLog(NULL)
,_infoLogLength(0)
,_shaderObject(NULL)
,_programObject(NULL)
{
	fstream fileStream;
	fileStream.open(fileName, fstream::in);

	if( fileStream.is_open() )
	{
		// Get file length
		fileStream.seekg(0, ios::end);
		this->_fileLength = fileStream.tellg();
		fileStream.seekg(0, ios::beg);

		if( this->_fileLength == 0 )
		{
			delete this;
			return;
		}

		//glCreateShader();
	}
	else
	{
		delete this;
		return;
	}
}


VertexShader::~VertexShader()
{
	delete this->_fileName;
	delete this->_shaderSource;
	delete this->_infoLog;
	//glDeleteShader(this->_shaderObject);
	//glDeleteProgram(this->_programObject);
}