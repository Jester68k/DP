// VEView.cpp : CVEView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "VE.h"

#include "Padf.h"
#include "VLine.h"
#include "Class.h"
#include "VEDoc.h"
#include "VEView.h"
#include "resource.h"
#include "PadfPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVEView

IMPLEMENT_DYNCREATE(CVEView, CScrollView)

BEGIN_MESSAGE_MAP(CVEView, CScrollView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopyCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopyCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CVEView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PADPROPERTY, OnPadproperty)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_INSERT_PADF, OnInsertPadf)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_INSERT_PADF, OnUpdateInsertPadf)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_PASTE_P, OnEditPasteP)
	ON_COMMAND(ID_INSERT_PROCESS, OnInsertProcess)
	ON_COMMAND(ID_INSERT_IF, OnInsertIf)
	ON_COMMAND(ID_INSERT_SWITCH, OnInsertSwitch)
	ON_COMMAND(ID_INSERT_FOR, OnInsertFor)
	ON_COMMAND(ID_INSERT_WHILE, OnInsertWhile)
	ON_COMMAND(ID_INSERT_DO_WHILE, OnInsertDoWhile)
	ON_UPDATE_COMMAND_UI(ID_PADPROPERTY, OnUpdatePadproperty)
	ON_COMMAND(ID_INSERT_COMMENT, OnInsertComment)
	ON_WM_MOUSEMOVE()
	ON_NOTIFY( TTN_GETDISPINFO, 0, OnTipsDispInfo )
	ON_COMMAND(ID_VIEW_ADJUST, OnViewAdjust)
	ON_COMMAND(ID_INSERTPADF, OnInsertPadf)
	//}}AFX_MSG_MAP
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVEView �N���X�̍\�z/����

CVEView::CVEView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B

	// CG: ���̍s�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	m_nClipboardFormat = ::RegisterClipboardFormat(_T("PAD"));
}

CVEView::~CVEView()
{
}

BOOL CVEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVEView �N���X�̕`��

void CVEView::OnDraw(CDC* pDC)
{
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CPen myPen, *pOldPen;
	CPoint pos = GetScrollPosition();
	CRect rect;
	CRectTracker rt;
	int am;
	CClass* pCls;
	CModule* pm;
	CPadf *pPadf;
	CString str;
	POSITION lpos;	// list position 1, 2

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
	if (pDoc->ac < 0 || pDoc->ac >= pDoc->cls.GetCount())
		return;
	pCls = (CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if (!pCls->mdl.GetCount())
		return;
	if (pDoc->am == -1) {
		return;
	}
	pm = (CModule*)(pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am)));
	if (pm->total_padfs > MAX_PADFS) {
		AfxMessageBox("�o�`�c�}�`�̐����ő吔�𒴂��Ă��܂��B", MB_OK);
		return;
	}
	TRACE("class: %d module: %d total padfs: %d \n", pDoc->ac, pDoc->am, pm->total_padfs);
	if (pm->total_padfs <= 0)
		return;

	am = pDoc->am;
	width = 0;
	height = 0;
	lpos = pm->vline.padf_list.GetHeadPosition();
	while (lpos) {
		pPadf = (CPadf*)pm->vline.padf_list.GetNext(lpos);
		if (pPadf->type >= PADF_PROCESS && pPadf->type <= PADF_COMMENT) {
			if (width < pPadf->rect.right + 10)
				width = pPadf->rect.right + 10;
			if (height < pPadf->rect.bottom + 10)
				height = pPadf->rect.bottom + 10;
		}
		TRACE("type %d:%d, (%d,%d)-(%d,%d) %s : %s\n", pPadf->type, pPadf->type2, pPadf->rect.left, pPadf->rect.top, pPadf->rect.right, pPadf->rect.bottom, pPadf->str, pPadf->comment);
	}
	CSize sizeTotal;
	// ���̃r���[�̃T�C�Y�̍��v���v�Z���܂��B
	sizeTotal.cx = width;
	sizeTotal.cy = height;
	SetScrollSizes(MM_TEXT, sizeTotal);

	rect.top = pm->vline.sy;
	rect.bottom = pm->vline.ey;
	rect.left = pm->vline.x;
	rect.right = pm->vline.x;
	pm->vline.Draw(pDC, rect);

	myPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	pOldPen = pDC->SelectObject(&myPen);

	lpos = pm->vline.padf_list.GetHeadPosition();
	while (lpos) {
		pPadf = (CPadf*)pm->vline.padf_list.GetNext(lpos);
		if (pPadf == pDoc->pAPadf)	// �A�N�e�B�u�Ȃo�`�c�}�`�Ȃ�`��X�^�C����������T�C�Y�Ɏw�肷��
			rt.m_nStyle = CRectTracker::resizeInside;
		else
			rt.m_nStyle = 0;
		rt.m_rect = pPadf->rect;
		rt.Draw(pDC);
	}
	pDC->SelectObject(pOldPen);
	myPen.DeleteObject();
}

void CVEView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: ���̃r���[�̃T�C�Y�̍��v���v�Z���܂��B
	sizeTotal.cx = 400;
	sizeTotal.cy = 250;
	SetScrollSizes(MM_TEXT, sizeTotal);

    m_toolTip_text = "";

    m_toolTip.Create( this );                          //�c�[���`�b�v�̍쐬
    m_toolTip.AddTool( this, LPSTR_TEXTCALLBACK );
	m_toolTip.SetMaxTipWidth(480);
}

/////////////////////////////////////////////////////////////////////////////
// CVEView �N���X�̈��

BOOL CVEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈������
	return DoPreparePrinting(pInfo);
}

void CVEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CVEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// CVEView �N���X�̐f�f

