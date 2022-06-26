#include "pch.h"
#include "SchemaDefinitionHelper.h"

CString SchemaDefinitionHelper::_schema = _T("");

CString SchemaDefinitionHelper::GenerateSchema(Element* element)
{
	_schema = "";

	WriteLine(_T("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"));
	WriteLine(_T("<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\">"));

	AddElement(element, 1);

	WriteLine(_T("</xs:schema>"));

	return _schema;
}

void SchemaDefinitionHelper::NewLine()
{
	_schema += _T("\r\n");
}

void SchemaDefinitionHelper::AddTabSpaces(int numberOfSpaces)
{
	for (int i = 0; i < numberOfSpaces; i++)
		_schema += _T("\t");
}

void SchemaDefinitionHelper::Write(CString string)
{
	_schema += string;
}

void SchemaDefinitionHelper::WriteLine(CString string)
{
	_schema += string;
	NewLine();
}

void SchemaDefinitionHelper::AddElement(Element* element, int numberOfSpaces)
{
	if (element == NULL)
		return;

	if (element->Type == DATATYPE_NONE)
	{
		CString elementString;
		CString name;
		CString minOccurs;
		CString maxOccurs;

		name.Format(_T(" name=\"%s\""), element->Name);

		if (element->MinimumOccurance < 0)
			minOccurs = _T(" minOccurs=\"unbounded\"");
		else if (element->MinimumOccurance == 1)
			minOccurs = _T("");
		else
			minOccurs.Format(_T(" minOccurs=\"%d\""), element->MinimumOccurance);

		if (element->MaximumOccurance < 0)
			maxOccurs = _T(" maxOccurs=\"unbounded\"");
		else if (element->MaximumOccurance == 1)
			maxOccurs = _T("");
		else
			maxOccurs.Format(_T(" maxOccurs=\"%d\""), element->MaximumOccurance);

		elementString.Format(_T("<xs:element%s%s%s>"), name, minOccurs, maxOccurs);

		AddTabSpaces(numberOfSpaces);
		WriteLine(elementString);

		AddTabSpaces(numberOfSpaces + 1);
		WriteLine(_T("<xs:complexType>"));

		if (element->Elements->GetCount() > 0)
		{
			AddTabSpaces(numberOfSpaces + 2);
			WriteLine(_T("<xs:sequence>"));

			POSITION position = element->Elements->GetHeadPosition();

			while (position != NULL)
			{
				Element* child = element->Elements->GetNext(position);
				AddElement(child, numberOfSpaces + 3);
			}

			AddTabSpaces(numberOfSpaces + 2);
			WriteLine(_T("</xs:sequence>"));
		}

		if (element->Attributes->GetCount() > 0)
		{
			POSITION position = element->Attributes->GetHeadPosition();

			while (position != NULL)
			{
				Attribute* attribute = element->Attributes->GetNext(position);
				AddAttribute(attribute, numberOfSpaces + 2);
			}

		}

		AddTabSpaces(numberOfSpaces + 1);
		WriteLine(_T("</xs:complexType>"));

		AddTabSpaces(numberOfSpaces);
		WriteLine(_T("</xs:element>"));
	}
	else
	{
		CString elementString;
		CString name;
		CString type;
		CString minOccurs;
		CString maxOccurs;

		name.Format(_T(" name=\"%s\""), element->Name);
		type.Format(_T(" type=\"xs:%s\""), element->Type);
		
		if (element->MinimumOccurance < 0)
			minOccurs = _T(" minOccurs=\"unbounded\"");
		else if (element->MinimumOccurance == 1)
			minOccurs = _T("");
		else
			minOccurs.Format(_T(" minOccurs=\"%d\""), element->MinimumOccurance);

		if (element->MaximumOccurance < 0)
			maxOccurs = _T(" maxOccurs=\"unbounded\"");
		else if (element->MaximumOccurance == 1)
			maxOccurs = _T("");
		else
			maxOccurs.Format(_T(" maxOccurs=\"%d\" "), element->MaximumOccurance);

		elementString.Format(_T("<xs:element%s%s%s%s />"), name, type, minOccurs, maxOccurs);

		AddTabSpaces(numberOfSpaces);
		WriteLine(elementString);
	}
}

void SchemaDefinitionHelper::AddAttribute(Attribute* attribute, int numberOfSpaces)
{
	CString attributeString;
	CString name;
	CString type;
	CString defaultOrFixed;
	CString use;

	name.Format(_T(" name=\"%s\""), attribute->Name);
	type.Format(_T(" type=\"xs:%s\""), attribute->Type);

	if (attribute->DefaultOrFixedValue != _T(""))
		attribute->IsDefault ?
			defaultOrFixed.Format(_T(" default=\"%s\""), attribute->DefaultOrFixedValue) :
			defaultOrFixed.Format(_T(" fixed=\"%s\""), attribute->DefaultOrFixedValue);
	else
		defaultOrFixed = _T("");

	use = attribute->IsRequired ? _T(" use=\"required\"") : _T("");
	attributeString.Format(_T("<xs:attribute%s%s%s%s />"), name, type, defaultOrFixed, use);

	AddTabSpaces(numberOfSpaces);
	WriteLine(attributeString);
}
