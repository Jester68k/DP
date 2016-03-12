// LeftView.cpp : CLeftView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "VE.h"

#include "Padf.h"
#include "VLine.h"
#include "LeftView.h"
#include "VEDoc.h"
#include "Class.h"
#include "LeftView.h"
#include "VarView.h"
#include "resource.h"
#include "ModulePropertyPage1.h"
#include "ModulePropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CScrollView)

BEGIN_MESSAGE_MAP(CLeftView, CScrollView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopyCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopyCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_INSERT, OnInsert)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_INSERT_M, OnInsertM)
	ON_COMMAND(ID_LINE, OnLine)
	ON_UPDATE_COMMAND_UI(ID_LINE, OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY( TTN_GETDISPINFO, 0, OnTipsDispInfo )

	//}}AFX_MSG_MAP
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView �N���X�̍\�z/����

CLeftView::CLeftView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	line_mode=0;
	// CG: ���̍s�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	m_nClipboardFormat = ::RegisterClipboardFormat(_T("MdlTree"));
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView �N���X�̕`��

void CLeftView::OnDraw(CDC* pDC)
{
	CVEDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
	CPen myPen, *pOldPen;
	DWORD mdl_num;
	POSITION lpos, lpos2;
	CClass* pCls;
	CModule *pMdl, *pMdl2;
	CRectTracker rt;

	if(pDoc->ac < 0 || pDoc->ac >= pDoc->cls.GetCount())
		return;
	TRACE("classes: %d, class # = %d ", pDoc->cls.GetCount(), pDoc->ac);
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	TRACE("pCls = %x modules=%d\n", pCls, pCls->mdl.GetCount());
	if(!(pCls->mdl.GetCount()))
		return;

	width = 0;
	height =0;
	lpos=pCls->mdl.GetHeadPosition();
	while(lpos) {
		pMdl=(CModule*)pCls->mdl.GetNext(lpos);
		if (width < pMdl->rect.right)
				width=pMdl->rect.right+10;
		if (height < pMdl->rect.bottom)
				height=pMdl->rect.bottom+10;
	}
	CSize sizeTotal;
	// ���̃r���[�̃T�C�Y�̍��v���v�Z���܂��B
	sizeTotal.cx = width;
	sizeTotal.cy = height;
	SetScrollSizes(MM_TEXT, sizeTotal);

	myPen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	pOldPen = pDC->SelectObject(&myPen);
	pos = GetScrollPosition();
	lpos=pCls->mdl.GetHeadPosition();
	while(lpos) {
		pMdl=(CModule*)pCls->mdl.GetNext(lpos);
		sx=pMdl->rect.left;
		sy=pMdl->rect.top;
		ex=pMdl->rect.right;
		ey=pMdl->rect.bottom;
		pDC->Rectangle(pMdl->rect);
		pDC->DrawText(pMdl->name,pMdl->rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER); 
		for(j=0; j<pMdl->line.GetSize(); j++) {
			mdl_num = pMdl->line[j];
			pDC->MoveTo((sx+ex)/2,ey);	// ���̃��W���[���̉�
			lpos2=pCls->mdl.FindIndex(mdl_num);
			pMdl2=(CModule*)(pCls->mdl.GetAt(lpos2));
			pDC->LineTo((pMdl2->rect.left + pMdl2->rect.right)/2, pMdl2->rect.top);	// ���̃��W���[���̏�
		}
		if(pMdl->recursive==TRUE) {
			pDC->MoveTo((sx+ex)/2, ey);
			pDC->LineTo((sx+ex)/2, ey+8);
			pDC->LineTo(sx-8, ey+8);
			pDC->LineTo(sx-8, sy-8);
			pDC->LineTo((sx+ex)/2, sy-8);
			pDC->LineTo((sx+ex)/2, sy);
		}
	}
	if(pDoc->am!=-1) {
		rt.m_nStyle = CRectTracker::resizeInside;
		lpos=pCls->mdl.FindIndex(pDoc->am);
		pMdl= (CModule*)pCls->mdl.GetAt(lpos);
		rt.m_rect = pMdl->rect;
		rt.m_rect.left -= pos.x;
		rt.m_rect.top -= pos.y;
		rt.m_rect.right -= pos.x;
		rt.m_rect.bottom -= pos.y;
		rt.Draw(pDC);
	}
	pDC->SelectObject(pOldPen);
}

void CLeftView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: ���̃r���[�̃T�C�Y�̍��v���v�Z���܂��B
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

    m_toolTip_text = "";

    m_toolTip.Create( this );                          //�c�[���`�b�v�̍쐬
    m_toolTip.AddTool( this, LPSTR_TEXTCALLBACK );
	m_toolTip.SetMaxTipWidth(480);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView �N���X�̈��

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈������
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView �N���X�̐f�f

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVEDoc* CLeftView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVEDoc)));
	return (CVEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView �N���X�̃��b�Z�[�W �n���h��

void CLeftView::OnContextMenu(CWnd*, CPoint point)
{
	CVEDoc* pDoc = GetDocument();
	int i;
	POSITION cPos, lpos;
	CClass* pCls;
	CModule* pMdl;

	if(line_mode)	// �����������[�h�Ȃ��������
		line_mode=0;
	pos = GetScrollPosition();
	client_point = point;
	ScreenToClient(&client_point);
	sx=client_point.x;
	sy=client_point.y;
	i=0;
	cPos=pDoc->cls.GetHeadPosition();
	pCls=(CClass*)(pDoc->cls.GetNext(cPos));

	lpos=pCls->mdl.GetHeadPosition();
	while(lpos) {
		pMdl=(CModule*)pCls->mdl.GetNext(lpos);
		rt.m_rect = pMdl->rect;
		rt.m_rect.left -= pos.x;
		rt.m_rect.top -= pos.y;
		rt.m_rect.right -= pos.x;
		rt.m_rect.bottom -= pos.y;
		if (rt.HitTest(client_point)>=0) {
			pDoc->am=i;
			InvalidateRect(NULL);
			pDoc->UpdateAllViews(NULL);
			break;
		}
		i++;
	}

	// CG: ���̃u���b�N�̓|�b�v�A�b�v ���j���[ �R���|�[�l���g�ɂ���Ēǉ�����܂���
	{
		if (point.x == -1 && point.y == -1){
			//�L�[�X�g���[�N�̔���
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_LEFT_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CLeftView::OnUpdateEditCopyCut(CCmdUI* pCmdUI)
{
	// CG: ���̊֐��̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	pCmdUI->Enable(IsSelected());
}

void CLeftView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	// CG: ���̊֐��̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	pCmdUI->Enable(::IsClipboardFormatAvailable(m_nClipboardFormat));
}

void CLeftView::OnEditCopy()
{
	// CG: ���̃u���b�N�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	{
		CSharedFile	memFile;
		CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);

		// �V���A���C�Y �f�[�^���A�[�J�C�u �I�u�W�F�N�g��
		DoCutCopyPaste(ar, FALSE);

		ar.Flush();

		HGLOBAL hData = memFile.Detach();
		if (OpenClipboard())
		{
			::SetClipboardData(m_nClipboardFormat, hData);
			CloseClipboard();
		}
		else
			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
	}
}

void CLeftView::OnEditCut()
{
	// CG: ���̃u���b�N�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	{
		CSharedFile	memFile;
		CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);

		// �V���A���C�Y �f�[�^���A�[�J�C�u �I�u�W�F�N�g��
		DoCutCopyPaste(ar, TRUE);

		ar.Flush();

		HGLOBAL hData = memFile.Detach();
		if (OpenClipboard())
		{
			::SetClipboardData(m_nClipboardFormat, hData);
			CloseClipboard();
		}
		else
			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
	}
}

