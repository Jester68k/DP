// PadPropertySheet.cpp : �C���v�������e�[�V���� �t�@�C��
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
	// ���̈ʒu�Ƀv���p�e�B �y�[�W�����ׂĒǉ����Ă��������B
	// �����ɒǉ����鏇������ʏ�ɕ\������鏇���ɂȂ�܂��B
	// �f�t�H���g�ł͍ŏ��̃v���p�e�B �y�[�W���A�N�e�B�u��
	// �Ȃ�܂��B���̃v���p�e�B �y�[�W���A�N�e�B�u�ɂ��邽
	// �߂ɂ́ASetActivePage() �֐����Ăяo���Ă��������B 
	// 

	AddPage(&m_Page1);
}

CPadfPropertySheet::~CPadfPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CPadfPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CPadPropertySheet)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPadfPropertySheet ���b�Z�[�W �n���h��


