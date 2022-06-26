#pragma once
#include "Element.h"

class MainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MainDialog)

public:
	MainDialog(CWnd* pParent = nullptr);
	virtual ~MainDialog();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

private:
	CString Schema;

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
public:
	Element* element;
	void InitializeComponent();
	afx_msg void OnBnClickedButtonAddElements();
	afx_msg void OnBnClickedButtonGenerateSchema();
	CString SchemaDefinition;
	afx_msg void OnBnClickedButtonSaveToFile();
};
