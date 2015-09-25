// PadPropertyPage1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "VE.h"
#include "resource.h"
#include "PadfPropertyPage1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CPadfPropertyPage1, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CPadfPropertyPage1 プロパティ ページ

CPadfPropertyPage1::CPadfPropertyPage1() : CPropertyPage(CPadfPropertyPage1::IDD)
{
	//{{AFX_DATA_INIT(CPadfPropertyPage1)
	m_type = 0;
	m_str = _T("");
	m_comment = _T("");
	//}}AFX_DATA_INIT
}

CPadfPropertyPage1::~CPadfPropertyPage1()
{
}

void CPadfPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPadfPropertyPage1)
	DDX_Control(pDX, IDC_CASE, m_case);
	DDX_Radio(pDX, IDC_PADTYPE0, m_type);
	DDX_Text(pDX, IDC_PADSTR, m_str);
	DDV_MaxChars(pDX, m_str, 256);
	DDX_Text(pDX, IDC_PADCOMMENT, m_comment);
	DDV_MaxChars(pDX, m_comment, 256);
	//}}AFX_DATA_MAP
}

#define WM_SETPAGEFOCUS WM_APP+2

BEGIN_MESSAGE_MAP(CPadfPropertyPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CPadfPropertyPage1)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_SETPAGEFOCUS, OnSetPageFocus)
END_MESSAGE_MAP()

BOOL CPadfPropertyPage1::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL fRet = CPropertyPage::OnSetActive();
	m_case.EnableWindow(case_flag);	// TRUE or FALSE
	m_case.SetWindowText(case_str);	// case string of switch
	if(1==padf_page_mode)
		PostMessage(WM_SETPAGEFOCUS, 0, 0L);

	return CPropertyPage::OnSetActive();
}

void CPadfPropertyPage1::OnOK() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	m_case.GetWindowText(case_str);
	CPropertyPage::OnOK();
}

LONG CPadfPropertyPage1::OnSetPageFocus(UINT wParam, LONG lParam)
{
  // IDC_BUTTON2 is the button on this property page
  // that you want to give the default focus.

  CEdit* pEdit = (CEdit*)GetDlgItem(IDC_PADSTR);
  ASSERT(pEdit);
  pEdit->SetFocus();
  return 0;
}
