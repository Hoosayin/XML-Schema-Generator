#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"

class CXMLSchemaGeneratorApp : public CWinApp
{
public:
	CXMLSchemaGeneratorApp();

public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CXMLSchemaGeneratorApp theApp;
