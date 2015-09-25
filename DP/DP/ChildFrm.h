
// ChildFrm.h : CChildFrame �N���X�̃C���^�[�t�F�C�X
//

#pragma once
class CVEView;

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// ����
protected:
	CSplitterWndEx m_wndSplitter;
	CSplitterWndEx m_wndSplitterSub0;
	CSplitterWndEx m_wndSplitterSub1;
public:

// ����
public:

// �I�[�o�[���C�h
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CVEView* GetRightPane();
// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
};
