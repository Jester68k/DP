// ClassView.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "VE.h"
#include "VEDoc.h"
#include "Class.h"
#include "ClassDlg.h"
#include "ClassView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassView

IMPLEMENT_DYNCREATE(CClassView, CListView)

CClassView::CClassView()
{
	// CG: ���̍s�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
	m_nClipboardFormat = ::RegisterClipboardFormat(_T("CLS"));
}

CClassView::~CClassView()
{
}


BEGIN_MESSAGE_MAP(CClassView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CClassView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_INSERT_CLS, OnInsertCls)
	ON_COMMAND(ID_CLS_PROPERTY, OnClsProperty)
	ON_UPDATE_COMMAND_UI(ID_CLS_PROPERTY, OnUpdateClsProperty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView �`��

void CClassView::OnDraw(CDC* pDC)
{
	// TODO: ���̈ʒu�ɕ`��p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClassView::SetListItems();
}


/////////////////////////////////////////////////////////////////////////////
// CClassView �f�f

#ifdef _DEBUG
void CClassView::AssertValid() const
{
	CListView::AssertValid();
}

void CClassView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CVEDoc* CClassView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVEDoc)));
	return (CVEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClassView ���b�Z�[�W �n���h��
BOOL CClassView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_SINGLESEL ;
	return CListView::PreCreateWindow(cs);
}

void CClassView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CListCtrl&	listCtrl = GetListCtrl();
	LVCOLUMN lvcol;
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	lvcol.iSubItem = 0;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvcol.pszText = "���";
	lvcol.cx = 60;
	listCtrl.InsertColumn(0, &lvcol);

	lvcol.iSubItem = 1;
	lvcol.pszText = "���O";
	lvcol.cx = 140;
	listCtrl.InsertColumn(1, &lvcol);

	CClassView::SetListItems();
}

void CClassView::SetListItems()
{
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl&	listCtrl = GetListCtrl();
	LVITEM	lvi;
	int index=0;
	POSITION m_pos;
	CClass* pCls;
	CString str;

	listCtrl.DeleteAllItems();
	lvi.mask = LVIF_TEXT;

	m_pos=pDoc->cls.GetHeadPosition();
	while(m_pos) {
		pCls = (CClass*)pDoc->cls.GetNext(m_pos);
		lvi.iItem= index;
		lvi.iSubItem = 0;
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(clstype_tbl[pCls->type]));
		index = listCtrl.InsertItem( &lvi );
		lvi.iItem = index;
		lvi.iSubItem = 1;
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pCls->name));
		listCtrl.SetItem(&lvi);
		index++;
	}
	listCtrl.SetHoverTime(1);
}

void CClassView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	CClassDlg clsdlg;
	int index;
	index = listCtrl.HitTest(point);

	if(index>-1) {
		if (index < pDoc->cls.GetCount()) {
			pDoc->ac=index;
			InvalidateRect(NULL,FALSE);
			pDoc->UpdateAllViews(NULL);
		}
	} else {
		CClassView::OnInsertCls();
	}
	CListView::OnLButtonDown(nFlags, point);
}

void CClassView::OnClsPropertyCommon(int index)
{
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClassDlg clsdlg;
	CClass* pCls;

	if(index >= 0 && index<pDoc->cls.GetCount()) {
		pCls = (CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(index));
		clsdlg.m_type = pCls->type;
		clsdlg.m_name = pCls->name;
		clsdlg.m_accesstype = pCls->acctype;
		clsdlg.m_baseclass = pCls->basecls;
		clsdlg.m_friendclass = pCls->friendcls;
		clsdlg.m_numvar = pCls->var.GetCount();
		clsdlg.m_numfunc = pCls->mdl.GetCount();
		if(clsdlg.DoModal()==IDOK) {
			if(0==index) {
				clsdlg.m_type = CLSTYPE_GLOBAL;
				clsdlg.m_name = "";
			} else 
				if(CheckClassName(clsdlg.m_name))
					return;
			pCls->SetValue(clsdlg.m_type, clsdlg.m_name, clsdlg.m_accesstype, clsdlg.m_baseclass, clsdlg.m_friendclass);
			pDoc->SetModifiedFlag();
			CClassView::SetListItems();
			InvalidateRect(NULL,FALSE);
			pDoc->UpdateAllViews(NULL);
		}
	}
}

