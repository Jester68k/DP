#if !defined(AFX_VARDLG_H__A80A5AC2_A985_41C1_B75A_25510121684B__INCLUDED_)
#define AFX_VARDLG_H__A80A5AC2_A985_41C1_B75A_25510121684B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VarDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CVarDlg ダイアログ

class CVarDlg : public CDialog
{
// コンストラクション
public:
	CVarDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CVarDlg)
	enum { IDD = IDD_VAR };
	int		m_kind;
	CString	m_comment;
	CString	m_name;
	int		m_scope;
	CString	m_start;
	int		m_type;
	int		m_pointer;
	CString	m_struct;
	int		m_accesstype;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CVarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CVarDlg)
	afx_msg void OnSelchangeType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VARDLG_H__A80A5AC2_A985_41C1_B75A_25510121684B__INCLUDED_)
