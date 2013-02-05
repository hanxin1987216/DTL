/***************************************************************************************************
jsontextwriter.cpp:
	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
	json text writer
		
Author:
	Lyre
	
Creating Time:
	2012-03-26
***************************************************************************************************/
#include "../prec.h"
#include "../lang/string.h"
#include "../lang/int64.h"
#include "../sys/exception.h"

#include "jsontextwriter.h"


JsonTextWriter::JsonTextWriter ()
	: _jsonStr (String::EMPTY)
	, _current ()
	, _root ()
	, _jsonObjectStack ()
	, _hasEnd (false)
{
}

JsonTextWriter::~JsonTextWriter (void)
{
	if (_root.getPtr ())
		cJSON_Delete (_root.getPtr ());
}

void JsonTextWriter::StartArray (const String &label)
{
	cJSON *tmp = cJSON_CreateArray ();
	JsonPointNode tmpNode (JSON_NODE_ARRAY, tmp, label);
	_current = tmpNode;
	
	if (_jsonObjectStack.empty ())
		_root = _current;
		
	_jsonObjectStack.push (tmpNode);	
}

void JsonTextWriter::EndArray ()
{
	// 
	// ÍêÕûÊÕÎ²
	//
	if (_current == _root) {
		char* json = cJSON_Print (_root.getPtr ());
		_jsonStr = json;
		free (json);
		_hasEnd = true;
		return ;
	}

	if (_jsonObjectStack.size () > 1)
	{
		_jsonObjectStack.pop ();
	}
			
	if (_jsonObjectStack.top ().getType () == JSON_NODE_ARRAY)
		cJSON_AddItemToArray (_jsonObjectStack.top ().getPtr (), _current.getPtr ());
	else
		cJSON_AddItemToObject (_jsonObjectStack.top ().getPtr (), _current.getLabel ().getCStr (), _current.getPtr ());
	
	_current = _jsonObjectStack.top ();
}

void JsonTextWriter::StartObject (const String &label, cJSON * jsonObject)
{
	cJSON *tmp = NULL;
	if (jsonObject == NULL)
		tmp = cJSON_CreateObject ();
	else
		tmp = jsonObject;
		
	JsonPointNode tmpNode (JSON_NODE_OBJECT, tmp, label);
	_current = tmpNode;
	
	if (_jsonObjectStack.empty ())
		_root = _current;
		
	_jsonObjectStack.push (tmpNode);
}

void JsonTextWriter::EndObject ()
{
	if (_current == _root) {
		char *json = cJSON_Print (_root.getPtr ());	
		_jsonStr = json;
		free (json);
		_hasEnd = true;
		return ;
	}
	
	if (_jsonObjectStack.size () > 1)
	{
		_jsonObjectStack.pop ();
	}
	
	if (_jsonObjectStack.top ().getType () == JSON_NODE_ARRAY)
		cJSON_AddItemToArray (_jsonObjectStack.top ().getPtr (), _current.getPtr ());
	else
		cJSON_AddItemToObject (_jsonObjectStack.top ().getPtr (), _current.getLabel ().getCStr (), _current.getPtr ());

	_current = _jsonObjectStack.top ();
}

void JsonTextWriter::WriteElement (const char *label, const String &value)
{
	WriteString (label, value);
}

void JsonTextWriter::WriteElement (const char *label, const char* value)
{
	String values (value);
	WriteString (label, values);
}

void JsonTextWriter::WriteElement (const char *label, const int value)
{
	WriteNumber<int> (label, value);
}

void JsonTextWriter::WriteElement (const char *label, const unsigned int value)
{
	WriteNumber<unsigned int> (label, value);
}

void JsonTextWriter::WriteElement (const char *label, const int64 value)
{
	String strValue = Int64::toString(value);
	WriteString (label, strValue);
}

void JsonTextWriter::WriteElement (const char *label, const short value)
{
	WriteNumber<short> (label, value);
}

void JsonTextWriter::WriteElement (const char *label, const unsigned short value)
{
	WriteNumber<unsigned short> (label, value);
}

void JsonTextWriter::WriteElement (const char *label, const bool value)
{
	WriteBool (label, value);
}

void JsonTextWriter::WriteString (const char *label, const String &value)
{
	if (_current.getType () == JSON_NODE_OBJECT)
	{
		cJSON_AddStringToObject (_current.getPtr (), label, value.getCStr ());
	}
	else if (_current.getType() == JSON_NODE_ARRAY)
	{
		cJSON *pItem = cJSON_CreateString(value.getCStr());
		cJSON_AddItemToArray(_current.getPtr(), pItem);
	}
	else
	{
		//
		// TODO: excption 
		//
	}
}

template <class T>
void JsonTextWriter::WriteNumber (const char *label, const T value)
{
	if (_current.getType() == JSON_NODE_OBJECT)
	{
		cJSON_AddNumberToObject (_current.getPtr (), label, value);
	}
	else if (_current.getType() == JSON_NODE_ARRAY)
	{
		cJSON *pItem = cJSON_CreateNumber(value);
		cJSON_AddItemToArray(_current.getPtr(), pItem);
	}
}

void JsonTextWriter::WriteBool (const char *label, const bool value)
{
	cJSON *item = NULL;
	if (value)
	{
		item = cJSON_CreateTrue();
		//cJSON_AddTrueToObject (_current.getPtr (), label);
	}
	else
	{
		item = cJSON_CreateFalse();
		//cJSON_AddFalseToObject (_current.getPtr (), label);
	}
	if (_current.getType() == JSON_NODE_OBJECT)
	{
		cJSON_AddItemToObject(_current.getPtr(), label, item);
	}
	else if (_current.getType() == JSON_NODE_ARRAY)
	{
		cJSON_AddItemToArray(_current.getPtr(), item);
	}
}

void JsonTextWriter::WriteNull (const char *label)
{
	if (_current.getType() == JSON_NODE_OBJECT)
	{
		cJSON_AddNullToObject (_current.getPtr (), label);
	}
	else if (_current.getType() == JSON_NODE_ARRAY)
	{
		cJSON *item = cJSON_CreateNull();
		cJSON_AddItemToArray(_current.getPtr(), item);
	}
}

String
JsonTextWriter::getJsonStr ()
{
	if (_hasEnd)
		return _jsonStr;
	else
		THROW ("Json Struct is not Correct");
}


cJSON* 
JsonTextWriter::getJsonObject(void)
{
	if (_hasEnd)
		return _root.getPtr();
	else
		THROW ("Json Struct is not Correct");	
}