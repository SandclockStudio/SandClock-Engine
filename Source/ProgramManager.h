#ifndef __PROGRAMMANAGER_H_
#define __PROGRAMMANAGER_H_

#include "Globals.h"
#include "Devil\include\IL\ilut.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include <assimp/include/assimp/scene.h>
#include <map>

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



public:

	ProgramManager();
	~ProgramManager();

	GLuint Load(const char* name, const char* vertex_shader, const char* fragment_shader);
	void Clear();

	int GetUniformLocation(const char* name, const char* uniform);
	void useProgram(const char* name);
	void UnuseProgram();

	static ProgramManager* GetInstance();
};
#endif