#ifdef _DEBUG
void CVEView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVEView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVEDoc* CVEView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVEDoc)));
	return (CVEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVEView �N���X�̃��b�Z�[�W �n���h��

void CVEView::OnContextMenu(CWnd*, CPoint point)
{
	CVEDoc* pDoc = GetDocument();
	CPoint client_point;
	CClass* pCls;
	CModule* pMdl;
	CPadf* pPadf;
	POSITION lpos;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if(-1==pDoc->am)
		return;
	pos = GetScrollPosition();
	client_point = point;
	ScreenToClient(&client_point);	// �X�N���[�����W����N���C�A���g���W�֕ϊ�����
	sx=client_point.x;
	sy=client_point.y;
	pMdl=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	if (pDoc->am != -1)
		lpos = pMdl->vline.padf_list.GetHeadPosition();
	while (lpos) {
		pPadf = (CPadf*)pMdl->vline.padf_list.GetNext(lpos);
		rt.m_rect = pPadf->rect;
		rt.m_rect.left -= pos.x;
		rt.m_rect.top -= pos.y;
		rt.m_rect.right -= pos.x;
		rt.m_rect.bottom -= pos.y;
		if (pPadf->type>=PADF_PROCESS && rt.HitTest(client_point)>=0) {
			pDoc->pAPadf = pPadf;
			InvalidateRect(NULL);
			break;
		}
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_VEVIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CVEView::OnUpdateEditCopyCut(CCmdUI* pCmdUI)
{
	// CG: ���̊֐��̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	pCmdUI->Enable(IsSelected());
}

void CVEView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	// CG: ���̊֐��̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	pCmdUI->Enable(::IsClipboardFormatAvailable(m_nClipboardFormat));
}

void CVEView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(IsSelected());	
}

void CVEView::OnEditCopy()
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

void CVEView::OnEditCut()	
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

void CVEView::OnEditPasteP() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
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

void CVEView::OnEditPaste()
{
	CVEDoc* pDoc=GetDocument();
	int i, count, type;
	CClass* pCls;
	CModule* pMdl;
	CPadf* pPadf;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	for(i=0, count=0;i<MAX_PADFS; i++) {
		pMdl = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
//		pPadf = pDoc->GetPadf(pMdl, pDoc->pAPadf);
		type = pPadf->type;
		if(type>=PADF_PROCESS && type<=PADF_REPEAT)
				count++;
	}
	if(0==count) {
		sx=16;
		sy=16;
	} else
		if (pDoc->pAPadf!=NULL) {
			pMdl = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
//			pPadf = pDoc->GetPadf(pMdl, pDoc->pAPadf);
//			sx = pPadf->rect.left;
//			sy = pPadf->rect.bottom + 16;
		}
	CVEView::OnEditPasteP();
}

BOOL CVEView::IsSelected()
{


	// TODO: �R�s�[����ѐ؂��胁�j���[�̗L��/��������I��I�ɍs����悤�ȃR�[�h��ǉ��܂���
	//       �C�����Ă��������B��ȏ�̃A�C�e�����I�����ꂽ�ꍇ�ɂ� TRUE ���A
	//       �I���A�A�C�e�����I������Ă��Ȃ��ꍇ�� FALSE ��Ԃ��܂�

	if (GetDocument()->am!=-1 && GetDocument()->pAPadf!=NULL)
		return TRUE;
	else
		return FALSE;
}

void CVEView::DoCutCopyPaste(CArchive &ar, BOOL bCut)
{
	CVEDoc* pDoc=GetDocument();
	int new_padf_num, am, ap, type, doc_type;
	int center_y;
	unsigned short width, height;
	CClass* pCls;
	CModule* pm;
	CPadf *pPadf, *pAPadf, *pNextPadf;


	// TODO: �I������Ă���f�[�^�� CArchive �I�u�W�F�N�g�o�R�ŃN���b�v�[�h�ւ܂���
	//       �N���b�v�{�[�h����R�s�[����R�[�h��ǉ����Ă��������B����: 
	//       ar.IsStoring() �� TRUE �̏ꍇ�́A�R�s�[�܂��͐؂��葀����Ӗ����܂��B

//	GetDocument()->Serialize(ar);
	pAPadf = pNextPadf = NULL;
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if ((am=pDoc->am)==-1)
		return;
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(am));
	pPadf=pDoc->pAPadf;
//	if(ap!=-1)
//		pAPadf=pDoc->GetPadf(pm,ap);
	if(ar.IsStoring()) {
		if(ap!=-1) {
			ar << (DWORD)1;
			ar << (USHORT)pAPadf->type;
			ar << (USHORT)pAPadf->type2;
			ar << (USHORT)(pAPadf->rect.right - pAPadf->rect.left +1);
			ar << (USHORT)(pAPadf->rect.bottom - pAPadf->rect.top + 1);
			ar << (CString)pAPadf->str;
//			ar << (CString)pAPadf->case_str;
			ar << (USHORT)pAPadf->num_branch;
		}
	} else {
		if(pm->vline.padf_list.GetCount()>=MAX_PADFS) {
			AfxMessageBox("����ȏ�o�`�c�}�`��\��t���ł��܂���");
			return;
		}
		ar >> (DWORD&)doc_type;
		if(doc_type!=1)
			return;
		pPadf=new CPadf();
		new_padf_num=pm->vline.padf_list.GetCount();
		pDoc->SetModifiedFlag();
		ar >> (USHORT&)type;
		ar >> (USHORT&)pPadf->type2;
		ar >> (USHORT&)width;
		ar >> (USHORT&)height;
		ar >> (CString&)pPadf->str;
//		ar >> (CString&)pPadf->case_str;
		ar >> (USHORT&)pPadf->num_branch;

//		pPadf->rect.left = sx;
//		pPadf->rect.top = sy;
//		pPadf->rect.right = sx + width -1;
//		pPadf->rect.bottom = sy + height -1;
		pPadf->num_branch = 0;
		if (ap!=-1) {
//			center_x = (pAPadf->rect.left+pAPadf->rect.right)/2;	// �A�N�e�B�u�}�`�̒��S�ʒu�̂w���W�����߂�
//			center_y = (pAPadf->rect.top+pAPadf->rect.bottom)/2;	// �A�N�e�B�u�}�`�̒��S�ʒu�̂x���W�����߂�
//			prev_p = pAPadf->prev_p;	// �A�N�e�B�u�}�`�̈�O�̐}�`�̔ԍ��𓾂�
//			next_p=pDoc->GetNextPadfNum(pm,ap,0);
			switch(pAPadf->type) { // �A�N�e�B�u�}�`�̃^�C�v�ŕ��򂷂�
			case PADF_PROCESS:	// �A�N�e�B�u�o�`�c�}�`���A�ڂ̎�
//				pPadf->prev_p_pos=0;
//				if(type==PADF_COMMENT) {
//					pPadf->prev_p = -1;
//				} else {
//					pPadf->rect.left= pPadf->rect.left;	// 
//					pPadf->rect.right = pPadf->rect.left + width -1;
//					if(sy>center_y) {
//						pPadf->prev_p=ap;
//						if(next_p!=-1) {
//							pNextPadf=pDoc->GetPadf(pm,next_p);
//							pNextPadf->prev_p=new_padf_num;
//						}
//					} else {	// ��ɒǉ�
//						pPadf->prev_p=prev_p;	// 
//						pPadf->prev_p=new_padf_num;		// 
//					}
//				}
				break;
			case PADF_SELECTION:	// �A�N�e�B�u�o�`�c�}�`���I���̎�
//				if(sx<pAPadf->rect.right) {	// sx���A�N�e�B�u�o�`�c�̉E�[��荶���̎�
//					pPadf->prev_p_pos=0;
//					pPadf->rect.left=pPadf->rect.left;	// 
//					pPadf->rect.right = pPadf->rect.left + width -1;
//					if(sy>center_y) { 
//						pPadf->prev_p=ap;
//					} else {
//						pPadf->prev_p=prev_p;
//						pPadf->prev_p=new_padf_num;
//					}
//				} else {
//					pPadf->prev_p=ap;
//					switch(pAPadf->type2) {
//					case 0: // if
//						if(sy<center_y) {
//							pPadf->prev_p_pos=1;
//							pPadf->case_y=(unsigned short)pPadf->rect.top;
//						} else {
//							pPadf->prev_p_pos=2;
//							pPadf->case_y=(unsigned short)pPadf->rect.bottom;
//						}
//						break;
//					case 1: // switch
//						pPadf->prev_p_pos=pAPadf->num_branch+1;
//						switch(pAPadf->num_branch) {
//						case 0:
//							pPadf->case_y=(unsigned short)pPadf->rect.top;
//							break;
//						case 1:
//							pPadf->case_y=(unsigned short)pPadf->rect.bottom;
//							break;
//						default:
//							pPadf->rect.bottom=(sy+ey)/2;
//							pPadf->case_y=(unsigned short)pPadf->rect.bottom;
//							break;
//						}
//						break;
//					}
//					++pAPadf->num_branch;
//				}
				break;
			case PADF_REPEAT:
				switch(pAPadf->num_branch) {
				case 0: // �E���ɐ}�`���Ȃ��Ȃ�
//					if(sx<pPadf->rect.right) {	// sx���A�N�e�B�u�o�`�c�̉E�[��荶���̎�
//						pPadf->prev_p_pos=0;
//						pPadf->rect.left=pPadf->rect.left;	// �ǉ������}�`�̓A�N�e�B�u�Ȑ}�`�̂w���W�Ɠ����ɂ���
//						pPadf->rect.right = ex = pPadf->rect.left + width -1;
//						if(sy>center_y) {
//							pPadf->prev_p=ap;
//						} else {
//							pPadf->prev_p=prev_p;
//							pPadf->prev_p=new_padf_num;
//							pPadf->prev_p_pos=0;
//						}
//					} else {
//						pPadf->prev_p=ap;
//						pPadf->prev_p_pos=-1;
//						pPadf->num_branch=1;
//					}
					break;
				case 1: // �E���ɐ}�`���P����Ȃ�
					if(sy>center_y) { // ���ɂ���Ȃ�
//						if(pDoc->GetNextPadfNum(pm,ap,0==-1)) {
//							pPadf->prev_p=pDoc->pAPadf;
//							pPadf->prev_p_pos=0;
//						} else {
//							pPadf->prev_p=pDoc->pAPadf;
//						}
					} else { //�@��ɂ���Ȃ�
//						pPadf->prev_p=prev_p;
//						pPadf->prev_p=new_padf_num;
//						pPadf->prev_p_pos=0;
					}
//					pPadf->prev_p_pos=0;
					break;
				}
				break;
			case PADF_COMMENT:	// �R�����g
//				pPadf->prev_p=-1;
				break;
			}
			pPadf->type=type;
//			pDoc->pAPadf=new_padf_num;
		} else {
			if(type==PADF_COMMENT) {
				pPadf->type=type;
//				pDoc->pAPadf=new_padf_num;
			}
		}
		pPadf->num_branch=0;
		pm->vline.padf_list.AddTail((CObject*)pPadf);
	}

	if (bCut)
	{
		ASSERT(ar.IsStoring()); //�؂���A�\��t������͂���܂���

		// TODO: ���ݑI������Ă���A�C�e�����폜���邽�߂ɂ̓R�[�h��ǉ��܂��͒u�������Ă��������B
		CVEView::OnEditDelete();
//		GetDocument()->DeleteContents();
	}

	// �؂���܂��͓\��t������̏ꍇ�A�ύX�ʂ�Ƀr���[����уt���O���X�V���܂�
	if (!(ar.IsStoring() && !bCut))
	{
		GetDocument()->UpdateAllViews(NULL);
		GetDocument()->SetModifiedFlag();
	}
}

void CVEView::OnPadproperty() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������

	// TODO: ���̊֐���ʂ��ăv���W�F�N�g�փA�^�b�`���ꂽ�v���p�e�B
	// �V�[�g�͂ǂ̃��b�Z�[�W �n���h��������t�b�N����Ă��܂���B
	// ���ۂɃv���p�e�B �V�[�g���g�p���邽�߂ɂ́A���̃v���p�e�B��
	// ���j���[ �A�C�e���܂��̓c�[�� �o�[ �{�^���̂悤�ȃv���W�F�N�g
	// ���̃R���g���[���Ɗ֘A�t����K�v������܂��B

	CPadfPropertySheet propSheet;
	int padf_type, padf_type2;

	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClientDC dc(this);
	CClass* pCls;
	CModule* pm;

	// ������ propSheet.DoModal() �� IDOK ��Ԃ����ꍇ�ɁA�v���p�e�B
	// �y�[�W��������擾����ꏊ�ł��B
	// �ȗ����̂��߂����ł͉����s���Ă��܂���B
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if (pDoc->am==-1 || pDoc->pAPadf==NULL || pDoc->pAPadf==NULL)
		return;
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	padf_type = pDoc->pAPadf->type;
	padf_type2 = pDoc->pAPadf->type2;
	propSheet.m_Page1.m_type = cnv_tbl2[padf_type][padf_type2];
	case_flag=FALSE;
	padf_page_mode=1;
	propSheet.m_Page1.m_str = pDoc->pAPadf->str;
	propSheet.m_Page1.m_comment = pDoc->pAPadf->comment;

	if ((propSheet.DoModal()==IDOK) && CheckString(propSheet.m_Page1.m_str)){
		pDoc->SetModifiedFlag();
		pDoc->pAPadf->str=propSheet.m_Page1.m_str;
		pDoc->pAPadf->comment=propSheet.m_Page1.m_comment;
		pDoc->pAPadf->type = cnv_tbl[propSheet.m_Page1.m_type][0];
		pDoc->pAPadf->type2 = cnv_tbl[propSheet.m_Page1.m_type][1];

		CClientDC dc(this);
		CSize size;
		CString str;

		str.Format(padf_msg[pDoc->pAPadf->type][pDoc->pAPadf->type2], propSheet.m_Page1.m_str);
		pDoc->pAPadf->rect.right = pDoc->pAPadf->rect.left + dc.GetTextExtent(str).cx -1;
		switch(pDoc->pAPadf->type){
		case PADF_PROCESS:
			pDoc->pAPadf->rect.right += 8*2;
			break;
		case PADF_SELECTION:
		case PADF_REPEAT:
			pDoc->pAPadf->rect.right += 8*4;
			break;
		case PADF_COMMENT:
			break;
		default:
			AfxMessageBox("�G���[���������܂����B",MB_OK);
			break;
		}
		InvalidateRect(NULL);
	}
}