void CClassView::OnInsertCls()
{
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl&	listCtrl = GetListCtrl();
	CClassDlg clsdlg;
	CClass *pCls, *pSearchCls;
	int num;

	clsdlg.m_type = CLSTYPE_CLASS;
	clsdlg.m_name = "";
	clsdlg.m_accesstype = AT_PUBLIC;
	clsdlg.m_baseclass = "";
	clsdlg.m_friendclass = "";
	if(IDOK==clsdlg.DoModal() && !CheckClassName(clsdlg.m_name)) {
		if(CLSTYPE_GLOBAL == clsdlg.m_type) {
			AfxMessageBox("�O���[�o���͂P�����ł��B",MB_OK);
			return;
		}
		for(num=0; num<pDoc->cls.GetCount(); num++) {
			pSearchCls=(CClass*)(pDoc->cls.GetAt(pDoc->cls.FindIndex(num)));
			if(clsdlg.m_type == pSearchCls->type && clsdlg.m_name == pSearchCls->name) {// ������ނƖ��O�Ȃ�return
				AfxMessageBox("������ނœ������O�̂��̂�����܂��B",MB_OK);
				return;
			}
		}
		pCls = new CClass();
		pCls->SetValue(clsdlg.m_type, clsdlg.m_name, clsdlg.m_accesstype, clsdlg.m_baseclass, clsdlg.m_friendclass);
		pDoc->am = -1;
		pDoc->pAPadf = NULL;
		for(num=0; num<pDoc->cls.GetCount(); num++) {
			pSearchCls=(CClass*)(pDoc->cls.GetAt(pDoc->cls.FindIndex(num)));
			if(clsdlg.m_type < pSearchCls->type) {
				pDoc->cls.InsertBefore(pDoc->cls.FindIndex(num), (CObject*)pCls);	// �N���X���}������J�E���g���P������
				pDoc->ac = num;
				goto jump;
			}
		}
		pDoc->ac = pDoc->cls.GetCount();
		pDoc->cls.AddTail((CObject*)pCls);	// �N���X�������ɒǉ�����J�E���g���P������
		jump:
		pDoc->SetModifiedFlag();
		CClassView::SetListItems();
		InvalidateRect(NULL,FALSE);
		pDoc->UpdateAllViews(NULL);
	}
}

BOOL CClassView::CheckClassName(CString str)
{
	BOOL array_cnt=0;

	if(str.GetLength()==0) {
//		AfxMessageBox("���O�����͂���Ă��܂���B",MB_OK);
		MessageBeep(MB_OK);
		return TRUE;
	}
	if(isdigit(str[0])) {
		AfxMessageBox("���O�̐擪�ɐ����͎g���܂���B",MB_OK);
		return TRUE;
	}
	for(int i=0; i<str.GetLength(); i++) {
		if(!(isalnum(str[i]) || str[i]=='_')) {
			AfxMessageBox("�p������'_'�i�A���_�[�X�R�A�j�ł���K�v������܂��B",MB_OK);
			return TRUE;
		}
	}
	return FALSE;
}

void CClassView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl&	listCtrl = GetListCtrl();
	CClassDlg clsdlg;
	int index;

	index = listCtrl.HitTest(point);
	if (index >= 0 && index < pDoc->cls.GetCount())
		CClassView::OnClsPropertyCommon(index);
	
	CListView::OnLButtonDblClk(nFlags, point);
}

