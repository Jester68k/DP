#if !defined(AFX_OPTIONDLG_H__47DD3680_9965_461B_93DC_352192779D1F__INCLUDED_)
#define AFX_OPTIONDLG_H__47DD3680_9965_461B_93DC_352192779D1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// COptionDlg ダイアログ

class COptionDlg : public CDialog
{
// コンストラクション
public:
	COptionDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(COptionDlg)
	enum { IDD = IDD_OPTION };
	CButton	m_path_browse;
	CString	m_compiler_path;
	int		m_compiler_type;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(COptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(COptionDlg)
	afx_msg void OnPathBrowse();
	afx_msg void OnSelchangeVcEnv();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_OPTIONDLG_H__47DD3680_9965_461B_93DC_352192779D1F__INCLUDED_)
