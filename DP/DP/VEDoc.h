// VEDoc.h : CVEDoc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEDOC_H__C831558E_A493_4917_B0AB_A09A040564BB__INCLUDED_)
#define AFX_VEDOC_H__C831558E_A493_4917_B0AB_A09A040564BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Padf.h"
#include "Module.h"

class CVEDoc : public CDocument
{
	friend class CClassView;
	friend class CLeftView;
	friend class CVarView;
	friend class CVEView;

protected:
	LONG ac, am, ap;	// active class(0 is global), active module, active PAD number
	CObList cls;
	CStdioFile f;
	CString path;
	CString title;
	CString compiler_path;
	int compiler_type;
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CVEDoc();
	DECLARE_DYNCREATE(CVEDoc)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

//�I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CVEDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CVEDoc();
protected:
	CPadf* GetPadf(CModule* pMdl, int pad);
	int GetNextPadfNum(CModule* pMdl, int p, int p_pos=0);
	void WriteLines(CModule* pMdl, int p, int indent);
	void WriteIndent(int tab);
	BOOL SaveSourceFile();
	void BuildApp(BOOL sw);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CVEDoc)
	afx_msg void OnSaveSourceFile();
	afx_msg void OnBuildBuild();
	afx_msg void OnBuildExec();
	afx_msg void OnToolOption();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VEDOC_H__C831558E_A493_4917_B0AB_A09A040564BB__INCLUDED_)
