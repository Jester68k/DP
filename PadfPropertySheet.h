// PadPropertySheet.h : ヘッダー ファイル
//
// このクラスはカスタム モーダル プロパティ シートを定義します。 
// CPadPropertySheet.
 
#ifndef __PADPROPERTYSHEET_H__
#define __PADPROPERTYSHEET_H__

#include "PadfPropertyPage1.h"

/////////////////////////////////////////////////////////////////////////////
// CPadPropertySheet

class CPadfPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CPadfPropertySheet)

// 構築
public:
	CPadfPropertySheet(CWnd* pWndParent = NULL);

// アトリビュート
public:
	CPadfPropertyPage1 m_Page1;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPadPropertySheet)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CPadfPropertySheet();

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CPadPropertySheet)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __PADPROPERTYSHEET_H__
