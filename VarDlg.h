#if !defined(AFX_VARDLG_H__A80A5AC2_A985_41C1_B75A_25510121684B__INCLUDED_)
#define AFX_VARDLG_H__A80A5AC2_A985_41C1_B75A_25510121684B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VarDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CVarDlg �_�C�A���O

class CVarDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CVarDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
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


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CVarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CVarDlg)
	afx_msg void OnSelchangeType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VARDLG_H__A80A5AC2_A985_41C1_B75A_25510121684B__INCLUDED_)
