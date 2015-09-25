// VarDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "VE.h"
#include "VarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVarDlg ダイアログ


CVarDlg::CVarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVarDlg)
	m_kind = -1;
	m_comment = _T("");
	m_name = _T("");
	m_scope = -1;
	m_start = _T("");
	m_type = -1;
	m_pointer = -1;
	m_struct = _T("");
	m_accesstype = -1;
	//}}AFX_DATA_INIT
}


void CVarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVarDlg)
	DDX_CBIndex(pDX, IDC_KIND, m_kind);
	DDX_Text(pDX, IDC_COMMENT, m_comment);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_CBIndex(pDX, IDC_SCOPE, m_scope);
	DDX_Text(pDX, IDC_START, m_start);
	DDX_CBIndex(pDX, IDC_TYPE, m_type);
	DDX_CBIndex(pDX, IDC_POINTER, m_pointer);
	DDX_Text(pDX, IDC_STRUCT, m_struct);
	DDX_CBIndex(pDX, IDC_ACCESSTYPE, m_accesstype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVarDlg, CDialog)
	//{{AFX_MSG_MAP(CVarDlg)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVarDlg メッセージ ハンドラ

void CVarDlg::OnSelchangeType() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	GetDlgItem(IDC_STRUCT)->EnableWindow(((CComboBox*)GetDlgItem(IDC_TYPE))->GetCurSel()>=TYPE_STRUCT);
}

BOOL CVarDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	GetDlgItem(IDC_STRUCT)->EnableWindow(((CComboBox*)GetDlgItem(IDC_TYPE))->GetCurSel()>=TYPE_STRUCT);
	GetDlgItem(IDC_ACCESSTYPE)->EnableWindow(access_flag);
	GetDlgItem(IDC_TYPE)->SetFocus();
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
