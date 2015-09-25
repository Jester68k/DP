// VarView.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "VE.h"
#include "Var.h"
#include "Class.h"
#include "VEDoc.h"
#include "VarDlg.h"
#include "VarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVarView

IMPLEMENT_DYNCREATE(CVarView, CListView)

BEGIN_MESSAGE_MAP(CVarView, CListView)
	//{{AFX_MSG_MAP(CVarView)
	ON_COMMAND(ID_INSERT_VAR, OnInsertVar)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_VAR_PROPERTY, OnVarProperty)
	ON_UPDATE_COMMAND_UI(ID_VAR_PROPERTY, OnUpdateVarProperty)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CVarView::CVarView()
{
}

CVarView::~CVarView()
{
}

BOOL CVarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_SINGLESEL ;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVarView �`��

void CVarView::OnDraw(CDC* pDC)
{
	CVEDoc* pDoc = GetDocument();
	// TODO: ���̈ʒu�ɕ`��p�̃R�[�h��ǉ����Ă�������
	SetListItems();
}

/////////////////////////////////////////////////////////////////////////////
// CVarView �f�f

#ifdef _DEBUG
void CVarView::AssertValid() const
{
	CListView::AssertValid();
}

void CVarView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CVEDoc* CVarView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVEDoc)));
	return (CVEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVarView ���b�Z�[�W �n���h��

void CVarView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CListCtrl&	listCtrl = GetListCtrl();
	LVCOLUMN lvcol;
	CVEDoc* pDoc = GetDocument();

	listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	lvcol.iSubItem = 0;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvcol.pszText = "���";
	lvcol.cx = 40;
	listCtrl.InsertColumn(0, &lvcol);

	lvcol.iSubItem = 1;
	lvcol.pszText = "�X�R�[�v";
	lvcol.cx = 80;
	listCtrl.InsertColumn(1, &lvcol);

	lvcol.iSubItem = 2;
	lvcol.pszText = "�^";
	lvcol.cx = 120;
	listCtrl.InsertColumn(2, &lvcol);

	lvcol.iSubItem = 3;
	lvcol.pszText = "���O";
	lvcol.cx = 140;
	listCtrl.InsertColumn(3, &lvcol);

	lvcol.iSubItem = 4;
	lvcol.pszText = "�����l�E���e";
	lvcol.cx = 100;
	listCtrl.InsertColumn(4, &lvcol);

	lvcol.iSubItem = 5;
	lvcol.pszText = "�R�����g";
	lvcol.cx = 200;
	listCtrl.InsertColumn(5, &lvcol);

	CVarView::SetListItems();
}

void CVarView::OnInsertVar() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CListCtrl& listCtrl = GetListCtrl();
	CVEDoc* pDoc = GetDocument();
	CVarDlg vardlg;
	POSITION m_pos;
	CClass* pCls;
	CModule* pMdl;
	CVar* pVar;

	if(pDoc->ac < 0 || pDoc->ac >=pDoc->cls.GetCount())
		return;
	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if(-1==pDoc->am)
		vardlg.m_scope = SCOPE_GLOBAL;
	else
		vardlg.m_scope = SCOPE_AUTO;
	vardlg.m_kind = KIND_VARIABLE;
	vardlg.m_type = TYPE_INT;
	vardlg.m_pointer = 0;
	vardlg.m_struct = _T("FILE");
	vardlg.m_accesstype = AT_PUBLIC;
	vardlg.m_name = _T("");
	vardlg.m_start = _T("");
	vardlg.m_comment = _T("");
	access_flag = (CLSTYPE_CLASS == pCls->type);
	if(vardlg.DoModal()==IDOK) {
		if(KIND_MACRO!=vardlg.m_kind && CheckVarName(vardlg.m_name))
			return;
		if(KIND_CONSTANT==vardlg.m_kind || KIND_MACRO==vardlg.m_kind || SCOPE_GLOBAL==vardlg.m_scope || CLSTYPE_UNION==pCls->type) {
			if(pCls->var.GetCount()) {
				m_pos=pCls->var.GetHeadPosition();
				while(m_pos) {
					pVar=(CVar*)pCls->var.GetNext(m_pos);
					if(pVar->name==vardlg.m_name) {
						if(0==pDoc->ac)
							AfxMessageBox("�������O�̃O���[�o���ϐ�������̂Œǉ��ł��܂���B",MB_OK);
						else
							AfxMessageBox("���������o�ϐ�������̂Œǉ��ł��܂���B",MB_OK);
						return;
					}
				}
			}
			pVar = new CVar();
			pVar->scope = SCOPE_GLOBAL;
			pVar->kind = vardlg.m_kind;
			if(KIND_MACRO!=vardlg.m_kind) {
				pVar->type = vardlg.m_type;	
				pVar->pointer = vardlg.m_pointer;
			} else {
				pVar->type = TYPE_VOID;
				pVar->pointer = 0;
			}
			pVar->access_type = vardlg.m_accesstype;
			pVar->struct_union = vardlg.m_struct;
			pVar->name = vardlg.m_name;
			if(CLSTYPE_GLOBAL==pCls->type)
				pVar->start = vardlg.m_start;
			pVar->comment = vardlg.m_comment;
			pCls->var.AddTail((CObject*)pVar);
		} else
			if(pDoc->am != -1) {
				pMdl=(CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
				m_pos=pMdl->var.GetHeadPosition();
				while(m_pos) {
					pVar=(CVar*)pMdl->var.GetNext(m_pos);
					if(pVar->name==vardlg.m_name) {
						AfxMessageBox("�������O�̃��[�J���ϐ�������̂Œǉ��ł��܂���B",MB_OK);
						return;
					}
				}
				pVar = new CVar();
				pVar->access_type = vardlg.m_accesstype;
				pVar->scope = vardlg.m_scope;
				pVar->kind = vardlg.m_kind;
				pVar->type = vardlg.m_type;
				pVar->pointer = vardlg.m_pointer;
				pVar->struct_union = vardlg.m_struct;
				pVar->name = vardlg.m_name;
				pVar->start = vardlg.m_start;
				pVar->comment = vardlg.m_comment;
				pMdl->var.AddTail((CObject*)pVar);
			}
		CVarView::SetListItems();
		pDoc->SetModifiedFlag();
		InvalidateRect(NULL,FALSE);
		pDoc->UpdateAllViews(NULL);
	}
}

void CVarView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	
	*pResult = 0;
}