void CVEView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CVEView::LClick(nFlags, point);
	CScrollView::OnLButtonDown(nFlags, point);
}

void CVEView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	CClass* pCls;
	CModule* pm;
	CPadf* pPadf;
	POSITION lpos;
	
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if(pDoc->am==-1)
		return;
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	if(pm->vline.padf_list.GetCount()==0)
		return;
	pos = GetScrollPosition();
	lpos=pm->vline.padf_list.GetHeadPosition();
	while(lpos) {
		pPadf = (CPadf*)pm->vline.padf_list.GetNext(lpos);
		rt.m_rect = pPadf->rect;
		rt.m_rect.left -= pos.x;
		rt.m_rect.top -= pos.y;
		rt.m_rect.right -= pos.x;
		rt.m_rect.bottom -= pos.y;
		if (pPadf->type>=PADF_PROCESS && pPadf->type<=PADF_COMMENT && rt.HitTest(point)>=0) {
			pDoc->pAPadf=pPadf;
			OnPadproperty();
			InvalidateRect(NULL);
			return;
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}


void CVEView::OnEditDelete() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int num_padfs;
	CClass* pCls;
	CModule *pm;
	CPadf *pPadf, *pPrevPadf;
	POSITION lpos;

	pPadf = NULL;
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
//	if (pDoc->am==-1 || pDoc->pAPadf==-1)
//		return;
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	num_padfs=pm->vline.padf_list.GetCount();

	if(num_padfs>=2) {
		lpos=pm->vline.padf_list.GetHeadPosition();
		while(lpos) {
			pPadf=(CPadf*)pm->vline.padf_list.GetNext(lpos);
//			if(pPadf->prev_p!=-1) {
//				pPrevPadf=pDoc->GetPadf(pm,pPadf->prev_p);
//				if (pPadf->prev_p==pDoc->pAPadf)
//					pPadf->prev_p=pPrevPadf->prev_p;
//			}
		}
		if(prev_p!=-1) {
//			pPrevPadf=pDoc->GetPadf(pm,prev_p);
			if(prev_p != -1) {
				if (pPrevPadf->type >= PADF_SELECTION && pPrevPadf->type <= PADF_REPEAT && pPrevPadf->num_branch > 0) {
					if (!(PADF_SELECTION == pPrevPadf->type && 1 == pPrevPadf->type2)) {
//						for(i=pActPadf->prev_p_pos; i<pPrevPadf->num_branch-1; i++) {
//							pPadf=pDoc->GetPadf(pm,pDoc->GetNextPadfNum(pm,prev_p,i));
//							pNextPadf=pDoc->GetPadf(pm,pDoc->GetNextPadfNum(pm,prev_p,i+1));
//							pPadf->case_y=pNextPadf->case_y;
//							pPadf->prev_p_pos--;
//							pNextPadf->prev_p_pos--;
					} else {
//						if (pPrevPadf->prev_p_pos!=0)
//							pPadf->prev_p_pos=pPrevPadf->prev_p_pos;
						pPrevPadf->num_branch--;
					}
				}
			}
		}
	}
//	delete pDoc->GetPadf(pm,pDoc->pAPadf);
//	pm->padf.RemoveAt(pm->padf.FindIndex(pDoc->pAPadf));
	pDoc->pAPadf = NULL;
	InvalidateRect(NULL);
}

