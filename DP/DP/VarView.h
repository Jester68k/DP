#if !defined(AFX_VARVIEW_H__93FA34DC_2DAA_4D97_8A8F_7F735A98907D__INCLUDED_)
#define AFX_VARVIEW_H__93FA34DC_2DAA_4D97_8A8F_7F735A98907D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VarView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CVarView �r���[
class CVarView : public CListView
{
	friend class CLeftView;
protected:
	CVarView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CVarView)

// �A�g���r���[�g
public:
	CVEDoc* GetDocument();
	BOOL IsSelected();

// �I�y���[�V����

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CVarView)
public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CVarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
public:
	//{{AFX_MSG(CVarView)
	afx_msg void OnInsertVar();
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditDelete();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnVarProperty();
	afx_msg void OnUpdateVarProperty(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void OnVarPropertyCommon(int no);
	BOOL CheckVarName(CString str);
	void SetListItems();
};

#ifndef _DEBUG  // VEView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CVEDoc* CVarView::GetDocument()
   { return (CVEDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VARVIEW_H__93FA34DC_2DAA_4D97_8A8F_7F735A98907D__INCLUDED_)
