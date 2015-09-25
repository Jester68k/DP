#if !defined(AFX_CLASSVIEW_H__9B7326ED_7103_4279_B3A0_7C558EFBA497__INCLUDED_)
#define AFX_CLASSVIEW_H__9B7326ED_7103_4279_B3A0_7C558EFBA497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CClassView ビュー

class CClassView : public CListView
{
	friend class CVEDoc;
protected:
	CClassView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CClassView)

// アトリビュート
public:
	CVEDoc* GetDocument();

// オペレーション
public:
	BOOL IsSelected();
	void DoCutCopyPaste(CArchive &ar, BOOL bCut);
	UINT m_nClipboardFormat;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CClassView)
public:
	virtual void OnInitialUpdate();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CClassView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
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

#ifndef _DEBUG  // VEView.cpp ファイルがデバッグ環境の時使用されます。
inline CVEDoc* CClassView::GetDocument()
   { return (CVEDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CLASSVIEW_H__9B7326ED_7103_4279_B3A0_7C558EFBA497__INCLUDED_)