void CVEView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	int sx, sy, ex, ey;
	CPoint client_point;
	CVEDoc* pDoc = GetDocument();
	CClass* pCls;
	CModule* pm;
	CPadf *pPadf;
	CRect rect;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if(pDoc->am==-1)
		return;
	ASSERT_VALID(pDoc);
	GetClientRect(&rect);
	switch(nChar) {
	case 'P':	// process
		InsertPadf2(PADF_PROCESS,0,1);
		return;
		break;
	case 'I':	// if
		InsertPadf2(PADF_SELECTION,0,1);
		return;
		break;
	case 'S':	// switch
		InsertPadf2(PADF_SELECTION,1,1);
		return;
		break;
	case 'F':	// for
		InsertPadf2(PADF_REPEAT,0,1);
		return;
		break;
	case 'W':	// while
		InsertPadf2(PADF_REPEAT,1,1);
		return;
		break;
	case 'D':	// do while
		InsertPadf2(PADF_REPEAT,2,1);
		return;
		break;
	case 'C':	// comment
		InsertPadf2(PADF_COMMENT,0,1);
		return;
		break;
	default:
		break;
	}
	if (pDoc->pAPadf==NULL) {
		CPoint pos;
		GetCursorPos(&pos); // Windows API ���ӁI�@���̂`�o�h�œ�������W�̓N���C�A���g���W�ł͂Ȃ��X�N���[�����W�ł��B
		switch (nChar) {
		case VK_LEFT:
			pos.x-=8;
			break;
		case VK_RIGHT:
			pos.x+=8;
			break;
		case VK_UP:
			pos.y-=8;
			break;
		case VK_DOWN:
			pos.y+=8;
			break;
		case VK_RETURN:
			client_point = pos;
			ScreenToClient(&client_point);	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
			LClick((UINT)0, client_point);	// ���N���b�N�Ɠ���
			return;
			break;
		case VK_CONTROL:
			return;
			break;
		default:
			MessageBeep(0);
			break;
		}
		SetCursorPos(pos.x,pos.y);	// Windows API
		return;
	}
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	pPadf=pDoc->pAPadf;
	sx=pPadf->rect.left;
	sy=pPadf->rect.top;
	ex=pPadf->rect.right;
	ey=pPadf->rect.bottom;
	switch (nChar) {
	case VK_LEFT:
		if(sx>16) {
			sx--;
			ex--;
		}
		break;
	case VK_RIGHT:
		if(ex<rect.right){
			sx++;
			ex++;
		}
		break;
	case VK_UP:
		if(sy>16) {
			sy--;
			ey--;
		}
		break;
	case VK_DOWN:
		if(ey<rect.bottom) {
			sy++;
			ey++;
		}
		break;
	case VK_RETURN:
		CVEView::OnPadproperty();
		CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
		break;
	case VK_ESCAPE:
		pDoc->pAPadf=NULL;
		InvalidateRect(NULL);
		CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
		break;
	case VK_CONTROL:
		return;
		break;
	default:
		MessageBeep(0);
		return;
		break;
	}
	if(sx < 16)
		sx = 16;
	if(ex < 16)
		ex = 16;
	if(sy < 16)
		sy = 16;
	if(ey < 16)
		ey = 16;
	pPadf->rect.left=sx;
	pPadf->rect.top=sy;
	pPadf->rect.right=ex;
	pPadf->rect.bottom=ey;
	InvalidateRect(NULL);

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CVEView::OnInsertPadf(void) // ���j���[�o�[����̑}��
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	InsertPadf2(PADF_PROCESS,0,0);
}

