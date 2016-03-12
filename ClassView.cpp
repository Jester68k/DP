// ClassView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "VE.h"
#include "VEDoc.h"
#include "Class.h"
#include "ClassDlg.h"
#include "ClassView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassView

IMPLEMENT_DYNCREATE(CClassView, CListView)

CClassView::CClassView()
{
	// CG: この行はクリップボード アシスタント コンポーネントによって追加されました
	m_nClipboardFormat = ::RegisterClipboardFormat(_T("CLS"));
}

CClassView::~CClassView()
{
}


BEGIN_MESSAGE_MAP(CClassView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CClassView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_INSERT_CLS, OnInsertCls)
	ON_COMMAND(ID_CLS_PROPERTY, OnClsProperty)
	ON_UPDATE_COMMAND_UI(ID_CLS_PROPERTY, OnUpdateClsProperty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView 描画

void CClassView::OnDraw(CDC* pDC)
{
	// TODO: この位置に描画用のコードを追加してください
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClassView::SetListItems();
}


/////////////////////////////////////////////////////////////////////////////
// CClassView 診断

#ifdef _DEBUG
void CClassView::AssertValid() const
{
	CListView::AssertValid();
}

void CClassView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CVEDoc* CClassView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVEDoc)));
	return (CVEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClassView メッセージ ハンドラ
BOOL CClassView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_SINGLESEL ;
	return CListView::PreCreateWindow(cs);
}

void CClassView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CListCtrl&	listCtrl = GetListCtrl();
	LVCOLUMN lvcol;
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	lvcol.iSubItem = 0;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvcol.pszText = "種類";
	lvcol.cx = 60;
	listCtrl.InsertColumn(0, &lvcol);

	lvcol.iSubItem = 1;
	lvcol.pszText = "名前";
	lvcol.cx = 140;
	listCtrl.InsertColumn(1, &lvcol);

	CClassView::SetListItems();
}

void CClassView::SetListItems()
{
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl&	listCtrl = GetListCtrl();
	LVITEM	lvi;
	int index=0;
	POSITION m_pos;
	CClass* pCls;
	CString str;

	listCtrl.DeleteAllItems();
	lvi.mask = LVIF_TEXT;

	m_pos=pDoc->cls.GetHeadPosition();
	while(m_pos) {
		pCls = (CClass*)pDoc->cls.GetNext(m_pos);
		lvi.iItem= index;
		lvi.iSubItem = 0;
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(clstype_tbl[pCls->type]));
		index = listCtrl.InsertItem( &lvi );
		lvi.iItem = index;
		lvi.iSubItem = 1;
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pCls->name));
		listCtrl.SetItem(&lvi);
		index++;
	}
	listCtrl.SetHoverTime(1);
}

void CClassView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	CClassDlg clsdlg;
	int index;
	index = listCtrl.HitTest(point);

	if(index>-1) {
		if (index < pDoc->cls.GetCount()) {
			pDoc->ac=index;
			InvalidateRect(NULL,FALSE);
			pDoc->UpdateAllViews(NULL);
		}
	} else {
		CClassView::OnInsertCls();
	}
	CListView::OnLButtonDown(nFlags, point);
}

void CClassView::OnClsPropertyCommon(int index)
{
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClassDlg clsdlg;
	CClass* pCls;

	if(index >= 0 && index<pDoc->cls.GetCount()) {
		pCls = (CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(index));
		clsdlg.m_type = pCls->type;
		clsdlg.m_name = pCls->name;
		clsdlg.m_accesstype = pCls->acctype;
		clsdlg.m_baseclass = pCls->basecls;
		clsdlg.m_friendclass = pCls->friendcls;
		clsdlg.m_numvar = pCls->var.GetCount();
		clsdlg.m_numfunc = pCls->mdl.GetCount();
		if(clsdlg.DoModal()==IDOK) {
			if(0==index) {
				clsdlg.m_type = CLSTYPE_GLOBAL;
				clsdlg.m_name = "";
			} else 
				if(CheckClassName(clsdlg.m_name))
					return;
			pCls->SetValue(clsdlg.m_type, clsdlg.m_name, clsdlg.m_accesstype, clsdlg.m_baseclass, clsdlg.m_friendclass);
			pDoc->SetModifiedFlag();
			CClassView::SetListItems();
			InvalidateRect(NULL,FALSE);
			pDoc->UpdateAllViews(NULL);
		}
	}
}

