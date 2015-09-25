// OptionDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "VE.h"
#include "OptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionDlg ダイアログ


COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionDlg)
	m_compiler_path = _T("");
	m_compiler_type = -1;
	//}}AFX_DATA_INIT
}


void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionDlg)
	DDX_Control(pDX, IDC_PATH_BROWSE, m_path_browse);
	DDX_Text(pDX, IDC_PATH, m_compiler_path);
	DDX_CBIndex(pDX, IDC_VC_ENV, m_compiler_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	//{{AFX_MSG_MAP(COptionDlg)
	ON_BN_CLICKED(IDC_PATH_BROWSE, OnPathBrowse)
	ON_CBN_SELCHANGE(IDC_VC_ENV, OnSelchangeVcEnv)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionDlg メッセージ ハンドラ

void COptionDlg::OnPathBrowse() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CFileDialog fd(TRUE, _T("bat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("環境設定バッチファイル(*.bat)|*.bat|"));
	if(fd.DoModal()==IDOK) {
		GetDlgItem(IDC_PATH)->SetWindowText(fd.GetPathName());
	}
}

void COptionDlg::OnSelchangeVcEnv() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	GetDlgItem(IDC_PATH_BROWSE)->EnableWindow(((CComboBox*)GetDlgItem(IDC_VC_ENV))->GetCurSel()==COMPILER_VC_OTHER);
	GetDlgItem(IDC_PATH)->EnableWindow(((CComboBox*)GetDlgItem(IDC_VC_ENV))->GetCurSel()==COMPILER_VC_OTHER);
}

BOOL COptionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	GetDlgItem(IDC_PATH_BROWSE)->EnableWindow(((CComboBox*)GetDlgItem(IDC_VC_ENV))->GetCurSel()==COMPILER_VC_OTHER);
	GetDlgItem(IDC_PATH)->EnableWindow(((CComboBox*)GetDlgItem(IDC_VC_ENV))->GetCurSel()==COMPILER_VC_OTHER);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
