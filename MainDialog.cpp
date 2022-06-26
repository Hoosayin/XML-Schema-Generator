#include "pch.h"
#include "XML Schema Generator.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include "AddElementDialog.h"
#include "Element.h"
#include "SchemaDefinitionHelper.h"

IMPLEMENT_DYNAMIC(MainDialog, CDialogEx)

MainDialog::MainDialog(CWnd* pParent)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
	, SchemaDefinition(_T(""))
{
	element = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_XML);
}

MainDialog::~MainDialog()
{
}

void MainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, SchemaDefinition);
}


BEGIN_MESSAGE_MAP(MainDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD_ELEMENTS, &MainDialog::OnBnClickedButtonAddElements)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE_SCHEMA, &MainDialog::OnBnClickedButtonGenerateSchema)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TO_FILE, &MainDialog::OnBnClickedButtonSaveToFile)
END_MESSAGE_MAP()

BOOL MainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	InitializeComponent();

	return TRUE;
}

void MainDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR MainDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void MainDialog::InitializeComponent()
{
	element = NULL;
	SchemaDefinition = _T("");
	Schema = _T("");
}


void MainDialog::OnBnClickedButtonAddElements()
{
	AddElementDialog* dialog = new AddElementDialog(L"schema", this);

	dialog->OnElementAdded = [this](Element * element) -> void {
		this->element = element;
	};

	INT_PTR response = dialog->DoModal();

	if (response == IDOK)
	{
		// Do nothing.
	}
	else if (response == IDCANCEL)
	{
		// Do nothing.
	}
	else if (response == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
}


void MainDialog::OnBnClickedButtonGenerateSchema()
{
	Schema = SchemaDefinitionHelper::GenerateSchema(element);
	SchemaDefinition = Schema;
	UpdateData(FALSE);
}


void MainDialog::OnBnClickedButtonSaveToFile()
{
	CFile file;

	file.Open(_T("./Debug/Schema.xsd"), CFile::modeCreate + CFile::modeWrite);
	file.Write(Schema, Schema.GetAllocLength());
	file.Flush();

	AfxMessageBox(_T("Schema is saved in \"Schema.xsd\"."));
}