void CLeftView::OnEditPaste()
{
	// CG: ���̃u���b�N�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	{
		if (OpenClipboard())
		{
			HANDLE hData = ::GetClipboardData(m_nClipboardFormat);
			if (hData != NULL)
			{
				CSharedFile memFile;
				memFile.SetHandle(hData,FALSE);
				CArchive ar(&memFile, CArchive::load);

				// �f�[�^���h�L�������g�փV���A���C�Y
				DoCutCopyPaste(ar, FALSE);
				ar.Close();
				memFile.Detach();
			}
			else
				AfxMessageBox(CG_IDS_CANNOT_GET_CLIPBOARD_DATA);
			CloseClipboard();
		}
		else
			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
	}

}

BOOL CLeftView::IsSelected()
{
	// TODO: �R�s�[����ѐ؂��胁�j���[�̗L��/��������I��I�ɍs����悤�ȃR�[�h��ǉ��܂���
	//       �C�����Ă��������B��ȏ�̃A�C�e�����I�����ꂽ�ꍇ�ɂ� TRUE ���A
	//       �I���A�A�C�e�����I������Ă��Ȃ��ꍇ�� FALSE ��Ԃ��܂�
	if (GetDocument()->am!=-1)
		return TRUE;
	else 
		return FALSE;
}

