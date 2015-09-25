// PadPropertySheet.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "resource.h"
#include "PadfPropertySheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPadPropertySheet

IMPLEMENT_DYNAMIC(CPadfPropertySheet, CPropertySheet)

CPadfPropertySheet::CPadfPropertySheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PAD_PROPSHT_CAPTION, pWndParent)
{
	// この位置にプロパティ ページをすべて追加してください。
	// ここに追加する順序が画面上に表示される順序になります。
	// デフォルトでは最初のプロパティ ページがアクティブに
	// なります。他のプロパティ ページをアクティブにするた
	// めには、SetActivePage() 関数を呼び出してください。 
	// 

	AddPage(&m_Page1);
}

CPadfPropertySheet::~CPadfPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CPadfPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CPadPropertySheet)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPadfPropertySheet メッセージ ハンドラ