void CClassView::OnInsertCls()
{
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl&	listCtrl = GetListCtrl();
	CClassDlg clsdlg;
	CClass *pCls, *pSearchCls;
	int num;

	clsdlg.m_type = CLSTYPE_CLASS;
	clsdlg.m_name = "";
	clsdlg.m_accesstype = AT_PUBLIC;
	clsdlg.m_baseclass = "";
	clsdlg.m_friendclass = "";
	if(IDOK==clsdlg.DoModal() && !CheckClassName(clsdlg.m_name)) {
		if(CLSTYPE_GLOBAL == clsdlg.m_type) {
			AfxMessageBox("グローバルは１つだけです。",MB_OK);
			return;
		}
		for(num=0; num<pDoc->cls.GetCount(); num++) {
			pSearchCls=(CClass*)(pDoc->cls.GetAt(pDoc->cls.FindIndex(num)));
			if(clsdlg.m_type == pSearchCls->type && clsdlg.m_name == pSearchCls->name) {// 同じ種類と名前ならreturn
				AfxMessageBox("同じ種類で同じ名前のものがあります。",MB_OK);
				return;
			}
		}
		pCls = new CClass();
		pCls->SetValue(clsdlg.m_type, clsdlg.m_name, clsdlg.m_accesstype, clsdlg.m_baseclass, clsdlg.m_friendclass);
		pDoc->am = -1;
		pDoc->pAPadf = NULL;
		for(num=0; num<pDoc->cls.GetCount(); num++) {
			pSearchCls=(CClass*)(pDoc->cls.GetAt(pDoc->cls.FindIndex(num)));
			if(clsdlg.m_type < pSearchCls->type) {
				pDoc->cls.InsertBefore(pDoc->cls.FindIndex(num), (CObject*)pCls);	// クラスが挿入されカウントが１つ増える
				pDoc->ac = num;
				goto jump;
			}
		}
		pDoc->ac = pDoc->cls.GetCount();
		pDoc->cls.AddTail((CObject*)pCls);	// クラスが末尾に追加されカウントが１つ増える
		jump:
		pDoc->SetModifiedFlag();
		CClassView::SetListItems();
		InvalidateRect(NULL,FALSE);
		pDoc->UpdateAllViews(NULL);
	}
}

BOOL CClassView::CheckClassName(CString str)
{
	BOOL array_cnt=0;

	if(str.GetLength()==0) {
//		AfxMessageBox("名前が入力されていません。",MB_OK);
		MessageBeep(MB_OK);
		return TRUE;
	}
	if(isdigit(str[0])) {
		AfxMessageBox("名前の先頭に数字は使えません。",MB_OK);
		return TRUE;
	}
	for(int i=0; i<str.GetLength(); i++) {
		if(!(isalnum(str[i]) || str[i]=='_')) {
			AfxMessageBox("英数字か'_'（アンダースコア）である必要があります。",MB_OK);
			return TRUE;
		}
	}
	return FALSE;
}

void CClassView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl&	listCtrl = GetListCtrl();
	CClassDlg clsdlg;
	int index;

	index = listCtrl.HitTest(point);
	if (index >= 0 && index < pDoc->cls.GetCount())
		CClassView::OnClsPropertyCommon(index);
	
	CListView::OnLButtonDblClk(nFlags, point);
}

