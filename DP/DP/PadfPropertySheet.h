// PadPropertySheet.h : �w�b�_�[ �t�@�C��
//
// ���̃N���X�̓J�X�^�� ���[�_�� �v���p�e�B �V�[�g���`���܂��B 
// CPadPropertySheet.
 
#ifndef __PADPROPERTYSHEET_H__
#define __PADPROPERTYSHEET_H__

#include "PadfPropertyPage1.h"

/////////////////////////////////////////////////////////////////////////////
// CPadPropertySheet

class CPadfPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CPadfPropertySheet)

// �\�z
public:
	CPadfPropertySheet(CWnd* pWndParent = NULL);

// �A�g���r���[�g
public:
	CPadfPropertyPage1 m_Page1;

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPadPropertySheet)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CPadfPropertySheet();

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CPadPropertySheet)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __PADPROPERTYSHEET_H__