void CVarView::SetListItems()
{
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	LVITEM	lvi;
	int index=0;
	POSITION m_pos;
	CClass* pCls;
	CModule* pMdl;
	CVar* pVar;
	CString str;

	listCtrl.DeleteAllItems();
	lvi.mask = LVIF_TEXT;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if(pCls->var.GetCount()) {
		m_pos=pCls->var.GetHeadPosition();
		while(m_pos) {
			pVar = (CVar*)pCls->var.GetNext(m_pos);
			lvi.iItem= index;
			lvi.iSubItem = 0;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(kind_tbl[pVar->kind]));
			index = listCtrl.InsertItem( &lvi );
			lvi.iItem = index;
			lvi.iSubItem = 1;
			if (CLSTYPE_GLOBAL==pCls->type)
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(scope_tbl[SCOPE_GLOBAL]));
			else
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(acctype_tbl[pVar->access_type]));
			listCtrl.SetItem(&lvi);
			lvi.iItem = index;
			lvi.iSubItem = 2;
			str=type_tbl2[pVar->type];
			if(pVar->type>=TYPE_STRUCT)
				str+="("+pVar->struct_union+")";
			if(pVar->type!=0)
				for(int i=0; i<pVar->pointer; i++)
					str += "*";
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
			listCtrl.SetItem(&lvi);
			lvi.iItem = index;
			lvi.iSubItem = 3;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pVar->name));
			listCtrl.SetItem(&lvi);
			lvi.iItem = index;
			lvi.iSubItem = 4;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pVar->start));
			listCtrl.SetItem(&lvi);
			lvi.iItem = index;	
			lvi.iSubItem = 5;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pVar->comment));
			listCtrl.SetItem(&lvi);
			index++;
		}
	}
	if(!pCls->mdl.GetCount())
		return;
	if(pDoc->am != -1) {
		pMdl = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
		if(pMdl->var.GetCount()) {
			m_pos=pMdl->var.GetHeadPosition();
			while(m_pos) {
				pVar = (CVar*)pMdl->var.GetNext(m_pos);
				lvi.iItem= index;
				lvi.iSubItem = 0;
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(kind_tbl[pVar->kind]));
				index = listCtrl.InsertItem( &lvi );
				lvi.iItem = index;
				lvi.iSubItem = 1;
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(scope_tbl[pVar->scope]));
				listCtrl.SetItem(&lvi);
				lvi.iItem = index;
				lvi.iSubItem = 2;
				if(pVar->type<TYPE_STRUCT)
					str=type_tbl2[pVar->type];
				else
					str=pVar->struct_union;
				if(pVar->type!=0)
					for(int i=0; i<pVar->pointer; i++)
						str += "*";
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
				listCtrl.SetItem(&lvi);
				lvi.iItem = index;
				lvi.iSubItem = 3;
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pVar->name));
				listCtrl.SetItem(&lvi);
				lvi.iItem = index;
				lvi.iSubItem = 4;
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pVar->start));
				listCtrl.SetItem(&lvi);
				lvi.iItem = index;
				lvi.iSubItem = 5;
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(pVar->comment));
				listCtrl.SetItem(&lvi);
				index++;
			}
		}
	}
	listCtrl.SetHoverTime(1);
}



