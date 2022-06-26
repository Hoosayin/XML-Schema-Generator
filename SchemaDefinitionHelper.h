#pragma once
#include "pch.h"
#include "Element.h"
#include "Attribute.h"

class SchemaDefinitionHelper
{
	// Fields.
private:
	static CString _schema;

	// Methods.
public:
	static CString GenerateSchema(Element* element);
private:
	static void NewLine();
	static void AddTabSpaces(int numberOfSpaces);
	static void Write(CString string);
	static void WriteLine(CString string);
	static void AddElement(Element* element, int numberOfSpaces);
	static void AddAttribute(Attribute* attribute, int numberOfSpaces);
};