void CClassView::OnContextMenu(CWnd*, CPoint point)
{

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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_CLASS_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

//DEL void CClassView::OnUpdateEditCopyCut(CCmdUI* pCmdUI)
//DEL {
//DEL 	// CG: ���̊֐��̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
//DEL 	pCmdUI->Enable(IsSelected());
//DEL }

//DEL void CClassView::OnUpdateEditPaste(CCmdUI* pCmdUI)
//DEL {
//DEL 	// CG: ���̊֐��̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
//DEL 	pCmdUI->Enable(::IsClipboardFormatAvailable(m_nClipboardFormat));
//DEL }

//DEL void CClassView::OnEditCopy()
//DEL {
//DEL 	// CG: ���̃u���b�N�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
//DEL 	{
//DEL 		CSharedFile	memFile;
//DEL 		CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);
//DEL 
//DEL 		// �V���A���C�Y �f�[�^���A�[�J�C�u �I�u�W�F�N�g��
//DEL 		DoCutCopyPaste(ar, FALSE);
//DEL 
//DEL 		ar.Flush();
//DEL 
//DEL 		HGLOBAL hData = memFile.Detach();
//DEL 		if (OpenClipboard())
//DEL 		{
//DEL 			::SetClipboardData(m_nClipboardFormat, hData);
//DEL 			CloseClipboard();
//DEL 		}
//DEL 		else
//DEL 			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
//DEL 	}
//DEL }

//DEL void CClassView::OnEditCut()
//DEL {
//DEL 	// CG: ���̃u���b�N�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
//DEL 	{
//DEL 		CSharedFile	memFile;
//DEL 		CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);
//DEL 
//DEL 		// �V���A���C�Y �f�[�^���A�[�J�C�u �I�u�W�F�N�g��
//DEL 		DoCutCopyPaste(ar, TRUE);
//DEL 
//DEL 		ar.Flush();
//DEL 
//DEL 		HGLOBAL hData = memFile.Detach();
//DEL 		if (OpenClipboard())
//DEL 		{
//DEL 			::SetClipboardData(m_nClipboardFormat, hData);
//DEL 			CloseClipboard();
//DEL 		}
//DEL 		else
//DEL 			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
//DEL 	}
//DEL }

//DEL void CClassView::OnEditPaste()
//DEL {
//DEL 	// CG: ���̃u���b�N�̓N���b�v�{�[�h �A�V�X�^���g �R���|�[�l���g�ɂ���Ēǉ�����܂���
//DEL 	{
//DEL 		if (OpenClipboard())
//DEL 		{
//DEL 			HANDLE hData = ::GetClipboardData(m_nClipboardFormat);
//DEL 			if (hData != NULL)
//DEL 			{
//DEL 				CSharedFile memFile;
//DEL 				memFile.SetHandle(hData,FALSE);
//DEL 				CArchive ar(&memFile, CArchive::load);
//DEL 
//DEL 				// �f�[�^���h�L�������g�փV���A���C�Y
//DEL 				DoCutCopyPaste(ar, FALSE);
//DEL 				ar.Close();
//DEL 				memFile.Detach();
//DEL 			}
//DEL 			else
//DEL 				AfxMessageBox(CG_IDS_CANNOT_GET_CLIPBOARD_DATA);
//DEL 			CloseClipboard();
//DEL 		}
//DEL 		else
//DEL 			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
//DEL 	}
//DEL 
//DEL }

BOOL CClassView::IsSelected()
{
	// TODO: �R�s�[����ѐ؂��胁�j���[�̗L��/��������I��I�ɍs����悤�ȃR�[�h��ǉ��܂���
	//       �C�����Ă��������B��ȏ�̃A�C�e�����I�����ꂽ�ꍇ�ɂ� TRUE ���A
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	if((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))!=-1) 
		return TRUE;
	else
		return FALSE;
}

void CClassView::DoCutCopyPaste(CArchive &ar, BOOL bCut)
{


	// TODO: �I������Ă���f�[�^�� CArchive �I�u�W�F�N�g�o�R�ŃN���b�v�[�h�ւ܂���
	//       �N���b�v�{�[�h����R�s�[����R�[�h��ǉ����Ă��������B����: 
	//       ar.IsStoring() �� TRUE �̏ꍇ�́A�R�s�[�܂��͐؂��葀����Ӗ����܂��B

	GetDocument()->Serialize(ar);

	if (bCut)
	{
		ASSERT(ar.IsStoring()); //�؂���A�\��t������͂���܂���

		// TODO: ���ݑI������Ă���A�C�e�����폜���邽�߂ɂ̓R�[�h��ǉ��܂��͒u�������Ă��������B

		GetDocument()->DeleteContents();
	}

	// �؂���܂��͓\��t������̏ꍇ�A�ύX�ʂ�Ƀr���[����уt���O���X�V���܂�
	if (!(ar.IsStoring() && !bCut))
	{
		GetDocument()->UpdateAllViews(NULL);
		GetDocument()->SetModifiedFlag();
	}
}

void CClassView::OnEditDelete() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	int index;
	POSITION pos;
	CClass* pCls;

	if((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))!=-1) {
		if(pDoc->cls.GetCount()>=2 && index > 0 && index<pDoc->cls.GetCount()) {
			pos = (POSITION)pDoc->cls.FindIndex(index);
			if(pos) {
				pCls=(CClass*)pDoc->cls.GetAt(pos);
				TRACE("pCls->name=%s \n", pCls->name);
				delete pCls;
				pDoc->cls.RemoveAt(pos);
				pDoc->ac=0;
				pDoc->am=-1;
				pDoc->pAPadf = NULL;
				InvalidateRect(NULL,FALSE);
				pDoc->UpdateAllViews(NULL);
				SetListItems();
				pDoc->SetModifiedFlag();
			}
		}
	}
}

void CClassView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	if((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))!=-1)
		pCmdUI->Enable(index>0 && index<pDoc->cls.GetCount());
	else
		pCmdUI->Enable(FALSE);
}

void CClassView::OnClsProperty() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED); 
	OnClsPropertyCommon(index);
}

void CClassView::OnUpdateClsProperty(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	pCmdUI->Enable((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))>=0);
}
