
#include "../Libraries/OpenGL/include/GL/glew.h"

#include "ProgramManager.h"

std::auto_ptr<ProgramManager> ProgramManager::instance;

ProgramManager::ProgramManager()
{

}

ProgramManager::~ProgramManager()
{
}

void ProgramManager::Load(const char * name, const char * vertex_shader, const char * fragment_shader)
{
	std::map<aiString, unsigned>::iterator it;
	for (it = programs.begin(); it != programs.end(); it++)
	{
		if (strcmp(name, it->first.C_Str()) != 0)
		{
			break;
		}
		
	}

	//Lo hemos encontrado, es it->second
	if (it != programs.end()) 
	{
		

	}
	else //No hemos encontrado el programa, lo creamos y añadimos
	{
		//TODO LEER EL FICHERO DE VERTEX
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

		//const GLchar * source;
		//glShaderSource(vertex, );

	}


}

void ProgramManager::Clear()
{
}

int ProgramManager::GetUniformLocation(const char * name, const char * uniform)
{
	return 0;
}

void ProgramManager::useProgram(const char * name)
{
}

void ProgramManager::UnuseProgram()
{
}

ProgramManager * ProgramManager::GetInstance()
{
	if (!instance.get() == NULL)
	{
		instance = std::auto_ptr<ProgramManager>(new ProgramManager);
	}
	return instance.get();
			
}
