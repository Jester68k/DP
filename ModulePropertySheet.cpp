// ModulePropertySheet.cpp : �C���v�������e�[�V���� �t�@�C��
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
	// ���̈ʒu�Ƀv���p�e�B �y�[�W�����ׂĒǉ����Ă��������B
	// �����ɒǉ����鏇������ʏ�ɕ\������鏇���ɂȂ�܂��B
	// �f�t�H���g�ł͍ŏ��̃v���p�e�B �y�[�W���A�N�e�B�u��
	// �Ȃ�܂��B���̃v���p�e�B �y�[�W���A�N�e�B�u�ɂ��邽
	// �߂ɂ́ASetActivePage() �֐����Ăяo���Ă��������B 
	// 

	AddPage(&m_Page1);
}

CModulePropertySheet::~CModulePropertySheet()
{
}


BEGIN_MESSAGE_MAP(CModulePropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModulePropertySheet)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CModulePropertySheet ���b�Z�[�W �n���h��


