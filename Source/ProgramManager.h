#ifndef __PROGRAMMANAGER_H_
#define __PROGRAMMANAGER_H_

/*#include "Devil\include\IL\ilut.h"
#include "assimp\include\assimp\cimport.h"*/
//#include <assimp\include\assimp\postprocess.h>
#include <assimp/include/assimp/scene.h>
#include <map>
#include <vector>

class Application;

class ProgramManager 
{
	struct LessString
	{
		bool operator()(const aiString& left, const aiString& right) const
		{
			return ::strcmp(left.data, right.data) < 0;
		}
	};

	typedef std::map<aiString, unsigned, LessString> ProgramList;
	ProgramList programs;
	//static std::auto_ptr<ProgramManager> instance;


public:
	ProgramManager();
	~ProgramManager();

	GLuint Load(const char* name, const char* vertex_shader, const char* fragment_shader);
	void Clear();

	int GetUniformLocation(const char* name, const char* uniform);
	void useProgram(const char* name);
	void UnuseProgram();

	static ProgramManager* GetInstance();
	//void Log(std::vector<GLchar> &log_to_print);
};
#endif


