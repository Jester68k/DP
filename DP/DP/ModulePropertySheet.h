// ModulePropertySheet.h : �w�b�_�[ �t�@�C��
//
// ���̃N���X�̓J�X�^�� ���[�_�� �v���p�e�B �V�[�g���`���܂��B 
// CModulePropertySheet.
 
#ifndef __MODULEPROPERTYSHEET_H__
#define __MODULEPROPERTYSHEET_H__

#include "ModulePropertyPage1.h"

/////////////////////////////////////////////////////////////////////////////
// CModulePropertySheet

class CModulePropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CModulePropertySheet)

// �\�z
public:
	CModulePropertySheet(CWnd* pWndParent = NULL);

// �A�g���r���[�g
public:
	CModulePropertyPage1 m_Page1;

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CModulePropertySheet)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CModulePropertySheet();

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CModulePropertySheet)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __MODULEPROPERTYSHEET_H__
