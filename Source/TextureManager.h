#ifndef __TEXTUREMANAGER_
#define __TEXTUREMANAGER_

#include <assimp/include/assimp/scene.h>
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include <map>

class Application;

class TextureManager
{
	struct LessString
	{
		bool operator()(const aiString& left, const aiString& right) const
		{
			return ::strcmp(left.data, right.data) < 0;
		}
	};

	typedef std::map<aiString, unsigned, LessString> TextureList;
	TextureList textures;
	static std::auto_ptr <TextureManager> instance;

public:


	TextureManager();
	~TextureManager();


	unsigned Load(const aiString&);

	unsigned ForceLoad(const aiString & file);

	TextureManager * GetInstance();

	void Clear();

private:
};

#endif // __TEXTUREMANAGER_