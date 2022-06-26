#include "pch.h"
#include "XML Schema Generator.h"
#include "AddAttributeDialog.h"
#include "afxdialogex.h"
#include "DataTypes.h"
#include "Attribute.h"

IMPLEMENT_DYNAMIC(AddAttributeDialog, CDialogEx)

AddAttributeDialog::AddAttributeDialog(CString elementName, CWnd* pParent)
	: CDialogEx(IDD_ADD_ATTRIBUTE_DIALOG, pParent)
	, AttributeName(_T(""))
	, DefaultOrFixedValue(_T(""))
	, ElementName(_T(""))
	, AttributeType(_T(""))
	, IsRequired(FALSE)
{
	ElementName = elementName;
	ElementName.Format(L"<%s>", ElementName);
}

AddAttributeDialog::~AddAttributeDialog()
{
}

void AddAttributeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ATTRIBUTE_NAME, AttributeName);
	DDX_Control(pDX, IDC_COMBO_ATTRIBUTE_TYPE, ComboAttributeType);
	DDX_Text(pDX, IDC_EDIT_DEFAULT_OF_FIXED_VALUE, DefaultOrFixedValue);
	DDX_Control(pDX, IDC_CHECK_IS_REQUIRED, CheckButtonRequired);
	DDX_Control(pDX, IDC_RADIO_FIXED_VALUE, RadioButtonFixedValue);
	DDX_Control(pDX, IDC_RADIO_DEFAULT_VALUE, RadioButtonDefaultValue);
	DDX_Text(pDX, IDC_STATIC_ATTRIBUTES_ELEMENT_NAME, ElementName);
	DDX_Check(pDX, IDC_CHECK_IS_REQUIRED, IsRequired);
}

BEGIN_MESSAGE_MAP(AddAttributeDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ATTRIBUTE, &AddAttributeDialog::OnBnClickedButtonAddAttribute)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_ATTRIBUTE, &AddAttributeDialog::OnBnClickedButtonCancelAttribute)
	ON_CBN_SELCHANGE(IDC_COMBO_ATTRIBUTE_TYPE, &AddAttributeDialog::OnCbnSelchangeComboAttributeType)
END_MESSAGE_MAP()

BOOL AddAttributeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitializeComponent();
	return TRUE;
}

void AddAttributeDialog::InitializeComponent()
{
	int length = DataTypes::Length();
	length--;

	for (int i = 0; i < length; i++)
		ComboAttributeType.AddString(DataTypes::Types[i]);

	ComboAttributeType.SetCurSel(0);
	AttributeType = DataTypes::Types[0];
	RadioButtonDefaultValue.SetCheck(TRUE);
	IsRequired = TRUE;

	UpdateData(FALSE);
}


void AddAttributeDialog::OnBnClickedButtonAddAttribute()
{
	UpdateData(TRUE);

	Attribute* attribute = new Attribute();
	attribute->Name = AttributeName;
	attribute->Type = AttributeType;
	attribute->DefaultOrFixedValue = DefaultOrFixedValue;
	attribute->IsDefault = RadioButtonDefaultValue.GetCheck();
	attribute->IsRequired = CheckButtonRequired.GetCheck();

	if (OnAddAttribute)
		OnAddAttribute(attribute);

	OnOK();
}


void AddAttributeDialog::OnBnClickedButtonCancelAttribute()
{
	OnCancel();
}

void AddAttributeDialog::OnCbnSelchangeComboAttributeType()
{
	int selectedIndex = ComboAttributeType.GetCurSel();
	
	if (selectedIndex != LB_ERR)
		ComboAttributeType.GetLBText(selectedIndex, AttributeType);
}
