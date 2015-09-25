// VarDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "VE.h"
#include "VarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVarDlg �_�C�A���O


CVarDlg::CVarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVarDlg)
	m_kind = -1;
	m_comment = _T("");
	m_name = _T("");
	m_scope = -1;
	m_start = _T("");
	m_type = -1;
	m_pointer = -1;
	m_struct = _T("");
	m_accesstype = -1;
	//}}AFX_DATA_INIT
}


void CVarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVarDlg)
	DDX_CBIndex(pDX, IDC_KIND, m_kind);
	DDX_Text(pDX, IDC_COMMENT, m_comment);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_CBIndex(pDX, IDC_SCOPE, m_scope);
	DDX_Text(pDX, IDC_START, m_start);
	DDX_CBIndex(pDX, IDC_TYPE, m_type);
	DDX_CBIndex(pDX, IDC_POINTER, m_pointer);
	DDX_Text(pDX, IDC_STRUCT, m_struct);
	DDX_CBIndex(pDX, IDC_ACCESSTYPE, m_accesstype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVarDlg, CDialog)
	//{{AFX_MSG_MAP(CVarDlg)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVarDlg ���b�Z�[�W �n���h��

void CVarDlg::OnSelchangeType() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	GetDlgItem(IDC_STRUCT)->EnableWindow(((CComboBox*)GetDlgItem(IDC_TYPE))->GetCurSel()>=TYPE_STRUCT);
}

BOOL CVarDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	GetDlgItem(IDC_STRUCT)->EnableWindow(((CComboBox*)GetDlgItem(IDC_TYPE))->GetCurSel()>=TYPE_STRUCT);
	GetDlgItem(IDC_ACCESSTYPE)->EnableWindow(access_flag);
	GetDlgItem(IDC_TYPE)->SetFocus();
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
