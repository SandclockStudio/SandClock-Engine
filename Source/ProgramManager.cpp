#include "../Libraries/OpenGL/include/GL/glew.h"
#include "ProgramManager.h"

static std::auto_ptr<ProgramManager> instance;

void Log(std::vector<GLchar> &log_to_print)
{
	
}

ProgramManager::ProgramManager()
{

}

ProgramManager::~ProgramManager()
{
}

GLuint ProgramManager::Load(const char * name, const char * vertex_shader, const char * fragment_shader)
{
	std::map<aiString, unsigned>::iterator it;

	it = programs.find(aiString(name));

	if (it != programs.end())
	{
		return (*it).second;
	}

	GLuint program = glCreateProgram();
	GLuint vertex;
	GLuint fragment;
	FILE* file;
	GLint file_size = 0;
	GLint result = 0;
	char* file_buffer;

	if (vertex_shader != nullptr)
	{
		file = fopen(vertex_shader,"r");
		if (file != nullptr) 
		{
			fseek(file, 0, SEEK_END);
			file_size = ftell(file) + 1;
			file_buffer = (char*)malloc(file_size);
			memset(file_buffer, 0, file_size);
			rewind(file);
			fread(file_buffer, file_size, 1, file);
			//Add EOF
			file_buffer[file_size - 1] = '\0';

			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &file_buffer, &file_size);
			glCompileShader(vertex);

			free(file_buffer);
			fclose(file);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (result != GL_FALSE)
			{
				glAttachShader(program, vertex);
			}

			glDeleteShader(vertex);
		}
	}

	if (fragment_shader != nullptr)
	{
		file = fopen(fragment_shader, "r");
		if (file != nullptr) 
		{
			fseek(file, 0, SEEK_END);
			file_size = ftell(file) + 1;
			file_buffer = (char*)malloc(file_size);
			memset(file_buffer, 0, file_size);
			rewind(file);
			fread(file_buffer, file_size, 1, file);
			//Add EOF
			file_buffer[file_size - 1] = '\0';

			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &file_buffer, &file_size);
			glCompileShader(fragment);

			free(file_buffer);
			fclose(file);

			result = 0;
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result != GL_FALSE)
			{
				glAttachShader(program, vertex);
			}
			glDeleteShader(vertex);
		}

		GLint programResult = 0;
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &programResult);
		if (programResult != GL_FALSE)
		{
			programs[aiString(name)] = program;
			return program;
		}
		else
			return - 1;
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
	std::map<aiString, unsigned, LessString>::iterator it;

	it = programs.find(aiString(name));
	if (it == programs.end())
		return;
	else
		glUseProgram((*it).second);
}

void ProgramManager::UnuseProgram()
{
	glUseProgram(0);
}

ProgramManager * ProgramManager::GetInstance()
{
	if (!instance.get() == NULL)
	{
		instance = std::auto_ptr<ProgramManager>(new ProgramManager);
	}
	return instance.get();
			
}