void CVEView::OnUpdateInsertPadf(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();

	if(pDoc->am!=-1)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CVEView::InsertPadf(int type1 = PADF_PROCESS, int type2 = 0, int mode = 0) // �o�`�c�}�`��R�����g�̑}��
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CPadfPropertySheet propSheet;

	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int center_x, center_y, type, new_padf_num, padf_xsize, padf_ysize;
	CClass* pCls;
	CModule* pm;
	CPadf *pPadf;
	// ������ propSheet.DoModal() �� IDOK ��Ԃ����ꍇ�ɁA�v���p�e�B
	// �y�[�W��������擾����ꏊ�ł��B
	// �ȗ����̂��߂����ł͉����s���Ă��܂���B
	if (pDoc->ac<0 || pDoc->ac >= pDoc->cls.GetCount())
		return;
	pCls = (CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if (pCls->type == CLSTYPE_UNION)
		return;
	if (pDoc->am == -1)
		return;
	pm = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	if (pm->total_padfs >= MAX_PADFS) {
		MessageBeep(0);
		AfxMessageBox("����ȏ�o�`�c�}�`��R�����g��ǉ��ł��܂���B");
		return;
	}
	propSheet.m_Page1.m_type = cnv_tbl2[type1][type2];	// 0=����
	propSheet.m_Page1.m_str = "";
	propSheet.m_Page1.m_comment = "";
//	propSheet.m_Page1.m_case.SetWindowText("");
	case_flag = FALSE;
	if (pDoc->pAPadf != NULL) {
		center_x = (pDoc->pAPadf->rect.left + pDoc->pAPadf->rect.right) / 2;	// �A�N�e�B�u�}�`�̒��S�ʒu�̂w���W�����߂�
		center_y = (pDoc->pAPadf->rect.top + pDoc->pAPadf->rect.bottom) / 2;	// �A�N�e�B�u�}�`�̒��S�ʒu�̂x���W�����߂�
		if (pDoc->pAPadf->type == PADF_SELECTION && pDoc->pAPadf->type2 == 1 && pDoc->pAPadf->rect.right <= sx)
			case_flag = TRUE;
	}
	padf_page_mode = mode;

	if (propSheet.DoModal() == IDOK && CheckString(propSheet.m_Page1.m_str)) {
		CClientDC dc(this);
		CSize size;
		CString string;

		pDoc->SetModifiedFlag();
		pPadf = new CPadf();
		pPadf->str = propSheet.m_Page1.m_str;
		new_padf_num = pm->vline.padf_list.GetCount();
		pPadf->type = type = cnv_tbl[propSheet.m_Page1.m_type][0];
		pPadf->type2 = cnv_tbl[propSheet.m_Page1.m_type][1];
		sx = pm->vline.x;
		if (sx<16)
			sx = 16;
		pPadf->rect.left = sx;
		if (sy<16)
			sy = 16;
		pPadf->rect.top = sy;
		string.Format(padf_msg[pPadf->type][pPadf->type2], pPadf->str);
		size = dc.GetTextExtent(string);
		padf_xsize = size.cx;
		padf_ysize = PADF_HEIGHT;
		pPadf->comment = propSheet.m_Page1.m_comment;
		switch (type) { // �}������o�`�c�}�`�̃^�C�v�ɂ���ĕ��򂷂�
		case PADF_PROCESS: // �A��
			padf_xsize += 8 * 2;
			break;
		case PADF_SELECTION:	// �I��
			padf_xsize += 8 * 4;
			padf_ysize = 16 * 3;
			break;
		case PADF_REPEAT:	// ����
			padf_xsize += 8 * 4;
			break;
		case PADF_COMMENT: // �R�����g
			break;
		default:
			AfxMessageBox("���̃v���O�����ɂ͕s�������܂��B");
			return;
		}
		pPadf->rect.right = ex = sx + padf_xsize - 1;
		pPadf->rect.bottom = ey = sy + padf_ysize - 1;
		if (pDoc->pAPadf != NULL) {
			switch (pDoc->pAPadf->type) { // �A�N�e�B�u�}�`�̃^�C�v�ŕ��򂷂�
			case PADF_PROCESS:	// �A�N�e�B�u�o�`�c�}�`���A�ڂ̎�
				pPadf->rect.left = pDoc->pAPadf->rect.left;	// 
				pPadf->rect.right = ex = pPadf->rect.left + padf_xsize;
				switch (type) { // �}������o�`�c�}�`�̃^�C�v�ɂ���ĕ��򂷂�
				case PADF_PROCESS: // �A��
					pPadf->rect.right = pPadf->rect.left + padf_xsize - 1;
					break;
				case PADF_SELECTION:	// �I��
					pPadf->rect.right = pPadf->rect.left + padf_xsize - 1;
					pPadf->rect.bottom = pPadf->rect.top + padf_ysize - 1;
					break;
				case PADF_REPEAT:	// ����
					pPadf->rect.right = pPadf->rect.left + padf_xsize - 1;
					break;
				case PADF_COMMENT: // �R�����g
					break;
				default:
					AfxMessageBox("���̃v���O�����ɂ͕s�������܂��B");
					return;
				}
				if (sy > center_y) {
					pPadf->rect.top = pDoc->pAPadf->rect.bottom + 16;
					pPadf->rect.bottom = pPadf->rect.top + padf_ysize;
					if (type != PADF_COMMENT) { // �A�N�e�B�u�o�`�c�}�`�̉��ɂo�`�c�}�`��ǉ�������
												//						pPadf->prev_p=pDoc->pAPadf;
					}
				} else {	// ��ɒǉ�
					pPadf->rect.bottom = pDoc->pAPadf->rect.top - 16;
					pPadf->rect.right = ex = sx + padf_xsize - 1;
					pPadf->rect.bottom = ey = sy + padf_ysize - 1;
					switch (pPadf->type) {
					case PADF_PROCESS: // �A��
						break;
					case PADF_SELECTION:	// �I��
						break;
					case PADF_REPEAT:	// ����
						break;
					case PADF_COMMENT: // �R�����g
						break;
					default:
						AfxMessageBox("���̃v���O�����ɂ͕s�������܂��B");
						return;
					}
					if (pPadf->type != PADF_COMMENT) {
						// �A�N�e�B�u�o�`�c�}�`�̏�ɂo�`�c�}�`��ǉ�������
					}
				}
				break;
			case PADF_SELECTION:	// �A�N�e�B�u�o�`�c�}�`���I���̎�
				if ((0 == pDoc->pAPadf->type2 && 2 == pDoc->pAPadf->num_branch) || sx < center_x) {	// �|�C���^��������荶���̎�
					if (sy > center_y) { //�|�C���^�����S��艺�̏ꍇ
 //						if(next_p != -1)
					}
					else {
					}
				} else {
					switch (pDoc->pAPadf->type2) { // if��switch���ŕ���
					case 0: // if�i�Q���j
						if (pDoc->pAPadf->num_branch < 2) {
							if (sy < center_y) {
//								pPadf->case_y=(unsigned short)pAPadf->rect.top;
							} else {
//								pPadf->prev_p_pos=2;
//								pPadf->case_y=(unsigned short)pAPadf->rect.bottom;
							}
						}
						break;
					case 1: // switch�i�����I���j
	//					pPadf->prev_p_pos=pAPadf->num_branch+1;
		//				pPadf->case_y=(unsigned short)(pPadf->rect.top+pPadf->rect.bottom)/2;
						switch (pDoc->pAPadf->num_branch) {
						case 0:	// �Ȃ��ꍇ
							break;
						case 1:	// �ЂƂ���ꍇ
							break;
						default:
//							if(pAPadf->rect.bottom < pPadf->case_y)
//								pAPadf->rect.bottom=pPadf->case_y;
							break;
						}
						break;
					}
					++pDoc->pAPadf->num_branch;
				}
				break;
			case PADF_REPEAT:
				switch (pPadf->num_branch) {
				case 0: // �E���ɐ}�`���Ȃ��Ȃ�
					if (sx < center_x) {	// �}�E�X�J�[�\�����A�N�e�B�u�}�`�̒�����荶�Ȃ�
	//					pPadf->prev_p_pos=0;
	//					pPadf->rect.left=pPadf->rect.left;	// �ǉ������}�`�̓A�N�e�B�u�Ȑ}�`�̂w���W�Ɠ����ɂ���
	//					pPadf->rect.right = ex = pPadf->rect.left + padf_xsize;
						if (sy > center_y) {
						}
						else {
						}
					}
					else {
						pPadf->num_branch = 1;
					}
					break;
				}
				break;
			case PADF_COMMENT:	// �R�����g
				break;
			}
		}
		pm->vline.padf_list.AddTail((CObject*)pPadf);
		if (0 == pm->total_padfs)
			pm->vline.sy = pPadf->rect.top;
		pm->vline.ey = pPadf->rect.bottom;
		pDoc->pAPadf = pPadf;
		pm->total_padfs++;
		InvalidateRect(NULL);
	}
}

void CVEView::LClick(UINT nFlags, CPoint point)
{
	CVEDoc* pDoc = GetDocument();
	CClass* pCls;
	CModule* pm;
	CPadf *pPadf, *pPrevPadf;
	CClientDC dc(this);
	CString string;
	bool ctrl_flag;
	int move_x, move_y;
	
	pPrevPadf = NULL;
	if(pDoc->ac <0 || pDoc->ac >= pDoc->cls.GetCount())
		return;
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if (pDoc->am==-1)
		return;
	pos = GetScrollPosition();
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	if(nFlags & MK_CONTROL)
		ctrl_flag=true;
	else
		ctrl_flag=false;
	POSITION lpos=pm->vline.padf_list.GetHeadPosition();
	while(lpos) {
		pPadf=(CPadf*)pm->vline.padf_list.GetNext(lpos);
		if (pPadf->type>=PADF_PROCESS && pPadf->type<=PADF_COMMENT) {
			rt.m_rect = pPadf->rect;
			rt.m_rect.left -= pos.x;
			rt.m_rect.top -= pos.y;
			rt.m_rect.right -= pos.x;
			rt.m_rect.bottom -= pos.y;
			if (rt.HitTest(point)>=0 && nFlags & MK_LBUTTON) {
				rt.Track(this,point,FALSE);
				move_x = rt.m_rect.left + pos.x - pPadf->rect.left;
				move_y = rt.m_rect.top + pos.y - pPadf->rect.top;
				pPadf->rect.top = rt.m_rect.top + pos.y;
				pPadf->rect.bottom = rt.m_rect.bottom + pos.y;
				pPadf->rect.left = rt.m_rect.left + pos.x;
//				if(pPadf->prev_p!=-1)
//					pPrevPadf=pDoc->GetPadf(pm,pPadf->prev_p);
//				if(pPadf->prev_p_pos!=0) {
//					pPadf->rect.left = rt.m_rect.left + pos.x;
//					pPadf->rect.right = rt.m_rect.right + pos.x;
//					if(ctrl_flag && pPadf->prev_p != -1 && pPrevPadf->num_branch!=pPadf->prev_p_pos)
//						pPadf->case_y += (WORD)pPadf->rect.top - (WORD)local_rect.top;
//				} else {
//					if(pPadf->prev_p!=-1) { // ��ԍŏ��̂o�`�c�łȂ����
//						if(PADF_SELECTION==pPrevPadf->type && 1==pPrevPadf->type2) {
//							if(pDoc->GetNextPadfNum(pm,i,0)==-1)
//								pPadf->case_y= (WORD)((pPadf->rect.top+pPadf->rect.bottom)/2);
//							if(pPrevPadf->num_branch==pPadf->prev_p_pos)
//								pPadf->case_y= (WORD)pPrevPadf->rect.bottom;
//						}
//						pPadf->rect.left = pPrevPadf->rect.left;
//					}
//				}
				if (pPadf->rect.left<16)
					pPadf->rect.left = 16;
				if (pPadf->rect.top<16)
					pPadf->rect.top = 16;
				string.Format(padf_msg[pPadf->type][pPadf->type2], pPadf->str);
				pPadf->rect.right=pPadf->rect.left + dc.GetTextExtent(string).cx -1;
				switch(pPadf->type) {
				case 0: // �A��
					pPadf->rect.right += 8*2;
					break;
				case 1:	// �I��
				case 2:	// ����
					pPadf->rect.right += 8*4;
					break;
				case 3: // �R�����g
					pPadf->rect.bottom = pPadf->rect.top + COMMENT_HEIGHT;
				break;
				}
//				MoveUnderPadf(i, move_x, move_y);
				pDoc->pAPadf = pPadf;
				InvalidateRect(NULL);
				pDoc->UpdateAllViews(NULL);
				return;
			}
		}
	}
	sx=point.x;
	sy=point.y;
	if(pDoc->pAPadf != NULL || 0==pm->vline.padf_list.GetCount())
		InsertPadf(PADF_PROCESS,0,0);
	else
		InsertPadf(PADF_COMMENT, 0, 0);
//	pDoc->pAPadf = pPadf;
}

BOOL CVEView::CheckString(CString& str)
{
	int i, len, start;
	CString str2;
	
	CVEDoc* pDoc=GetDocument();
	POSITION pos;
	CClass* pCls;
	CModule* pMdl;
	int mdl;

	len=str.GetLength();
	if(0==len) {
		AfxMessageBox("�������͂���Ă��܂���",MB_OK);
		return FALSE;
	}
	return TRUE;	// �b��I�ɂ������܂�

	for(i=0; i<len; ) {
		i=SkipSpace(str, i, len);	// �X�y�[�X���΂��܂�
		if(i==-1)
			return FALSE;
		start=i;
		if(isalpha(str[i])) {
			i++;
			while(isalnum(str[i]))
				i++;
			str2=str.Mid(start,i-start);
			if('('==str[i]) {
				i++;
				mdl=0;
				pos=pCls->mdl.GetHeadPosition();
				while(pos) {
					pMdl=(CModule*)pCls->mdl.GetNext(pos);
					if(str2==pMdl->name) {
						while(str[i]!=')' && i<len)
							i++;
						return TRUE;
					}
					mdl++;
				}
				if(pCls->mdl.GetCount()==mdl) {
					AfxMessageBox("���W���[���E�c���[�ɓo�^����Ă��Ȃ����W���[�����Ăяo���Ă��܂��B�֐���ǉ����Ă��������B",MB_OK);
					return FALSE;
				}
			} else {
				i=SkipSpace(str, i, len);
				if(-1==i) {
					AfxMessageBox("���@�Ɍ�肪����܂��B",MB_OK);
					return FALSE;
				}
				if('='==str[i]) {
					i++;
					i=SkipSpace(str, i, len);
					if(-1==i) {
						AfxMessageBox("���@�Ɍ�肪����܂��B",MB_OK);
						return FALSE;
					}
					return TRUE;
				} else {
					AfxMessageBox("���@�Ɍ�肪����܂��B",MB_OK);
					return FALSE;
				}
			}
		} else {
			if(!('*'==str[i] || str.Mid(i,2)=="++" || str.Mid(i,2)=="--")) {
				AfxMessageBox("�擪�ɗ���͕̂ϐ���֐�������̉��Z�q�����ł��B",MB_OK);
				return FALSE;
			}
		}
	}
	return TRUE;
}


int CVEView::SkipSpace(CString& str, int i, int len)
{
	if(i>=len)
		return -1;
	while(isspace(str[i]))
		i++;
	if(i>=len)
		return -1;
	return i;
}


void CVEView::InsertPadf2(int type1, int type2, int mode)
{
	CVEDoc* pDoc = GetDocument();
	int count;
	CClass* pCls;
	CModule* pm;
	CPadf* pPadf;
	POSITION lpos;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	lpos=pm->vline.padf_list.GetHeadPosition();
	count=0;
	while(lpos) {
		pPadf=(CPadf*)pm->vline.padf_list.GetNext(lpos);
		if(pPadf->type>=PADF_PROCESS && pPadf->type<=PADF_REPEAT)
			count++;
	}
	if(0==count) {
		sx=16;
		sy=16;
		InsertPadf(type1,type2,mode);
	} else
		if (pDoc->pAPadf==NULL) {
			pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
			pPadf=pDoc->pAPadf;
			sx = pPadf->rect.left;
			sy = pPadf->rect.bottom + 16;
			InsertPadf(type1,type2,mode);
		}
}

void CVEView::OnInsertProcess() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	InsertPadf2(PADF_PROCESS, 0, 1);
}