void CVarView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CVarView::SetListItems();
}

void CVarView::OnEditDelete() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	int index;
	POSITION pos;
	CClass* pCls;
	CModule* pMdl;
	CVar* pVar;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED)) != -1) {
		if(pDoc->am != -1 && index>=pCls->var.GetCount()) {
			index -= pCls->var.GetCount();
			pMdl = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
			pos = pMdl->var.FindIndex(index);
			pVar = (CVar*)pMdl->var.GetAt(pos);
			delete pVar;
			pMdl->var.RemoveAt(pos);
		} else {
			pos = pCls->var.FindIndex(index);
			pVar = (CVar*)pCls->var.GetAt(pos);
			delete pVar;
			pCls->var.RemoveAt(pos);
		}
		pDoc->SetModifiedFlag();
		InvalidateRect(NULL,FALSE);
		pDoc->UpdateAllViews(NULL);
	}
}

void CVarView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	CPoint client_point;

	client_point = point;
	ScreenToClient(&client_point);	// �X�N���[�����W����N���C�A���g���W�֕ϊ�����
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_VARVIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

BOOL CVarView::IsSelected()
{
	// TODO: �R�s�[����ѐ؂��胁�j���[�̗L��/��������I��I�ɍs����悤�ȃR�[�h��ǉ��܂���
	//       �C�����Ă��������B��ȏ�̃A�C�e�����I�����ꂽ�ꍇ�ɂ� TRUE ���A
	//       �I���A�A�C�e�����I������Ă��Ȃ��ꍇ�� FALSE ��Ԃ��܂�
	CListCtrl&	listCtrl = GetListCtrl();
	int index;

	if((index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED))!=-1) 
		return TRUE;
	else
		return FALSE;
}

void CVarView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(IsSelected());	
}

void CVarView::OnVarProperty() 
{
	CVarView::OnVarPropertyCommon(-1); 
}

