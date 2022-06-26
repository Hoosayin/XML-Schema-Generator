#pragma once
#include "functional"
#include "Element.h"

using namespace std;

class AddElementDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AddElementDialog)

public:
	AddElementDialog(CString parentElementName, CWnd* pParent = nullptr);
	virtual ~AddElementDialog();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_ELEMENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

private:
	Element* element;

	DECLARE_MESSAGE_MAP()
public:
	CString ElementName;
	int MinimumOccurance;
	int MaximumOccurance;
	afx_msg void OnBnClickedButtonAddAttribute();
	virtual BOOL OnInitDialog();
	void InitializeComponent();
	CComboBox ComboElementType;
	CString ElementType;
	afx_msg void OnCbnSelchangeComboElementType();
	void ToggleListBoxes(int value);
	void AddColumnsToListControls();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonCancel();
	CListCtrl ListElements;
	CListCtrl ListAttributes;
	afx_msg void OnBnClickedButtonAddElement();
	function<void(Element*)> OnElementAdded;
	CString ParentElementName;
};
