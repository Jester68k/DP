
// VE.h : VE アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル
#include "OutputWnd.h"
#include "PropertiesWnd.h"

const int PADF_PROCESS = 0;
const int PADF_SELECTION = 1;
const int PADF_REPEAT = 2;
const int PADF_COMMENT = 3;

const int MAX_PADFS = 65535;

const int MODULE_HEIGHT = 24;
const int PADF_HEIGHT = 24;
const int COMMENT_HEIGHT = 2+16+2;

const int KIND_VARIABLE = 0;
const int KIND_CONSTANT = 1;
const int KIND_MACRO = 2;

const int SCOPE_AUTO = 0;
const int SCOPE_LOCAL_STATIC = 1;
const int SCOPE_GLOBAL = 2;

const int TYPE_VOID = 0;
const int TYPE_INT = 1;
const int TYPE_UNSIGNED_INT = 2;
const int TYPE_CHAR = 3;
const int TYPE_UNSIGNED_CHAR = 4;
const int TYPE_SHORT = 5;
const int TYPE_UNSIGNED_SHORT = 6;
const int TYPE_LONG = 7;
const int TYPE_UNSIGNED_LONG = 8;
const int TYPE_FLOAT = 9;
const int TYPE_DOUBLE = 10;
const int TYPE_BOOL = 11;
const int TYPE_STRUCT = 12;
const int TYPE_UNION = 13;
const int TYPE_CLASS = 14;

const int CLSTYPE_GLOBAL = 0;
const int CLSTYPE_CLASS = 1;
const int CLSTYPE_STRUCT = 2;
const int CLSTYPE_UNION = 3;
const int CLSTYPE_INTERFACE = 4;

const WORD AT_PUBLIC = 0;	// Access Type: public
const WORD AT_PRIVATE = 1;	// private
const WORD AT_PROTECTED = 2;// protected

const WORD FUNCTYPE_NORMAL = 0;			// 通常
const WORD FUNCTYPE_VIRTUAL = 1;		// 仮想関数
const WORD FUNCTYPE_PUREVIRTUAL = 2;	// 純粋仮想関数
const WORD FUNCTYPE_FRIEND = 3;

const WORD COMPILER_VC_ENV = 0;
const WORD COMPILER_VC2015 = 1;
const WORD COMPILER_VC2013 = 2;
const WORD COMPILER_VC2012 = 3;
const WORD COMPILER_VC2010 = 4;
const WORD COMPILER_VC2008 = 5;
const WORD COMPILER_VC60 = 6;
const WORD COMPILER_VC_OTHER = 7;

extern CMFCTabCtrl	m_wndTabs;
extern COutputWnd        m_wndOutput;
extern CPropertiesWnd    m_wndProperties;

extern CString padf_msg[4][3];
extern CString case_str;
extern BOOL case_flag;
extern BOOL access_flag;
extern BOOL clsaccesstype_flag;
extern int padf_page_mode;
extern int padf_len[4][3];
extern int padf_len2[7];
extern int cnv_tbl[7][2], cnv_tbl2[4][3]; // プロパティ・シートとPAD変換用テーブル
extern CString kind_tbl[];
extern CString clstype_tbl[];
extern CString scope_tbl[];	// 変数一覧のスコープ
extern CString type_tbl[], type_tbl2[];
extern CString acctype_tbl[];
extern CString cpp_header_str;

// CVEApp:
// このクラスの実装については、VE.cpp を参照してください。
//

class CVEApp : public CWinAppEx
{
public:
	CVEApp();


// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVEApp theApp;
