
// VE.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "VE.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "VEDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFCTabCtrl	m_wndTabs;
COutputWnd        m_wndOutput;
CPropertiesWnd    m_wndProperties;

CString padf_msg[4][3]={"%s","","","if(%s)","switch(%s)","","for(%s)","while(%s)","do while(%s)","%s","",""};
CString case_str;
BOOL case_flag;
BOOL access_flag = AT_PUBLIC;
BOOL clsaccesstype_flag;
int padf_page_mode;
int padf_len[4][3]={{0,0,0},{4,8,0},{5,7,10},{0,0,0}};
int padf_len2[7]={0,4,8,5,7,10,0};
int cnv_tbl[7][2]={{0,0},{1,0},{1,1},{2,0},{2,1},{2,2},{3,0}};
int cnv_tbl2[4][3]={{0,0,0},{1,2,0},{3,4,5},{6,0,0}};
CString scope_tbl[4]={"auto","static(ローカル)","グローバル",""};
CString scope_src_tbl[3]={"","static","グローバル"};
CString kind_tbl[3]={"変数","定数","マクロ"};
CString clstype_tbl[5]={"ｸﾞﾛｰﾊﾞﾙ","構造体","共用体","クラス","ｲﾝﾀｰﾌｪｰｽ"};
CString acctype_tbl[3]={"public","private","protected"};
CString type_tbl[]={"void","int","unsigned int", "char", "unsigned char", "short", "unsigned short", "long", "unsigned long","float","double","bool","構造体","共用体","クラス"};
CString type_tbl2[]={"",   "int","unsigned int", "char", "unsigned char", "short", "unsigned short", "long", "unsigned long","float","double","bool","構造体","共有体"};
CString c_header_str="#include<iostream>\n#include<assert.h>\n#include<ctype.h>\n#include<errno.h>\n#include<float.h>\n#include<iso646.h>\n#include<limits.h>\n#include<locale.h>\n#include<math.h>\n#include<setjmp.h>\n#include<signal.h>\n#include<stdarg.h>\n#include<stddef.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n#include<time.h>\n#include<wchar.h>\n#include<wctype.h>";
CString cpp_header_str="#include<complex>\n#include<exception> \n#include<fstream> \n#include<iomanip> \n#include<ios> \n#include<iosfwd> \n#include<iostream> \n#include<istream>\n#include<limits> \n#include<locale> \n#include<memory> \n#include<new> \n#include<ostream> \n#include<sstream> \n#include<stdexcept> \n#include<streambuf> \n#include<string> \n#include<strstream> \n#include<typeinfo> \n#include<valarray> \n#include<algorithm> \n#include<bitset> \n#include<deque> \n#include<functional> \n#include<iterator> \n#include<list> \n#include<map> \n#include<numeric> \n#include<queue> \n#include<set> \n#include<stack> \n#include<utility> \n#include<vector> \n#include<cassert> \n#include<cctype> \n#include<cerrno> \n#include<cfloat> \n#include<ciso646> \n#include<climits> \n#include<clocale> \n#include<cmath> \n#include<csetjmp> \n#include<csignal> \n#include<cstdarg> \n#include<cstddef> \n#include<cstdio> \n#include<cstdlib> \n#include<cstring> \n#include<ctime> \n#include<cwchar> \n#include<cwctype>";


// CVEApp

BEGIN_MESSAGE_MAP(CVEApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CVEApp::OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CVEApp コンストラクション

CVEApp::CVEApp()
{
	m_bHiColorIcons = TRUE;

	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// アプリケーションが共通言語ランタイム サポート (/clr) を使用して作成されている場合:
	//     1) この追加設定は、再起動マネージャー サポートが正常に機能するために必要です。
	//     2) 作成するには、プロジェクトに System.Windows.Forms への参照を追加する必要があります。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 下のアプリケーション ID 文字列を一意の ID 文字列で置換します。推奨される
	// 文字列の形式は CompanyName.ProductName.SubProduct.VersionInformation です
	SetAppID(_T("VE.AppID.NoVersion"));

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

// 唯一の CVEApp オブジェクトです。

CVEApp theApp;


// CVEApp 初期化

BOOL CVEApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE ライブラリを初期化します。
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// RichEdit コントロールを使用するには AfxInitRichEdit2() が必要です	
	// AfxInitRichEdit2();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
	LoadStdProfileSettings(16);  // 標準の INI ファイルのオプションをロードします (MRU を含む)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_DPTYPE,
		RUNTIME_CLASS(CVEDoc),
		RUNTIME_CLASS(CChildFrame), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CLeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// メイン MDI フレーム ウィンドウを作成します。
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// 接尾辞が存在する場合にのみ DragAcceptFiles を呼び出します
	//  MDI アプリケーションでは、この呼び出しは、m_pMainWnd を設定した直後に発生しなければなりません。
	// ドラッグ/ドロップ オープンを許可します。
	m_pMainWnd->DragAcceptFiles();

	// DDE、file open など標準のシェル コマンドのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DDE Execute open を使用可能にします。
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CVEApp::ExitInstance()
{
	//TODO: 追加したリソースがある場合にはそれらも処理してください
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CVEApp メッセージ ハンドラー


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CVEApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CVEApp のカスタマイズされた読み込みメソッドと保存メソッド

void CVEApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_EDIT_MENU);
}

void CVEApp::LoadCustomState()
{
}

void CVEApp::SaveCustomState()
{
}

// CVEApp メッセージ ハンドラー