void CLeftView::DoCutCopyPaste(CArchive &ar, BOOL bCut)
{
	int i, j, doc_type, num_padfs;
	USHORT width, height;
	CVEDoc* pDoc=GetDocument();
	WORD size;
	CClass* pCls;
	CModule* pMdl;
	CPadf* pPadf;
	CVLine* pVl;
	POSITION cPos, lpos;
	// TODO: �I������Ă���f�[�^�� CArchive �I�u�W�F�N�g�o�R�ŃN���b�v�[�h�ւ܂���
	//       �N���b�v�{�[�h����R�s�[����R�[�h��ǉ����Ă��������B����: 
	//       ar.IsStoring() �� TRUE �̏ꍇ�́A�R�s�[�܂��͐؂��葀����Ӗ����܂��B
	i=pDoc->am;
	if(ar.IsStoring()) {
		if(i==-1)
			return;
		ar << (DWORD)0;
		cPos=pDoc->cls.GetHeadPosition();
		pCls=(CClass*)(pDoc->cls.GetNext(cPos));
		lpos=pCls->mdl.FindIndex(i);
		pMdl=(CModule*)(pCls->mdl.GetAt(lpos));
		ar << (CString)pMdl->name;
		ar << (CString)pMdl->arg;
		ar << (WORD)pMdl->ret_type;
		ar << (USHORT)(pMdl->rect.right-pMdl->rect.left);
		ar << (USHORT)(pMdl->rect.bottom-pMdl->rect.top);
		ar << (USHORT)pMdl->recursive;
		pVl = &pMdl->vline;
		ar << pVl;
		ar << pMdl->line.GetSize();
		for(j=0; j<pMdl->line.GetSize(); j++)
			ar << pMdl->line[j];
	}
	else {
		ar >> (DWORD&)doc_type;
		if (doc_type != 0)
			return;
		pMdl = new CModule();
		ar >> (CString&)pMdl->name;
		ar >> (CString&)pMdl->arg;
		ar >> (WORD&)pMdl->ret_type;
		ar >> (USHORT&)width;
		ar >> (USHORT&)height;
		pMdl->rect.left = sx;
		pMdl->rect.top = sy;
		pMdl->rect.right = sx + width - 1;
		pMdl->rect.bottom = sy + height - 1;
		ar >> (USHORT&)num_padfs;
		ar >> (USHORT&)pMdl->recursive;
		ar >> pVl;
		pMdl->vline.x = pVl->x;
		pMdl->vline.sy = pVl->sy;
		pMdl->vline.ey = pVl->ey;
		pMdl->vline.hline_y = pVl->hline_y;
		num_padfs = pVl->padf_list.GetCount();
		if (num_padfs>0) {
			while (--num_padfs >= 0) {
				ar >> pPadf;
				pMdl->vline.padf_list.AddTail((CObject*)pPadf);
			}
		}
		ar >> (DWORD&)size;
		pMdl->line.SetSize(size);
		for(j=0; j<size; j++)
			ar >> pMdl->line[j];
		if(pDoc->am!=-1)
			pMdl->line.Add(i);
	}
//	GetDocument()->Serialize(ar);

	if (bCut)
	{
		ASSERT(ar.IsStoring()); //�؂���A�\��t������͂���܂���

		// TODO: ���ݑI������Ă���A�C�e�����폜���邽�߂ɂ̓R�[�h��ǉ��܂��͒u�������Ă��������B
		CLeftView::OnEditDelete();
//		GetDocument()->DeleteContents();
	}

	// �؂���܂��͓\��t������̏ꍇ�A�ύX�ʂ�Ƀr���[����уt���O���X�V���܂�
	if (!(ar.IsStoring() && !bCut))
	{
		GetDocument()->UpdateAllViews(NULL);
		GetDocument()->SetModifiedFlag();
	}
}

