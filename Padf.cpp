#include "stdafx.h"
#include "VLine.h"
#include "Padf.h"
#include "VE.h"

IMPLEMENT_SERIAL(CPadf, CObject, 0)

// CPad シリアライズ
CPadf::CPadf()
{
	num_branch = 0;
}

CPadf::~CPadf()
{
}

void CPadf::Serialize(CArchive& ar)
{
	POSITION pos;
	int num_vlines;
	CVLine* pVl;

	if (ar.IsStoring()) {
		ar << (WORD)type;
		ar << (WORD)type2;
		ar << (CRect)rect;
		ar << (CString)str;
		ar << (CString)case_str;
		ar << (WORD)num_branch;
		ar << (CString)comment;
		ar << vl_list.GetCount();
		if (vl_list.GetCount()) {
			pos = vl_list.GetHeadPosition();
			while (pos) {
				pVl = (CVLine*)vl_list.GetNext(pos);
				ar << pVl;
			}
		}
	}
	else {
		ar >> (WORD&)type;
		ar >> (WORD&)type2;
		ar >> (CRect&)rect;
		ar >> (CString&)str;
		ar >> (CString&)case_str;
		ar >> (WORD&)num_branch;
		ar >> (CString&)comment;
		ar >> num_vlines;
		if (num_vlines > 0) {
			while (--num_vlines >= 0) {
				ar >> pVl;
				vl_list.AddTail((CObject*)pVl);
			}
		}
	}
}

void CPadf::Draw(CDC* pDC)
{
	CRectTracker rt;
	int sx, sy, ex, ey, xsize, ysize;
	CVLine* pVl;
	POSITION pos;
	CPen myPen, *pOldPen;
	CString display_string;

	myPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	pOldPen = pDC->SelectObject(&myPen);

	if (type >= PADF_PROCESS && type <= PADF_COMMENT) {
		if (type == PADF_COMMENT)
			pDC->DrawText(str, rect, DT_LEFT | DT_WORDBREAK);
		else {
			display_string.Format(padf_msg[type][type2], str);
			display_string.Replace("&", "&&");
			pDC->DrawText(display_string, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
		sx = rect.left;
		sy = rect.top;
		ex = rect.right;
		ey = rect.bottom;
		xsize = ex - sx + 1;
		ysize = ey - sy + 1;
		if (type >= PADF_PROCESS && type <= PADF_REPEAT) {
			pDC->MoveTo(ex, sy);
			pDC->LineTo(sx, sy);
			pDC->LineTo(sx, ey);
			pDC->LineTo(ex, ey);
		}
		switch (type) {
		case PADF_PROCESS:
			pDC->MoveTo(ex, sy);
			pDC->LineTo(ex, ey);
			break;
		case PADF_SELECTION:
			pDC->MoveTo(ex, sy);
			if (num_branch <= 2) {
				pDC->LineTo(ex - 10, sy + ysize / 2);
				pDC->LineTo(ex, ey);
			} else {
				if(vl_list.GetCount()) {
					pos = vl_list.GetHeadPosition();
					while (pos) {
						pVl = (CVLine*)vl_list.GetNext(pos);
						pDC->LineTo(ex - 10, pVl->hline_y);
						pDC->LineTo(ex, pVl->hline_y);
					}
				}
			}
			break;
		case PADF_REPEAT:
			pDC->MoveTo(ex, sy);
			pDC->LineTo(ex, ey);
			if (type2 != 2) {
				pDC->MoveTo(sx + 10, sy);	// for(), while() 
				pDC->LineTo(sx + 10, ey);	// 
			}
			else {
				pDC->MoveTo(ex - 10, sy);	// do while()
				pDC->LineTo(ex - 10, ey);	//
			}
			break;
		default:
			break;
		}
		// draw line
		if (vl_list.GetCount()) {
			pos = vl_list.GetHeadPosition();
			while (pos) {
				pVl = (CVLine*)vl_list.GetNext(pos);
				pVl->Draw(pDC, rect);
			}
		}
	}
	pDC->SelectObject(pOldPen);
	myPen.DeleteObject();
}

BOOL CPadf::HitTest(int x, int y)
{
	return FALSE;
}