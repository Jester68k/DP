// ModulePropertyPage1.h : ヘッダー ファイル
//

#ifndef __MODULEPROPERTYPAGE1_H__
#define __MODULEPROPERTYPAGE1_H__

/////////////////////////////////////////////////////////////////////////////
// CModulePropertyPage1 ダイアログ

class CModulePropertyPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CModulePropertyPage1)

// 構築
public:
	CModulePropertyPage1();
	~CModulePropertyPage1();

// ダイアログ データ
	//{{AFX_DATA(CModulePropertyPage1)
	enum { IDD = IDD_MPROPPAGE1 };
	CString	m_mname;
	CString m_marg;
	int		m_mret_type;
	CString	m_mret_struct;
	int		m_mret_pointer;
	CString	m_mcomment;
	UINT	m_mnumpadfs;
	UINT	m_mnum_vars;
	BOOL	m_mrecursive;
	BOOL	m_minline;
	int		m_accesstype;
	int		m_mfunctype;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CModulePropertyPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// Implementation
protected:
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CModulePropertyPage1)
	afx_msg void OnSelchangeMretType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#endif // __MODULEPROPERTYPAGE1_H__