void CLeftView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	POSITION lpos;
	CClass* pCls;
	CModule* pMdl;
	int move_x, move_y;
	
	i=0;
	pos = GetScrollPosition();
	pCls=(CClass*)(pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac)));
	lpos=pCls->mdl.GetHeadPosition();
	while(lpos) {
		pMdl=(CModule*)pCls->mdl.GetNext(lpos);
		rt.m_rect = pMdl->rect;
		rt.m_rect.left -= pos.x;
		rt.m_rect.top -= pos.y;
		rt.m_rect.right -= pos.x;
		rt.m_rect.bottom -= pos.y;
		if (rt.HitTest(point)>=0) {
			switch(line_mode) {
			case 0:
				rt.Track(this,point,FALSE);
				move_x = rt.m_rect.left + pos.x - pMdl->rect.left;
				move_y = rt.m_rect.top + pos.y - pMdl->rect.top;
				pMdl->rect.left += move_x;
				pMdl->rect.top += move_y;
				pMdl->rect.right += move_x;
				pMdl->rect.bottom += move_y;
				pDoc->am=i;
				pDoc->pAPadf = NULL;
				InvalidateRect(NULL);
				pDoc->UpdateAllViews(this);
				GetDocument()->SetModifiedFlag();
				return;
				break;
			case 1:
				line_mode=2;
				pDoc->am=i;
				pDoc->pAPadf = NULL;
				InvalidateRect(NULL);
				pDoc->UpdateAllViews(this);
				return;
				break;
			case 2:
				pMdl = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
				pMdl->line.Add(i);
				line_mode=0;
				InvalidateRect(NULL);
				pDoc->UpdateAllViews(this);
				GetDocument()->SetModifiedFlag();
				return;
				break;
			}
		}
		i++;
	}

	if(-1!=pDoc->am) {
		before_am=pDoc->am;
		pDoc->am=-1;
	} else {
		client_point=point;
		OnInsert();
	}
	InvalidateRect(NULL);
	pDoc->UpdateAllViews(this);
//	POSITION v_pos = pDoc->GetFirstViewPosition();
//	CVarView* pVarView = (CVarView*)pDoc->GetNextView(v_pos);
//	pVarView->SetListItems();

	CScrollView::OnLButtonDown(nFlags, point);
}

void CLeftView::OnInsert() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CLeftView::OnInsertCommon();
}

