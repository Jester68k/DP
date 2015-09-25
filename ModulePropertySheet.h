// ModulePropertySheet.h : ヘッダー ファイル
//
// このクラスはカスタム モーダル プロパティ シートを定義します。 
// CModulePropertySheet.
 
#ifndef __MODULEPROPERTYSHEET_H__
#define __MODULEPROPERTYSHEET_H__

#include "ModulePropertyPage1.h"

/////////////////////////////////////////////////////////////////////////////
// CModulePropertySheet

class CModulePropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CModulePropertySheet)

// 構築
public:
	CModulePropertySheet(CWnd* pWndParent = NULL);

// アトリビュート
public:
	CModulePropertyPage1 m_Page1;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CModulePropertySheet)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CModulePropertySheet();

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CModulePropertySheet)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __MODULEPROPERTYSHEET_H__