void CVEView::OnInsertIf() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	InsertPadf2(PADF_SELECTION, 0, 1);
}

void CVEView::OnInsertSwitch() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	InsertPadf2(PADF_SELECTION, 1, 1);
}

void CVEView::OnInsertFor() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	InsertPadf2(PADF_REPEAT, 0, 1);
}

void CVEView::OnInsertWhile() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	InsertPadf2(PADF_REPEAT, 1, 1);
}

void CVEView::OnInsertDoWhile() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	InsertPadf2(PADF_REPEAT, 2, 1);
}

void CVEView::OnInsertComment() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	InsertPadf2(PADF_COMMENT, 0, 1);
}

void CVEView::OnUpdatePadproperty(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();

	pCmdUI->Enable(pDoc->am!=-1 && pDoc->pAPadf==NULL);
}

void CVEView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	CClass* pCls;
	CModule* pm;
	CPadf *pPadf;
	CString str;
	
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if (pDoc->am==-1)
		return;
	GetParentFrame()->SetActiveView(this, FALSE);	// ���̃r���[���A�N�e�B�u�ɂ���
	pos = GetScrollPosition();
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	POSITION lpos=pm->vline.padf_list.GetHeadPosition();
	while(lpos) {
		pPadf=(CPadf*)pm->vline.padf_list.GetNext(lpos);
		if (pPadf->type>=PADF_PROCESS && pPadf->type<=PADF_REPEAT) {
			rt.m_rect = pPadf->rect;
			rt.m_rect.left -= pos.x;
			rt.m_rect.top -= pos.y;
			rt.m_rect.right -= pos.x;
			rt.m_rect.bottom -= pos.y;
			if (rt.HitTest(point)>=0) {
		        m_toolTip_text.Format("%s", pPadf->comment);
			    m_toolTip.Update();
				return;
			}
		}
	}
	m_toolTip_text=type_tbl[pm->ret_type];
	for(int i=0; i<pm->ret_pointer; i++)
		m_toolTip_text+="*";
	m_toolTip_text += " " + pm->name + "(" + pm->arg + ") \r\n" + pm->comment + "\r\n�o�`�c�}�`�Ƌ�`�R�����g�F";
	str.Format("%d\r\n���[�J���ϐ��F%d", pm->vline.padf_list.GetCount(), pm->var.GetCount());
	m_toolTip_text += str;
	str.Format("\r\n�O���[�o���ϐ��F%d", pCls->var.GetCount());
	m_toolTip_text += str;
    m_toolTip.Update();