void CLeftView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	POSITION lpos;
	CClass* pCls;
	CModule* pMdl;
	
	pos = GetScrollPosition();
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	lpos=pCls->mdl.GetHeadPosition();
	while(lpos) {
		pMdl=(CModule*)pCls->mdl.GetNext(lpos);
		rt.m_rect = pMdl->rect;
		rt.m_rect.left -= pos.x;
		rt.m_rect.top -= pos.y;
		rt.m_rect.right -= pos.x;
		rt.m_rect.bottom -= pos.y;
		if (rt.HitTest(point)>=0) {
			OnProperties();
			pDoc->am=i;
//			InvalidateRect(NULL);
			return;
		}
	}
	pDoc->am=before_am;
	client_point=point;
	OnInsert();

	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CLeftView::OnProperties()
{
	// TODO: ���̊֐���ʂ��ăv���W�F�N�g�փA�^�b�`���ꂽ�v���p�e�B
	// �V�[�g�͂ǂ̃��b�Z�[�W �n���h��������t�b�N����Ă��܂���B
	// ���ۂɃv���p�e�B �V�[�g���g�p���邽�߂ɂ́A���̃v���p�e�B��
	// ���j���[ �A�C�e���܂��̓c�[�� �o�[ �{�^���̂悤�ȃv���W�F�N�g
	// ���̃R���g���[���Ɗ֘A�t����K�v������܂��B

	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CModulePropertySheet propSheet;
	CClass* pCls;
	CModule* pMdl;
	int num_padfs;

	if (-1==pDoc->am)
		return;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	pMdl=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));

	propSheet.m_Page1.m_mname=pMdl->name;
	propSheet.m_Page1.m_marg=pMdl->arg;
	propSheet.m_Page1.m_mret_type=pMdl->ret_type;
	propSheet.m_Page1.m_mret_pointer=pMdl->ret_pointer;
	propSheet.m_Page1.m_accesstype = pMdl->access_type;
	propSheet.m_Page1.m_mcomment=pMdl->comment;
	num_padfs = pMdl->vline.padf_list.GetCount();
	propSheet.m_Page1.m_mnumpadfs = num_padfs;
	propSheet.m_Page1.m_mnum_vars=pMdl->var.GetCount();
	propSheet.m_Page1.m_mrecursive=pMdl->recursive;
	propSheet.m_Page1.m_minline=pMdl->inline_flag;
	propSheet.m_Page1.m_mfunctype=pMdl->func_type;
	clsaccesstype_flag = (pCls->type>=CLSTYPE_CLASS);
	if (propSheet.DoModal()==IDOK) {
		CClientDC dc(this);
		CSize size;

		pMdl->name = propSheet.m_Page1.m_mname;
		pMdl->arg = propSheet.m_Page1.m_marg;
		pMdl->ret_type = propSheet.m_Page1.m_mret_type;
		pMdl->ret_pointer = propSheet.m_Page1.m_mret_pointer;
		pMdl->access_type = propSheet.m_Page1.m_accesstype;
		pMdl->comment = propSheet.m_Page1.m_mcomment;
		pMdl->recursive = propSheet.m_Page1.m_mrecursive;
		pMdl->inline_flag = propSheet.m_Page1.m_minline;
		pMdl->func_type = propSheet.m_Page1.m_mfunctype;
		size = dc.GetTextExtent(pMdl->name);
		pMdl->rect.right = pMdl->rect.left + size.cx + 2*8;
		pDoc->SetModifiedFlag();
		InvalidateRect(NULL,TRUE);
		pDoc->UpdateAllViews(this);
	}
}

void CLeftView::OnEditDelete(void) 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	POSITION lpos;
	CClass* pCls;
	CModule* pMdl;
	int l, lsize;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if (pDoc->am==-1 || pDoc->am >= pCls->mdl.GetCount())
		return;
	lpos=pCls->mdl.GetHeadPosition();
	while(lpos) {
		pMdl = (CModule*)pCls->mdl.GetNext(lpos);
		lsize=pMdl->line.GetSize();
		for(l=0; l<lsize; l++) {
			if(pMdl->line[l]==pDoc->am) {
				pMdl->line.RemoveAt(l);
				lsize--;
				l--;
				continue;
			}
			if(pMdl->line[l]>pDoc->am)
				pMdl->line[l]--;
		}
	}
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	lpos = pCls->mdl.FindIndex(pDoc->am);
	pMdl = (CModule*)pCls->mdl.GetAt(lpos);
	pCls->mdl.RemoveAt(lpos);
	delete pMdl;
	pDoc->am=-1;
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(this);
	InvalidateRect(NULL);
}