void CClassView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: このブロックはポップアップ メニュー コンポーネントによって追加されました
	{
		if (point.x == -1 && point.y == -1){
			//キーストロークの発動
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_CLASS_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

//DEL void CClassView::OnUpdateEditCopyCut(CCmdUI* pCmdUI)
//DEL {
//DEL 	// CG: この関数はクリップボード アシスタント コンポーネントによって追加されました
//DEL 	pCmdUI->Enable(IsSelected());
//DEL }

//DEL void CClassView::OnUpdateEditPaste(CCmdUI* pCmdUI)
//DEL {
//DEL 	// CG: この関数はクリップボード アシスタント コンポーネントによって追加されました
//DEL 	pCmdUI->Enable(::IsClipboardFormatAvailable(m_nClipboardFormat));
//DEL }

//DEL void CClassView::OnEditCopy()
//DEL {
//DEL 	// CG: このブロックはクリップボード アシスタント コンポーネントによって追加されました
//DEL 	{
//DEL 		CSharedFile	memFile;
//DEL 		CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);
//DEL 
//DEL 		// シリアライズ データをアーカイブ オブジェクトへ
//DEL 		DoCutCopyPaste(ar, FALSE);
//DEL 
//DEL 		ar.Flush();
//DEL 
//DEL 		HGLOBAL hData = memFile.Detach();
//DEL 		if (OpenClipboard())
//DEL 		{
//DEL 			::SetClipboardData(m_nClipboardFormat, hData);
//DEL 			CloseClipboard();
//DEL 		}
//DEL 		else
//DEL 			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
//DEL 	}
//DEL }

//DEL void CClassView::OnEditCut()
//DEL {
//DEL 	// CG: このブロックはクリップボード アシスタント コンポーネントによって追加されました
//DEL 	{
//DEL 		CSharedFile	memFile;
//DEL 		CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);
//DEL 
//DEL 		// シリアライズ データをアーカイブ オブジェクトへ
//DEL 		DoCutCopyPaste(ar, TRUE);
//DEL 
//DEL 		ar.Flush();
//DEL 
//DEL 		HGLOBAL hData = memFile.Detach();
//DEL 		if (OpenClipboard())
//DEL 		{
//DEL 			::SetClipboardData(m_nClipboardFormat, hData);
//DEL 			CloseClipboard();
//DEL 		}
//DEL 		else
//DEL 			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
//DEL 	}
//DEL }

//DEL void CClassView::OnEditPaste()
//DEL {
//DEL 	// CG: このブロックはクリップボード アシスタント コンポーネントによって追加されました
//DEL 	{
//DEL 		if (OpenClipboard())
//DEL 		{
//DEL 			HANDLE hData = ::GetClipboardData(m_nClipboardFormat);
//DEL 			if (hData != NULL)
//DEL 			{
//DEL 				CSharedFile memFile;
//DEL 				memFile.SetHandle(hData,FALSE);
//DEL 				CArchive ar(&memFile, CArchive::load);
//DEL 
//DEL 				// データをドキュメントへシリアライズ
//DEL 				DoCutCopyPaste(ar, FALSE);
//DEL 				ar.Close();
//DEL 				memFile.Detach();
//DEL 			}
//DEL 			else
//DEL 				AfxMessageBox(CG_IDS_CANNOT_GET_CLIPBOARD_DATA);
//DEL 			CloseClipboard();
//DEL 		}
//DEL 		else
//DEL 			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
//DEL 	}
//DEL 
//DEL }

BOOL CClassView::IsSelected()
{
	// TODO: コピーおよび切り取りメニューの有効/無効化を選択的に行えるようなコードを追加または
	//       修正してください。一つ以上のアイテムが選択された場合には TRUE を、
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	if((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))!=-1) 
		return TRUE;
	else
		return FALSE;
}

void CClassView::DoCutCopyPaste(CArchive &ar, BOOL bCut)
{


	// TODO: 選択されているデータを CArchive オブジェクト経由でクリップードへまたは
	//       クリップボードからコピーするコードを追加してください。メモ: 
	//       ar.IsStoring() が TRUE の場合は、コピーまたは切り取り操作を意味します。

	GetDocument()->Serialize(ar);

	if (bCut)
	{
		ASSERT(ar.IsStoring()); //切り取り、貼り付け操作はありません

		// TODO: 現在選択されているアイテムを削除するためにはコードを追加または置き換えてください。

		GetDocument()->DeleteContents();
	}

	// 切り取りまたは貼り付け操作の場合、変更通りにビューおよびフラグを更新します
	if (!(ar.IsStoring() && !bCut))
	{
		GetDocument()->UpdateAllViews(NULL);
		GetDocument()->SetModifiedFlag();
	}
}

void CClassView::OnEditDelete() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	int index;
	POSITION pos;
	CClass* pCls;

	if((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))!=-1) {
		if(pDoc->cls.GetCount()>=2 && index > 0 && index<pDoc->cls.GetCount()) {
			pos = (POSITION)pDoc->cls.FindIndex(index);
			if(pos) {
				pCls=(CClass*)pDoc->cls.GetAt(pos);
				TRACE("pCls->name=%s \n", pCls->name);
				delete pCls;
				pDoc->cls.RemoveAt(pos);
				pDoc->ac=0;
				pDoc->am=-1;
				pDoc->pAPadf = NULL;
				InvalidateRect(NULL,FALSE);
				pDoc->UpdateAllViews(NULL);
				SetListItems();
				pDoc->SetModifiedFlag();
			}
		}
	}
}

void CClassView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	if((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))!=-1)
		pCmdUI->Enable(index>0 && index<pDoc->cls.GetCount());
	else
		pCmdUI->Enable(FALSE);
}

void CClassView::OnClsProperty() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED); 
	OnClsPropertyCommon(index);
}

void CClassView::OnUpdateClsProperty(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	pCmdUI->Enable((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))>=0);
}
