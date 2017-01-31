#include "JsonParser.h"
#include "Globals.h"
#include "parson.h"

JsonParser::JsonParser(const char* file)
{
	json_file = json_value_get_object(json_parse_file(file));
}

JsonParser::~JsonParser()
{

}

bool JsonParser::LoadObject(const char * name)
{
	parsedObject = false;
	if (object == nullptr)
	{
		if (json_object_dothas_value(json_file, name))
		{
			object = json_object_dotget_object(json_file, name);
			parsedObject = true;
		}
		else 
			LOGCHAR("Object not loaded");
	}
	else 
		LOGCHAR("Object already loaded.");

	return parsedObject;
}

bool JsonParser::UnloadObject()
{
	bool return_value = parsedObject;

	//si parseObject esta a true es que esta el objeto cargado

	if (parsedObject == false)
		LOGCHAR("Parsing with errors.");

	parsedObject = true;
	object = nullptr;

	return return_value;

}

const char* JsonParser::GetString(const char* name)
{
	const char* return_value = nullptr;
	if (object != nullptr)
	{
		if (json_object_dothas_value_of_type(object, name, JSONString))
		{
			return_value = json_object_dotget_string(object, name);
		}
		else
		{
			LOGCHAR("Incorrect string value");
			parsedObject = false;
		}
	}
	else
	{
		LOGCHAR("No section loaded. Existing Object");
		parsedObject = true;
	}
	return return_value;
}


int JsonParser::GetInt(const char* name)
{
	int return_value = NULL;
	if (object != nullptr)
	{
		if (json_object_dothas_value_of_type(object, name, JSONNumber))
		{
			return_value = (int)json_object_dotget_number(object, name);
		}
		else
		{
			LOGCHAR("Incorrect integer value");
			parsedObject = false;
		}
	}
	else
	{
		LOGCHAR("No section loaded. Existing Object");
		parsedObject = false;
	}
	return return_value;
}

bool JsonParser::GetBool(const char* name)
{
	bool return_value = false;
	if (object != nullptr)
	{
		if (json_object_dothas_value_of_type(object, name, JSONBoolean))
			return_value = json_object_dotget_boolean(object, name) > 0 ? true : false;
		else
		{
			LOGCHAR("Incorrect boolean value");
			parsedObject = false;
		}
	}

	else
	{
		LOGCHAR("No section loaded. Existing Object");
		parsedObject = false;
	}
	return return_value;
}