void CLeftView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	CPoint pos, point;
	ASSERT_VALID(pDoc);
	CClass* pCls;
	CModule* pMdl;
	POSITION lpos;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if(nChar=='I') {
		CLeftView::OnInsertM();
		return;
	}
	if(nChar=='L') {
		CLeftView::OnLine();
		return;
	}
	if(pDoc->am==-1) { // ���W���[�����I������Ă��Ȃ��Ȃ�
		GetCursorPos(&point); // �}�E�X�E�J�[�\���̈ʒu�𓾂�(Windows API)
		switch (nChar) {
		case VK_LEFT:
			point.x-=8;
			break;
		case VK_RIGHT:
			point.x+=8;
			break;
		case VK_UP:
			point.y-=8;
			break;
		case VK_DOWN:
			point.y+=8;
			break;
		case VK_RETURN:
			client_point = point;
			ScreenToClient(&client_point);
			pos = GetScrollPosition();
			lpos = pCls->mdl.GetHeadPosition();
			while(lpos) {
				pMdl = (CModule*)pCls->mdl.GetNext(lpos);
				rt.m_rect = pMdl->rect;
				rt.m_rect.left -= pos.x;
				rt.m_rect.top -= pos.y;
				rt.m_rect.right -= pos.x;
				rt.m_rect.bottom -= pos.y;
				if (rt.HitTest(client_point)>=0) {
					pDoc->am=i;
					InvalidateRect(NULL);
					pDoc->UpdateAllViews(this);
					return;
				}
			}
			break;
		default:
			MessageBeep(0);
			break;
		}
		SetCursorPos(point.x,point.y);	// �}�E�X�E�J�[�\���̈ʒu��ύX(Windows API)
	} else { // ���W���[�����I������Ă���Ȃ�
		pMdl=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
		switch(nChar) {
		case VK_RETURN:
			CLeftView::OnProperties();
			break;
		case VK_DELETE:
			CLeftView::OnEditDelete();
			break;
		case VK_LEFT:
			pMdl->rect.left--;
			pMdl->rect.right--;
			break;
		case VK_RIGHT:
			pMdl->rect.left++;
			pMdl->rect.right++;
			break;
		case VK_UP:
			pMdl->rect.top--;
			pMdl->rect.bottom--;
			break;
		case VK_DOWN:
			pMdl->rect.top++;
			pMdl->rect.bottom++;
			break;
		case VK_ESCAPE:
			pDoc->am=-1;
			InvalidateRect(NULL);
			pDoc->UpdateAllViews(this);
			break;
		default:
			MessageBeep(0);
			break;
		}
		InvalidateRect(NULL);
	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CLeftView::OnInsertM(void) 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	int i, max=0, max_bottom=0;
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClass* pCls;
	CModule* pMdl;
	POSITION lpos;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if(pDoc->am!=-1) {	// �������W���[�����I������Ă���Ȃ��
		pMdl = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
		client_point.x=pMdl->rect.left;	// �V�������W���[���̂w���W�͑I������Ă��郂�W���[���Ɠ���
		client_point.y=pMdl->rect.bottom+16; // �V�������W���[���̂x���W�͑I������Ă��郂�W���[���̉��Ӂ{�P�U
	} else {
		lpos = pCls->mdl.GetHeadPosition();
		i=0;
		while(lpos) {
			pMdl = (CModule*)pCls->mdl.GetNext(lpos);
			if(pMdl->rect.bottom>max_bottom) {
				max=i;
				max_bottom = pMdl->rect.bottom;
			}
			i++;
		}
		pMdl=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(max));
		client_point.x = pMdl->rect.left;
		client_point.y = max_bottom + 16;
	}
	CLeftView::OnInsertCommon();
}

