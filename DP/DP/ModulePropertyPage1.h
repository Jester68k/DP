// ModulePropertyPage1.h : �w�b�_�[ �t�@�C��
//

#ifndef __MODULEPROPERTYPAGE1_H__
#define __MODULEPROPERTYPAGE1_H__

/////////////////////////////////////////////////////////////////////////////
// CModulePropertyPage1 �_�C�A���O

class CModulePropertyPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CModulePropertyPage1)

// �\�z
public:
	CModulePropertyPage1();
	~CModulePropertyPage1();

// �_�C�A���O �f�[�^
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


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CModulePropertyPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// Implementation
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CModulePropertyPage1)
	afx_msg void OnSelchangeMretType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#endif // __MODULEPROPERTYPAGE1_H__
