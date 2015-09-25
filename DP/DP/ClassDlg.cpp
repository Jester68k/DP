// ClassDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ve.h"
#include "ClassDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassDlg ダイアログ


CClassDlg::CClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClassDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClassDlg)
	m_type = -1;
	m_name = _T("");
	m_baseclass = _T("");
	m_accesstype = -1;
	m_friendclass = _T("");
	m_numvar = 0;
	m_numfunc = 0;
	//}}AFX_DATA_INIT
}


void CClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassDlg)
	DDX_CBIndex(pDX, IDC_CLSTYPE, m_type);
	DDX_Text(pDX, IDC_CNAME, m_name);
	DDX_Text(pDX, IDC_BASECLASS, m_baseclass);
	DDX_CBIndex(pDX, IDC_ACCESSTYPE, m_accesstype);
	DDX_Text(pDX, IDC_FRIENDCLASS, m_friendclass);
	DDX_Text(pDX, IDC_CNUMVAR, m_numvar);
	DDX_Text(pDX, IDC_CNUMFUNC, m_numfunc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClassDlg, CDialog)
	//{{AFX_MSG_MAP(CClassDlg)
	ON_CBN_SELCHANGE(IDC_CLSTYPE, OnSelchangeClstype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassDlg メッセージ ハンドラ

void CClassDlg::OnSelchangeClstype() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	GetDlgItem(IDC_CNAME)->EnableWindow(((CComboBox*)GetDlgItem(IDC_CLSTYPE))->GetCurSel()!=CLSTYPE_GLOBAL);
	GetDlgItem(IDC_ACCESSTYPE)->EnableWindow(((CComboBox*)GetDlgItem(IDC_CLSTYPE))->GetCurSel()==CLSTYPE_CLASS);
	GetDlgItem(IDC_BASECLASS)->EnableWindow(((CComboBox*)GetDlgItem(IDC_CLSTYPE))->GetCurSel()==CLSTYPE_CLASS);
	GetDlgItem(IDC_FRIENDCLASS)->EnableWindow(((CComboBox*)GetDlgItem(IDC_CLSTYPE))->GetCurSel()==CLSTYPE_CLASS);
}

BOOL CClassDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	GetDlgItem(IDC_CNAME)->EnableWindow(((CComboBox*)GetDlgItem(IDC_CLSTYPE))->GetCurSel()!=CLSTYPE_GLOBAL);
	GetDlgItem(IDC_ACCESSTYPE)->EnableWindow(((CComboBox*)GetDlgItem(IDC_CLSTYPE))->GetCurSel()==CLSTYPE_CLASS);
	GetDlgItem(IDC_BASECLASS)->EnableWindow(((CComboBox*)GetDlgItem(IDC_CLSTYPE))->GetCurSel()==CLSTYPE_CLASS);
	GetDlgItem(IDC_FRIENDCLASS)->EnableWindow(((CComboBox*)GetDlgItem(IDC_CLSTYPE))->GetCurSel()==CLSTYPE_CLASS);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
