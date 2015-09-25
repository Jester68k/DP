
// VE.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
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
CString scope_tbl[4]={"auto","static(���[�J��)","�O���[�o��",""};
CString scope_src_tbl[3]={"","static","�O���[�o��"};
CString kind_tbl[3]={"�ϐ�","�萔","�}�N��"};
CString clstype_tbl[5]={"��۰���","�\����","���p��","�N���X","����̪��"};
CString acctype_tbl[3]={"public","private","protected"};
CString type_tbl[]={"void","int","unsigned int", "char", "unsigned char", "short", "unsigned short", "long", "unsigned long","float","double","bool","�\����","���p��","�N���X"};
CString type_tbl2[]={"",   "int","unsigned int", "char", "unsigned char", "short", "unsigned short", "long", "unsigned long","float","double","bool","�\����","���L��"};
CString c_header_str="#include<iostream>\n#include<assert.h>\n#include<ctype.h>\n#include<errno.h>\n#include<float.h>\n#include<iso646.h>\n#include<limits.h>\n#include<locale.h>\n#include<math.h>\n#include<setjmp.h>\n#include<signal.h>\n#include<stdarg.h>\n#include<stddef.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n#include<time.h>\n#include<wchar.h>\n#include<wctype.h>";
CString cpp_header_str="#include<complex>\n#include<exception> \n#include<fstream> \n#include<iomanip> \n#include<ios> \n#include<iosfwd> \n#include<iostream> \n#include<istream>\n#include<limits> \n#include<locale> \n#include<memory> \n#include<new> \n#include<ostream> \n#include<sstream> \n#include<stdexcept> \n#include<streambuf> \n#include<string> \n#include<strstream> \n#include<typeinfo> \n#include<valarray> \n#include<algorithm> \n#include<bitset> \n#include<deque> \n#include<functional> \n#include<iterator> \n#include<list> \n#include<map> \n#include<numeric> \n#include<queue> \n#include<set> \n#include<stack> \n#include<utility> \n#include<vector> \n#include<cassert> \n#include<cctype> \n#include<cerrno> \n#include<cfloat> \n#include<ciso646> \n#include<climits> \n#include<clocale> \n#include<cmath> \n#include<csetjmp> \n#include<csignal> \n#include<cstdarg> \n#include<cstddef> \n#include<cstdio> \n#include<cstdlib> \n#include<cstring> \n#include<ctime> \n#include<cwchar> \n#include<cwctype>";


// CVEApp

BEGIN_MESSAGE_MAP(CVEApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CVEApp::OnAppAbout)
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CVEApp �R���X�g���N�V����

CVEApp::CVEApp()
{
	m_bHiColorIcons = TRUE;

	// �ċN���}�l�[�W���[���T�|�[�g���܂�
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// �A�v���P�[�V���������ʌ��ꃉ���^�C�� �T�|�[�g (/clr) ���g�p���č쐬����Ă���ꍇ:
	//     1) ���̒ǉ��ݒ�́A�ċN���}�l�[�W���[ �T�|�[�g������ɋ@�\���邽�߂ɕK�v�ł��B
	//     2) �쐬����ɂ́A�v���W�F�N�g�� System.Windows.Forms �ւ̎Q�Ƃ�ǉ�����K�v������܂��B
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ���̃A�v���P�[�V���� ID ���������ӂ� ID ������Œu�����܂��B���������
	// ������̌`���� CompanyName.ProductName.SubProduct.VersionInformation �ł�
	SetAppID(_T("VE.AppID.NoVersion"));

	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

// �B��� CVEApp �I�u�W�F�N�g�ł��B

CVEApp theApp;


// CVEApp ������

BOOL CVEApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE ���C�u���������������܂��B
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// RichEdit �R���g���[�����g�p����ɂ� AfxInitRichEdit2() ���K�v�ł�	
	// AfxInitRichEdit2();

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	SetRegistryKey(_T("�A�v���P�[�V���� �E�B�U�[�h�Ő������ꂽ���[�J�� �A�v���P�[�V����"));
	LoadStdProfileSettings(16);  // �W���� INI �t�@�C���̃I�v�V���������[�h���܂� (MRU ���܂�)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_DPTYPE,
		RUNTIME_CLASS(CVEDoc),
		RUNTIME_CLASS(CChildFrame), // �J�X�^�� MDI �q�t���[��
		RUNTIME_CLASS(CLeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ���C�� MDI �t���[�� �E�B���h�E���쐬���܂��B
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// �ڔ��������݂���ꍇ�ɂ̂� DragAcceptFiles ���Ăяo���܂�
	//  MDI �A�v���P�[�V�����ł́A���̌Ăяo���́Am_pMainWnd ��ݒ肵������ɔ������Ȃ���΂Ȃ�܂���B
	// �h���b�O/�h���b�v �I�[�v���������܂��B
	m_pMainWnd->DragAcceptFiles();

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h ���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DDE Execute open ���g�p�\�ɂ��܂��B
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// �R�}���h ���C���Ŏw�肳�ꂽ�f�B�X�p�b�` �R�}���h�ł��B�A�v���P�[�V������
	// /RegServer�A/Register�A/Unregserver �܂��� /Unregister �ŋN�����ꂽ�ꍇ�AFalse ��Ԃ��܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CVEApp::ExitInstance()
{
	//TODO: �ǉ��������\�[�X������ꍇ�ɂ͂������������Ă�������
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CVEApp ���b�Z�[�W �n���h���[


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CVEApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CVEApp �̃J�X�^�}�C�Y���ꂽ�ǂݍ��݃��\�b�h�ƕۑ����\�b�h

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

// CVEApp ���b�Z�[�W �n���h���[



