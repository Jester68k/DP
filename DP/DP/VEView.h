// VEView.h : CVEView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEVIEW_H__22BD401E_0FAB_43EC_A3D5_8BB9C5291AAF__INCLUDED_)
#define AFX_VEVIEW_H__22BD401E_0FAB_43EC_A3D5_8BB9C5291AAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVEView : public CScrollView
{
protected:
	CPoint pos;
	CToolTipCtrl m_toolTip;
	CString m_toolTip_text;
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CVEView();
	DECLARE_DYNCREATE(CVEView)

// �A�g���r���[�g
public:
	CVEDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CVEView)
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnInitialUpdate(); // �\�z��̍ŏ��̂P�x�����Ăяo����܂��B
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	int before_ap;
	int prev_p, prev_p_pos, next_p;
	CRectTracker rt;
	int sx, sy, ex, ey;
	int width, height;

	afx_msg void OnUpdateEditCopyCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	BOOL IsSelected();
	void DoCutCopyPaste(CArchive &ar, BOOL bCut);
	UINT m_nClipboardFormat;
	virtual ~CVEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL CheckString(CString& str);
	int SkipSpace(CString& str, int i, int len);
	void Adjust(CModule* pMdl, int pad);

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	void MoveUnderPadf(int padf_num, int move_x, int move_y);
	void LClick(UINT nFlags,CPoint point);
	void InsertPadf(int type1, int type2, int mode);
	void InsertPadf2(int type1, int type2, int mode);
	//{{AFX_MSG(CVEView)
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnPadproperty();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnInsertPadf();
	afx_msg void OnEditDelete();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateInsertPadf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditPasteP();
	afx_msg void OnInsertProcess();
	afx_msg void OnInsertIf();
	afx_msg void OnInsertSwitch();
	afx_msg void OnInsertFor();
	afx_msg void OnInsertWhile();
	afx_msg void OnInsertDoWhile();
	afx_msg void OnUpdatePadproperty(CCmdUI* pCmdUI);
	afx_msg void OnInsertComment();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTipsDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewAdjust();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // VEView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CVEDoc* CVEView::GetDocument()
   { return (CVEDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VEVIEW_H__22BD401E_0FAB_43EC_A3D5_8BB9C5291AAF__INCLUDED_)
