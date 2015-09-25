#if !defined(AFX_CLASSVIEW_H__9B7326ED_7103_4279_B3A0_7C558EFBA497__INCLUDED_)
#define AFX_CLASSVIEW_H__9B7326ED_7103_4279_B3A0_7C558EFBA497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CClassView �r���[

class CClassView : public CListView
{
	friend class CVEDoc;
protected:
	CClassView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CClassView)

// �A�g���r���[�g
public:
	CVEDoc* GetDocument();

// �I�y���[�V����
public:
	BOOL IsSelected();
	void DoCutCopyPaste(CArchive &ar, BOOL bCut);
	UINT m_nClipboardFormat;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CClassView)
public:
	virtual void OnInitialUpdate();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CClassView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	BOOL CheckClassName(CString str);
//	void OnInsertCls();
	void OnClsPropertyCommon(int index);
	void SetListItems();
	//{{AFX_MSG(CClassView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnInsertCls();
	afx_msg void OnClsProperty();
	afx_msg void OnUpdateClsProperty(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

#ifndef _DEBUG  // VEView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CVEDoc* CClassView::GetDocument()
   { return (CVEDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CLASSVIEW_H__9B7326ED_7103_4279_B3A0_7C558EFBA497__INCLUDED_)
