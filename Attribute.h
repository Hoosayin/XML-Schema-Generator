#pragma once
#include "pch.h"

class Attribute
{
	// Fields
public:
	CString Name;
	CString Type;
	CString DefaultOrFixedValue;
	bool IsDefault;
	bool IsRequired;
};