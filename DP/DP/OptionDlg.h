#if !defined(AFX_OPTIONDLG_H__47DD3680_9965_461B_93DC_352192779D1F__INCLUDED_)
#define AFX_OPTIONDLG_H__47DD3680_9965_461B_93DC_352192779D1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// COptionDlg �_�C�A���O

class COptionDlg : public CDialog
{
// �R���X�g���N�V����
public:
	COptionDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(COptionDlg)
	enum { IDD = IDD_OPTION };
	CButton	m_path_browse;
	CString	m_compiler_path;
	int		m_compiler_type;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(COptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(COptionDlg)
	afx_msg void OnPathBrowse();
	afx_msg void OnSelchangeVcEnv();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_OPTIONDLG_H__47DD3680_9965_461B_93DC_352192779D1F__INCLUDED_)