//	m_toolTip.Pop();
	CScrollView::OnMouseMove(nFlags, point);
}

BOOL CVEView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
    m_toolTip.RelayEvent( pMsg );
	return CScrollView::PreTranslateMessage(pMsg);	
}

void CVEView::OnTipsDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMTTDISPINFO lpttd;

	if ( m_toolTip_text != "" ) {              // �c�[���`�b�v�̓��e��\��
		lpttd = (LPNMTTDISPINFO)pNMHDR;
		lpttd->lpszText = (LPSTR)(LPCTSTR)m_toolTip_text;
    }

    *pResult = 0;
}
void CVEView::OnViewAdjust() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClass* pCls;
	CModule* pMdl;
	CPadf *pPadf;
	POSITION lpos2;
	int pad;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	pMdl=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	if(pMdl->vline.padf_list.GetCount()) { // ���W���[���ɂo�`�c�}�`�Ȃǂ����邩�ǂ���
		lpos2=pMdl->vline.padf_list.GetHeadPosition();
		while(lpos2) {
			pPadf = (CPadf*)pMdl->vline.padf_list.GetNext(lpos2);
			if (pPadf->type>=PADF_PROCESS && pPadf->type<=PADF_REPEAT)
				break;
		}
		CVEView::Adjust(pMdl,pad);	// pMdl�����W���[���̃A�h���X�Ap���o�`�c�A�P���C���f���g
	}
	InvalidateRect(NULL, TRUE);
}

