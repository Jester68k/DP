// PadfPropertyPage1.h : �w�b�_�[ �t�@�C��
//

#ifndef __PADPROPERTYPAGE1_H__
#define __PADPROPERTYPAGE1_H__

/////////////////////////////////////////////////////////////////////////////
// CPadfPropertyPage1 �_�C�A���O

class CPadfPropertyPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPadfPropertyPage1)

// �\�z
public:
	CPadfPropertyPage1();
	~CPadfPropertyPage1();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPadfPropertyPage1)
	enum { IDD = IDD_PPROPPAGE1 };
	CEdit	m_case;
	int		m_type;
	CString	m_str;
	CString	m_comment;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPadfPropertyPage1)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	virtual LONG OnSetPageFocus(UINT,LONG);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// Implementation
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPadfPropertyPage1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __PADPROPERTYPAGE1_H__
