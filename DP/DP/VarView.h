#if !defined(AFX_VARVIEW_H__93FA34DC_2DAA_4D97_8A8F_7F735A98907D__INCLUDED_)
#define AFX_VARVIEW_H__93FA34DC_2DAA_4D97_8A8F_7F735A98907D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VarView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CVarView ビュー
class CVarView : public CListView
{
	friend class CLeftView;
protected:
	CVarView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CVarView)

// アトリビュート
public:
	CVEDoc* GetDocument();
	BOOL IsSelected();

// オペレーション

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CVarView)
public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CVarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
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

#ifndef _DEBUG  // VEView.cpp ファイルがデバッグ環境の時使用されます。
inline CVEDoc* CVarView::GetDocument()
   { return (CVEDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VARVIEW_H__93FA34DC_2DAA_4D97_8A8F_7F735A98907D__INCLUDED_)
