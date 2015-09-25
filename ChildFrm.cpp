
// ChildFrm.cpp : CChildFrame �N���X�̎���
//

#include "stdafx.h"
#include "VE.h"

#include "Module.h"
#include "ChildFrm.h"
#include "ClassView.h"
#include "LeftView.h"
#include "VarView.h"
#include "VEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame �R���X�g���N�V����/�f�X�g���N�V����

CChildFrame::CChildFrame()
{
	// TODO: �����o�[�������R�[�h�������ɒǉ����Ă��������B
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	// �����E�B���h�E�̍쐬
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
	m_wndSplitter.SetColumnInfo(0,300,100);
	m_wndSplitter.SetColumnInfo(1,600,100);
	if (!m_wndSplitterSub0.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE,m_wndSplitter.IdFromRowCol(0,0)))
		return FALSE;
	if (!m_wndSplitterSub1.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE,m_wndSplitter.IdFromRowCol(0,1)))
		return FALSE;

	if(!m_wndSplitterSub0.CreateView(0, 0, RUNTIME_CLASS(CClassView), CSize(100, 80), pContext) || 
	!m_wndSplitterSub0.CreateView(1, 0, RUNTIME_CLASS(CLeftView), CSize(100, 250), pContext) || 
	!m_wndSplitterSub1.CreateView(0, 0, RUNTIME_CLASS(CVarView), CSize(300, 100), pContext) ||
	!m_wndSplitterSub1.CreateView(1, 0, RUNTIME_CLASS(CVEView), CSize(300, 200), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		m_wndSplitterSub0.DestroyWindow();
		m_wndSplitterSub1.DestroyWindow();
		return FALSE;
	}

	return TRUE;

}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs ��ύX���āAWindow �N���X�܂��̓X�^�C����ύX���܂��B
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame �f�f

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ���b�Z�[�W �n���h���[
