// ModulePropertyPage1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "resource.h"
#include "VE.h"
#include "ModulePropertyPage1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CModulePropertyPage1, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CModulePropertyPage1 プロパティ ページ

CModulePropertyPage1::CModulePropertyPage1() : CPropertyPage(CModulePropertyPage1::IDD)
{
	//{{AFX_DATA_INIT(CModulePropertyPage1)
	m_mname = _T("");
	m_marg = _T("");
	m_mret_type = -1;
	m_mret_struct = _T("");
	m_mret_pointer = -1;
	m_mcomment = _T("");
	m_mnumpadfs = 0;
	m_mnum_vars = 0;
	m_mrecursive = FALSE;
	m_minline = FALSE;
	m_accesstype = -1;
	m_mfunctype = -1;
	//}}AFX_DATA_INIT
}

CModulePropertyPage1::~CModulePropertyPage1()
{
}

void CModulePropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModulePropertyPage1)
	DDX_Text(pDX, IDC_MNAME, m_mname);
	DDV_MaxChars(pDX, m_mname, 256);
	DDX_Text(pDX, IDC_MARG, m_marg);
	DDV_MaxChars(pDX, m_marg, 256);
	DDX_CBIndex(pDX, IDC_MRET_TYPE, m_mret_type);
	DDX_Text(pDX, IDC_MRET_STRUCT, m_mret_struct);
	DDX_CBIndex(pDX, IDC_MRET_POINTER, m_mret_pointer);
	DDX_Text(pDX, IDC_MCOMMENT, m_mcomment);
	DDX_Text(pDX, IDC_MNUMPADFS, m_mnumpadfs);
	DDV_MinMaxUInt(pDX, m_mnumpadfs, 0, 65535);
	DDX_Text(pDX, IDC_MNUM_VARS, m_mnum_vars);
	DDV_MinMaxUInt(pDX, m_mnum_vars, 0, 65535);
	DDX_Check(pDX, IDC_MRECURSIVE, m_mrecursive);
	DDX_Check(pDX, IDC_MINLINE, m_minline);
	DDX_CBIndex(pDX, IDC_MACCESSTYPE, m_accesstype);
	DDX_CBIndex(pDX, IDC_MFUNCTYPE, m_mfunctype);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CModulePropertyPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CModulePropertyPage1)
	ON_CBN_SELCHANGE(IDC_MRET_TYPE, OnSelchangeMretType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CModulePropertyPage1::OnSelchangeMretType() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	GetDlgItem(IDC_MRET_STRUCT)->EnableWindow(((CComboBox*)GetDlgItem(IDC_MRET_TYPE))->GetCurSel()>=TYPE_STRUCT);
}

BOOL CModulePropertyPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	GetDlgItem(IDC_MACCESSTYPE)->EnableWindow(clsaccesstype_flag);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