void CLeftView::OnInsertCommon()
{
	CVEDoc* pDoc = GetDocument();
	CModulePropertySheet propSheet;
	CSize size;
	ASSERT_VALID(pDoc);
	CClass* pCls;
	CModule* pMdl;
	CClientDC dc(this);

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if(CLSTYPE_UNION==pCls->type || CLSTYPE_INTERFACE==pCls->type)
		return;
	propSheet.m_Page1.m_mname="";
	propSheet.m_Page1.m_marg="";
	propSheet.m_Page1.m_mret_type=TYPE_VOID;
	propSheet.m_Page1.m_mret_pointer=0;
	propSheet.m_Page1.m_mret_struct="";
	propSheet.m_Page1.m_accesstype = AT_PUBLIC;
	propSheet.m_Page1.m_mcomment="";
	propSheet.m_Page1.m_mnumpadfs=0;
	propSheet.m_Page1.m_mrecursive=FALSE;
	propSheet.m_Page1.m_mfunctype=FUNCTYPE_NORMAL;
	propSheet.m_Page1.m_minline=FALSE;
	clsaccesstype_flag = (pCls->type>=CLSTYPE_CLASS);
	if (propSheet.DoModal()==IDOK && propSheet.m_Page1.m_mname!="") {
		pMdl = new CModule();
		pMdl->name = propSheet.m_Page1.m_mname;
		pMdl->arg = propSheet.m_Page1.m_marg;
		if (pMdl->arg=="")
			pMdl->arg="void";
		pMdl->ret_type = propSheet.m_Page1.m_mret_type;
		pMdl->ret_pointer = propSheet.m_Page1.m_mret_pointer;
		pMdl->ret_class = propSheet.m_Page1.m_mret_struct;
		pMdl->access_type = propSheet.m_Page1.m_accesstype;
		pMdl->comment = propSheet.m_Page1.m_mcomment;
		pMdl->recursive = propSheet.m_Page1.m_mrecursive;
		if (CLSTYPE_CLASS==pCls->type)
			pMdl->func_type = propSheet.m_Page1.m_mfunctype;
		else
			pMdl->func_type = FUNCTYPE_NORMAL;
		pMdl->inline_flag = propSheet.m_Page1.m_minline;
		pMdl->rect.left = client_point.x;
		pMdl->rect.top = client_point.y;
		size = dc.GetTextExtent(pMdl->name);
		pMdl->rect.right = client_point.x + size.cx + 2*8;
		pMdl->rect.bottom = client_point.y + MODULE_HEIGHT;
		pCls->mdl.AddTail((CObject*)pMdl);
		if(pDoc->am!=-1) {
			pMdl = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
			pMdl->line.Add(pCls->mdl.GetCount()-1);
		}
		pDoc->am = pCls->mdl.GetCount()-1;
		pDoc->SetModifiedFlag();
		InvalidateRect(NULL,FALSE);
		pDoc->UpdateAllViews(NULL);
	}
}

void CLeftView::OnLine() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->am==-1)
		line_mode = 1;
	else
		line_mode = 2;
}

void CLeftView::OnUpdateLine(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClass* pCls;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	pCmdUI->Enable(pCls->mdl.GetCount()>=2);
}

void CLeftView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(pDoc->am!=-1);
}

void CLeftView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CPoint pos;
	POSITION lpos;
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClass* pCls;
	CModule* pm;
	CString str;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	GetParentFrame()->SetActiveView(this, FALSE);
	pos = GetScrollPosition();
	lpos=pCls->mdl.GetHeadPosition();
	while(lpos) {
		pm=(CModule*)pCls->mdl.GetNext(lpos);
		if(pm->rect.PtInRect(point)) {
			m_toolTip_text=type_tbl[pm->ret_type];
			for(int i=0; i<pm->ret_pointer; i++)
				m_toolTip_text+=_T("*");
			m_toolTip_text += _T(" ") + pm->name + _T("(") + pm->arg + _T(") \r\n") + pm->comment + _T("\r\n�o�`�c�}�`�Ƌ�`�R�����g�F");
			str.Format(_T("%d\r\n���[�J���ϐ��F%d"), pm->total_padfs, pm->var.GetCount());
			m_toolTip_text += str;
		    m_toolTip.Update();
			return;
		}
	}
	switch(pCls->type) {
	case CLSTYPE_GLOBAL:
		m_toolTip_text.Format(_T("�O���[�o���ϐ��F%d\r\n�O���[�o���֐��F%d"), pCls->var.GetCount(), pCls->mdl.GetCount());
		break;
	case CLSTYPE_UNION:
		m_toolTip_text.Format(_T("�����o�ϐ��F%d"), pCls->var.GetCount());
		break;
	default:
		m_toolTip_text.Format(_T("�����o�ϐ��F%d\r\n�����o�֐��F%d"), pCls->var.GetCount(), pCls->mdl.GetCount());
		break;
	}
    m_toolTip.Update();
//	m_toolTip.Pop();
	CScrollView::OnMouseMove(nFlags, point);
}



BOOL CLeftView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
    m_toolTip.RelayEvent( pMsg );
	return CScrollView::PreTranslateMessage(pMsg);
}

void CLeftView::OnTipsDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMTTDISPINFO lpttd;

	if ( m_toolTip_text != "" ) {              // �c�[���`�b�v�̓��e��\��
		lpttd = (LPNMTTDISPINFO)pNMHDR;
		lpttd->lpszText = (LPSTR)(LPCTSTR)m_toolTip_text;
    }

    *pResult = 0;
}
