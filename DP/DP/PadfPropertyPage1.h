// PadfPropertyPage1.h : ヘッダー ファイル
//

#ifndef __PADPROPERTYPAGE1_H__
#define __PADPROPERTYPAGE1_H__

/////////////////////////////////////////////////////////////////////////////
// CPadfPropertyPage1 ダイアログ

class CPadfPropertyPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPadfPropertyPage1)

// 構築
public:
	CPadfPropertyPage1();
	~CPadfPropertyPage1();

// ダイアログ データ
	//{{AFX_DATA(CPadfPropertyPage1)
	enum { IDD = IDD_PPROPPAGE1 };
	CEdit	m_case;
	int		m_type;
	CString	m_str;
	CString	m_comment;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPadfPropertyPage1)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	virtual LONG OnSetPageFocus(UINT,LONG);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// Implementation
protected:
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CPadfPropertyPage1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __PADPROPERTYPAGE1_H__
