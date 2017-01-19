#ifndef __JSON_PARSER_H_
#define __JSON_PARSER_H_

#include "Globals.h"
#include "parson.h"



class JsonParser
{

public:
	JsonParser(const char* file);
	~JsonParser();
	bool LoadObject(const char* name);
	bool UnloadObject();

	const char* GetString(const char* name);
	int GetInt(const char* name);
	bool GetBool(const char* name);

	JSON_Object* json_file = nullptr;
	JSON_Object* object = nullptr;
	bool parsedObject = false;
};





#endif