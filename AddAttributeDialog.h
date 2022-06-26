#pragma once
#include "pch.h"
#include "functional"
#include "Attribute.h"

using namespace std;

class AddAttributeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AddAttributeDialog)

public:
	AddAttributeDialog(CString elementName, CWnd* pParent = nullptr);
	virtual ~AddAttributeDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_ATTRIBUTE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CString AttributeName;
	CComboBox ComboAttributeType;
	CString DefaultOrFixedValue;
	CButton CheckButtonRequired;
	CButton RadioButtonFixedValue;
	CButton RadioButtonDefaultValue;
	CString ElementName;
	virtual BOOL OnInitDialog();
	void InitializeComponent();
	afx_msg void OnBnClickedButtonAddAttribute();
	afx_msg void OnBnClickedButtonCancelAttribute();
	CString AttributeType;
	BOOL IsRequired;
	afx_msg void OnCbnSelchangeComboAttributeType();
	function<void(Attribute*)> OnAddAttribute;

};