void CVarView::OnVarPropertyCommon(int no=-1) 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	CVarDlg vardlg;
	int index;
	CVar* pVar;
	CClass* pCls;
	CModule* pMdl;

	pCls=(CClass*)pDoc->cls.GetAt(pDoc->cls.FindIndex(pDoc->ac));
	if (no != -1) {
		index=no;
		listCtrl.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	} else
		index=listCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(index != -1) {
		if(pDoc->am != -1 && index>=pCls->var.GetCount()) {
			index -= pCls->var.GetCount();
			pMdl = (CModule*)pCls->mdl.GetAt(pCls->mdl.FindIndex(pDoc->am));
			pVar = (CVar*)pMdl->var.GetAt(pMdl->var.FindIndex(index));
			vardlg.m_kind = pVar->kind;
			vardlg.m_scope = pVar->scope;
			vardlg.m_type = pVar->type;
			vardlg.m_pointer = pVar->pointer;
			vardlg.m_struct = pVar->struct_union;
			vardlg.m_accesstype = pVar->access_type;
			vardlg.m_name = pVar->name;
			vardlg.m_start = pVar->start;
			vardlg.m_comment = pVar->comment;
			access_flag = (CLSTYPE_CLASS == pCls->type);
			if(vardlg.DoModal()==IDOK) {
				if(KIND_MACRO!=vardlg.m_kind && CheckVarName(vardlg.m_name))
					return;
				if(KIND_CONSTANT==vardlg.m_kind || KIND_MACRO==vardlg.m_kind || vardlg.m_scope!=SCOPE_GLOBAL) {
					pVar->kind = vardlg.m_kind;
					pVar->scope = vardlg.m_scope;
					if(KIND_MACRO!=vardlg.m_kind) {
						pVar->type = vardlg.m_type;	
						pVar->pointer = vardlg.m_pointer;
						pVar->struct_union = vardlg.m_struct;
					} else {
						pVar->type = TYPE_VOID;
						pVar->pointer = 0;
					}
					pVar->access_type = vardlg.m_accesstype;
					pVar->name = vardlg.m_name;
					if(CLSTYPE_GLOBAL==pCls->type)
						pVar->start = vardlg.m_start;
					pVar->comment = vardlg.m_comment;
					pDoc->SetModifiedFlag();
					CVarView::SetListItems();
					InvalidateRect(NULL,FALSE);
					pDoc->UpdateAllViews(NULL);
				}				
			}
		} else {
			pVar = (CVar*)pCls->var.GetAt(pCls->var.FindIndex(index));
			vardlg.m_kind = pVar->kind;
			vardlg.m_scope = pVar->scope;
			vardlg.m_type = pVar->type;
			vardlg.m_pointer = pVar->pointer;
			vardlg.m_struct = pVar->struct_union;
			vardlg.m_name = pVar->name;
			vardlg.m_start = pVar->start;
			vardlg.m_comment = pVar->comment;
			if(vardlg.DoModal()==IDOK && vardlg.m_scope==SCOPE_GLOBAL) {
				if(KIND_MACRO!=vardlg.m_kind && CheckVarName(vardlg.m_name))
					return;
				if(KIND_CONSTANT==vardlg.m_kind ||KIND_MACRO==vardlg.m_kind || vardlg.m_scope==SCOPE_GLOBAL) {
					pVar->scope = vardlg.m_scope;
					pVar->kind = vardlg.m_kind;
					if(KIND_MACRO!=vardlg.m_kind) {
						pVar->type = vardlg.m_type;	
						pVar->pointer = vardlg.m_pointer;
						pVar->struct_union = vardlg.m_struct;
					} else {
						pVar->type = TYPE_VOID;
						pVar->pointer = 0;
					}
				}
				pVar->name = vardlg.m_name;
				if(CLSTYPE_GLOBAL==pCls->type)
					pVar->start = vardlg.m_start;
				pVar->comment = vardlg.m_comment;
				pDoc->SetModifiedFlag();
				CVarView::SetListItems();
				InvalidateRect(NULL,FALSE);
				pDoc->UpdateAllViews(NULL);
			}
		}
	}
}

void CVarView::OnUpdateVarProperty(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(IsSelected());	
}

void CVarView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	CVarDlg vardlg;
	int index;
	index = listCtrl.HitTest(point);
	if(index == -1)
		CVarView::OnInsertVar();

	CListView::OnLButtonDown(nFlags, point);
}

BOOL CVarView::CheckVarName(CString str)
{
	BOOL array_cnt=0;

	if(str.GetLength()==0) {
		AfxMessageBox("���O�����͂���Ă��܂���B",MB_OK);
		return TRUE;
	}
	if(isdigit(str[0])) {
		AfxMessageBox("���O�̐擪�ɐ����͎g���܂���B",MB_OK);
		return TRUE;
	}
	for(int i=0; i<str.GetLength(); i++) {
		if('['==str[i]) {
			if(++array_cnt>1) {
				AfxMessageBox("'['�̐����������܂��B",MB_OK);
				return TRUE;
			}
			continue;
		}
		if(']'==str[i]) {
			if(--array_cnt<0) {
				AfxMessageBox("']'�̐����������܂��B",MB_OK);
				return TRUE;
			}
			continue;
		}
		if(!(isalnum(str[i]) || str[i]=='_')) {
			AfxMessageBox("�p������'_'�i�A���_�[�X�R�A�j�ł���K�v������܂��B",MB_OK);
			return TRUE;
		}
	}
	if(array_cnt!=0) {
		AfxMessageBox("']'�ŕ����Ă��܂���B",MB_OK);
		return TRUE;
	} else
		return FALSE;
}

void CVarView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	CVEDoc* pDoc = GetDocument();
	CListCtrl&	listCtrl = GetListCtrl();
	CVarDlg vardlg;
	int index;
	index = listCtrl.HitTest(point);

	if(index != -1)
		CVarView::OnVarPropertyCommon(index);
	
	CListView::OnLButtonDblClk(nFlags, point);
}
