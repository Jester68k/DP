#if !defined(AFX_CLASSDLG_H__A8647E31_A051_4EF9_8FE1_C97C96CD1571__INCLUDED_)
#define AFX_CLASSDLG_H__A8647E31_A051_4EF9_8FE1_C97C96CD1571__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CClassDlg �_�C�A���O

class CClassDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CClassDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CClassDlg)
	enum { IDD = IDD_CLS };
	int		m_type;
	CString	m_name;
	CString	m_baseclass;
	int		m_accesstype;
	CString	m_friendclass;
	UINT	m_numvar;
	UINT	m_numfunc;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CClassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CClassDlg)
	afx_msg void OnSelchangeClstype();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CLASSDLG_H__A8647E31_A051_4EF9_8FE1_C97C96CD1571__INCLUDED_)
