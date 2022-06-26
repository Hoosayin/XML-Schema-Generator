#include "pch.h"
#include "XML Schema Generator.h"
#include "AddElementDialog.h"
#include "afxdialogex.h"
#include "DataTypes.h"
#include "AddAttributeDialog.h"

IMPLEMENT_DYNAMIC(AddElementDialog, CDialogEx)

AddElementDialog::AddElementDialog(CString parentElementName, CWnd* pParent)
	: CDialogEx(IDD_ADD_ELEMENT_DIALOG, pParent)
	, ElementName(_T(""))
	, MinimumOccurance(0)
	, MaximumOccurance(0)
	, ParentElementName(_T(""))
{
	ParentElementName = parentElementName;
	ParentElementName.Format(L"<%s>", ParentElementName);
}

AddElementDialog::~AddElementDialog()
{
}

void AddElementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ELEMENT_NAME, ElementName);
	DDX_Text(pDX, IDC_EDIT_MINIMUM_OCCURANCE, MinimumOccurance);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_OCCURANC, MaximumOccurance);
	DDX_Control(pDX, IDC_COMBO_ELEMENT_TYPE, ComboElementType);
	DDX_Control(pDX, IDC_LIST_ELEMENTS, ListElements);
	DDX_Control(pDX, IDC_LIST_ATTRIBUTES, ListAttributes);
	DDX_Text(pDX, IDC_STATIC_PARENT_ELEMENT_NAME, ParentElementName);
}


BEGIN_MESSAGE_MAP(AddElementDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ATTRIBUTE, &AddElementDialog::OnBnClickedButtonAddAttribute)
	ON_CBN_SELCHANGE(IDC_COMBO_ELEMENT_TYPE, &AddElementDialog::OnCbnSelchangeComboElementType)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &AddElementDialog::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &AddElementDialog::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ELEMENT, &AddElementDialog::OnBnClickedButtonAddElement)
END_MESSAGE_MAP()

void AddElementDialog::OnBnClickedButtonAddAttribute()
{
	UpdateData(TRUE);

	AddAttributeDialog* dialog = new AddAttributeDialog(ElementName, this);
	dialog->OnAddAttribute = [this](Attribute* attribute) -> void {
		this->element->Attributes->AddTail(attribute);

		int nIndex = ListAttributes.InsertItem(0, attribute->Name);
		ListAttributes.SetItemText(nIndex, 1, attribute->Type);
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


BOOL AddElementDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitializeComponent();

	return TRUE;
}

void AddElementDialog::InitializeComponent()
{
	int length = DataTypes::Length();

	for (int i = 0; i < DataTypes::Length(); i++)
		ComboElementType.AddString(DataTypes::Types[i]);

	ComboElementType.SetCurSel(0);
	ElementType = DataTypes::Types[0];

	ElementName = L"NoName";
	MinimumOccurance = 1;
	MaximumOccurance = 1;

	ToggleListBoxes(FALSE);
	AddColumnsToListControls();
	element = new Element();
	element->Attributes = new CList<Attribute*>();
	element->Elements = new CList<Element*>();

	UpdateData(FALSE);
}


void AddElementDialog::OnCbnSelchangeComboElementType()
{
	int selectedIndex = ComboElementType.GetCurSel();

	if (selectedIndex != LB_ERR)
		ComboElementType.GetLBText(selectedIndex, ElementType);

	if (ElementType == DATATYPE_NONE)
		ToggleListBoxes(TRUE);
	else
		ToggleListBoxes(FALSE);
}

void AddElementDialog::ToggleListBoxes(int value)
{
	(CButton*)GetDlgItem(IDC_BUTTON_ADD_ELEMENT)->EnableWindow(value);
	(CButton*)GetDlgItem(IDC_BUTTON_ADD_ATTRIBUTE)->EnableWindow(value);
	ListElements.EnableWindow(value);
	ListAttributes.EnableWindow(value);
}

void AddElementDialog::AddColumnsToListControls()
{
	ListElements.InsertColumn(0, L"ELEMENT", LVCFMT_LEFT, 100);
	ListElements.InsertColumn(1, L"TYPE", LVCFMT_LEFT, 100);

	ListAttributes.InsertColumn(0, L"ATTRIBUTE", LVCFMT_LEFT, 100);
	ListAttributes.InsertColumn(1, L"TYPE", LVCFMT_LEFT, 100);
}

void AddElementDialog::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);

	element->Name = ElementName;
	element->Type = ElementType;
	element->MinimumOccurance = MinimumOccurance;
	element->MaximumOccurance = MaximumOccurance;

	if (ElementType != DATATYPE_NONE)
	{
		element->Elements = new CList<Element*>();
		element->Attributes = new CList<Attribute*>();
	}

	if (OnElementAdded)
		OnElementAdded(element);

	OnOK();
}


void AddElementDialog::OnBnClickedButtonCancel()
{
	OnCancel();
}


void AddElementDialog::OnBnClickedButtonAddElement()
{
	UpdateData(TRUE);

	AddElementDialog* dialog = new AddElementDialog(ElementName, this);

	dialog->OnElementAdded = [this](Element* element) -> void {
		this->element->Elements->AddTail(element);

		int nIndex = ListElements.InsertItem(0, element->Name);
		ListElements.SetItemText(nIndex, 1, element->Type);
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
