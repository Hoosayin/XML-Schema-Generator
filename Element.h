#pragma once
#include "pch.h"
#include "Attribute.h"

class Element
{
	// Fields.
public:
	CString Name;
	CString Type;
	int MinimumOccurance;
	int MaximumOccurance;
	CList<Attribute*>* Attributes;
	CList<Element*>* Elements;

	// Methods.
public:
	Element();
};

