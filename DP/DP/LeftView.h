// LeftView.h : CLeftView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__62372E26_2CFA_4020_90D3_7678F3E690E9__INCLUDED_)
#define AFX_LEFTVIEW_H__62372E26_2CFA_4020_90D3_7678F3E690E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVEDoc;

class CLeftView : public CScrollView
{
friend class CPad;
public:
	int i, j, k, sx, sy, ex, ey, width, height;
	CPoint pos;
	CRect rect;
	CRectTracker rt;
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// �A�g���r���[�g
public:
	CVEDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // �\�z��̍ŏ��̂P�x�����Ăяo����܂��B
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	int start_module;
	int line_mode;
	afx_msg void OnUpdateEditCopyCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	BOOL IsSelected();
	void DoCutCopyPaste(CArchive &ar, BOOL bCut);
	UINT m_nClipboardFormat;
	virtual ~CLeftView();
	afx_msg void OnProperties();	// CVEView����Ăяo�����߂ɓ��ʂ�public�ɂ��Ă���
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int before_am;
	CPoint client_point;

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	CToolTipCtrl m_toolTip;
	CString m_toolTip_text;
	void OnInsertCommon();
	//{{AFX_MSG(CLeftView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnInsert();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditDelete();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInsertM();
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTipsDispInfo(NMHDR* pNMHDR, LRESULT* pResult);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // LeftView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CVEDoc* CLeftView::GetDocument()
   { return (CVEDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LEFTVIEW_H__62372E26_2CFA_4020_90D3_7678F3E690E9__INCLUDED_)