void CVEView::Adjust(CModule* pMdl, int p)
{
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int next_p;
	BOOL do_while_flag=FALSE;
	CPadf *pPadf;
	
//	pPadf = pDoc->GetPadf(pMdl,p);
//	if (pPadf->type>=PADF_PROCESS && pPadf->type<=PADF_COMMENT && pPadf->prev_p != -1 && 0==pPadf->prev_p_pos) {
//		pPrevPadf = pDoc->GetPadf(pMdl, pPadf->prev_p);
//		diff = pPrevPadf->rect.left - pPadf->rect.left;
//		if(diff!=0) {
//			pPadf->rect.left += diff;
//			pPadf->rect.right += diff;
//		}
//	}
//	next_p = pDoc->GetNextPadfNum(pMdl,p,0);	// ���̂o�`�c�}�`�̔ԍ��𓾂�
	switch(pPadf->type) {	// �o�`�c�}�`�̎�ނ𓾂� */
	case PADF_PROCESS:	// ����
		break;
	case PADF_SELECTION:	// �I��
		if(pPadf->num_branch>0) {
			switch(pPadf->type2) {
			case 0:	// if��
//				if(-1!=(pad_num=pDoc->GetNextPadfNum(pMdl,p,1))) {
//					Adjust(pMdl,pad_num);
//				}
//				if(-1!=(pad_num=pDoc->GetNextPadfNum(pMdl,p,2))) {
//					Adjust(pMdl,pad_num);
//				}
				break;
			case 1:	// switch��
				for(int pos=1; pos<=pPadf->num_branch; pos++) {
//					if(-1!=(pad_num=pDoc->GetNextPadfNum(pMdl,p,pos))) {
//						pNextPadf=pDoc->GetPadf(pMdl,pad_num);
//						Adjust(pMdl,pad_num);
//					}
				}
				break;
			}
		}
		break;
	case PADF_REPEAT:	// ����
//		if((pad_num=pDoc->GetNextPadfNum(pMdl,p,-1))!=-1) {
//			Adjust(pMdl,pad_num);
//		}
		break;
	}
	if(next_p != -1) {
		Adjust(pMdl, next_p);
	}
}



void CVEView::MoveUnderPadf(int padf_num, int move_x, int move_y)
{
	CVEDoc* pDoc = GetDocument();
	CClass* pCls;
	CModule* pm;
	CPadf *pPadf, *pPrevPadf;
	CClientDC dc(this);
	
	if(pDoc->ac <0 || pDoc->ac >= pDoc->cls.GetCount())
		return;
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if (pDoc->am==-1)
		return;
	pos = GetScrollPosition();
	pm=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
	pPrevPadf=(CPadf*)pm->vline.padf_list.GetAt(pm->vline.padf_list.FindIndex(padf_num));
	int i=0;
	POSITION lpos=pm->vline.padf_list.GetHeadPosition();
	while(lpos) {
		pPadf=(CPadf*)pm->vline.padf_list.GetNext(lpos);
//		if (pPadf->prev_p==padf_num) {
//			pPadf->rect.left += move_x;
//			pPadf->rect.right += move_x;
		//	pPadf->rect.top += move_y;
		//	pPadf->rect.bottom += move_y;
			if(pPrevPadf->type==PADF_SELECTION && pPrevPadf->type2==1)
		//		pPadf->case_y += move_y;
//			MoveUnderPadf(i, move_x, move_y);
//		}
		i++;
	}
}
