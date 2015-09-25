// ModulePropertySheet.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "resource.h"
#include "ModulePropertySheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModulePropertySheet

IMPLEMENT_DYNAMIC(CModulePropertySheet, CPropertySheet)

CModulePropertySheet::CModulePropertySheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// この位置にプロパティ ページをすべて追加してください。
	// ここに追加する順序が画面上に表示される順序になります。
	// デフォルトでは最初のプロパティ ページがアクティブに
	// なります。他のプロパティ ページをアクティブにするた
	// めには、SetActivePage() 関数を呼び出してください。 
	// 

	AddPage(&m_Page1);
}

CModulePropertySheet::~CModulePropertySheet()
{
}


BEGIN_MESSAGE_MAP(CModulePropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModulePropertySheet)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CModulePropertySheet メッセージ ハンドラ


