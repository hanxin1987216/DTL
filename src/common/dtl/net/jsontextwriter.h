/***************************************************************************************************
jsontextwriter.h:
	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
	json text writer
		
Author:
	Lyre
	
Creating Time:
	2012-03-26
***************************************************************************************************/
#ifndef _DTL_NET_JSONTEXTWRITER_H_
#define _DTL_NET_JSONTEXTWRITER_H_

#include <dtprec.h>
#include <stack>
#include "json.h"

enum JsonNodeType
{
	JSON_NODE_UNINIT = 0,
	JSON_NODE_ARRAY = 1,
	JSON_NODE_OBJECT,
};

class DTL_DLLEXPORT JsonPointNode
{
public:
	JsonPointNode ()
	{
		_type = JSON_NODE_UNINIT;
		_ptr = NULL;
		_label = String::EMPTY;
	}
	
	JsonPointNode (const JsonNodeType type, cJSON *ptr, const String &label = String::EMPTY)
	{
		_type = type;
		_ptr = ptr;
		_label = label;
	}
	
	JsonPointNode (const JsonPointNode &node)
	{
		_type = node.getType ();
		_ptr = node.getPtr ();
		_label = node.getLabel ();
	}
	
	JsonPointNode& operator =(JsonPointNode& node)
	{
		this->_type = node.getType ();
		this->_ptr = node.getPtr ();
		this->_label = node.getLabel ();
		return *this;
	}
	
	bool operator ==(JsonPointNode& node)
	{
		return (this->_ptr == node.getPtr ());
	}
	
	~JsonPointNode () {}
	
	cJSON* getPtr () const
	{
		return _ptr;
	}
	
	JsonNodeType getType () const
	{
		return _type;
	}
	
	String getLabel () const
	{
		return _label;
	}
	
private:
	JsonNodeType	_type;
	cJSON*			_ptr;
	String			_label;
};

class DTL_DLLEXPORT JsonTextWriter
{
public:
	JsonTextWriter ();
	virtual ~JsonTextWriter();
	
	void StartArray (const String &label = String::EMPTY);
	void EndArray ();
	
	void StartObject (const String &label = String::EMPTY,cJSON * jsonObject = NULL);
	void EndObject ();

	void WriteElement (const char *label, const String &value);
	void WriteElement (const char *label, const char* value);
	void WriteElement (const char *label, const int value);
	void WriteElement (const char *label, const unsigned int value);
	void WriteElement (const char *label, const int64 value);
	void WriteElement (const char *label, const short value);
	void WriteElement (const char *label, const unsigned short value);
	void WriteElement (const char *label, const bool value);
	void WriteNull (const char *label);
	
public:
	String getJsonStr (void);
	cJSON* getJsonObject(void);
	

private:
	void WriteString (const char *label, const String &value);
	
	template <class T>
	void WriteNumber (const char *label, const T value);
	
	
	void WriteBool (const char *label, const bool value);
	
private:
	String					_jsonStr;
	JsonPointNode			_root;
	JsonPointNode			_current;
	stack<JsonPointNode>	_jsonObjectStack;
	
	bool					_hasEnd;
};

#endif // _DTL_NET_JSONTEXTWRITER_H_
