// Module.cpp: CModule クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VE.h"
#include "Var.h"
#include "VLine.h"
#include "Padf.h"
#include "Module.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CModule, CObject, 0)

CModule::CModule()
{
	total_padfs = 0;
}

CModule::~CModule()
{
	POSITION pos;

	if(var.GetCount()>0) {
		pos= var.GetHeadPosition();
		while(pos) {
			delete (CVar*)(var.GetNext(pos));
		}
		var.RemoveAll();
	}
	if(line.GetSize()>0)
		line.RemoveAll();
}

// CModule serialize

void CModule::Serialize(CArchive& ar)
{
	int l, v;
	WORD lsize, num_vars, num_padfs;
	CVar* pVar;
	CPadf* pPadf;
	CVLine* pVl;
	POSITION pos;

	if (ar.IsStoring()) {
		ar << name;
		ar << arg;
		ar << (WORD)ret_type;
		ar << (WORD)ret_pointer;
		ar << ret_class;
		ar << (WORD)access_type;
		ar << comment;
		ar << rect;
		ar << (BOOL)recursive;
		ar << (BOOL)inline_flag;
		ar << (WORD)func_type;
		ar << (WORD)total_padfs;
		lsize = line.GetSize();
		ar << (WORD)lsize;
		if(lsize>0) {
			for(l=0; l<lsize; l++)
				ar << (WORD)line[l];
		}
		ar << (WORD)var.GetCount();
		if(var.GetCount()) {
			pos = var.GetHeadPosition();
			while(pos) {
				pVar= (CVar*)var.GetNext(pos);
				ar << pVar;
			}
		}
		ar << &vline;
	} else {
		ar >> name;
		ar >> arg;
		ar >> (WORD&)ret_type;
		ar >> (WORD&)ret_pointer;
		ar >> ret_class;
		ar >> (WORD&)access_type;
		ar >> comment;
		ar >> rect;
		ar >> (BOOL&)recursive;
		ar >> (BOOL&)inline_flag;
		ar >> (WORD&)func_type;
		ar >> (WORD&)total_padfs;
		ar >> (WORD&)lsize;
		if(lsize>0) {
			line.SetSize(lsize,1);
			for(l=0; l<lsize; l++) {
				ar >> (WORD&)line[l];
			}
		}
		ar >> (WORD&)num_vars;
		if(num_vars>0)
			for(v=0; v<num_vars; v++) {
				ar >> pVar;
				var.AddTail((CObject*)pVar);
			}
		ar >> pVl;

		vline.hline_y = pVl->hline_y;	// Horizontal line position Y
		vline.case_str = pVl->case_str;	// case string
		vline.x=pVl->x;					// Vertical Line position X
		vline.sy=pVl->sy;				//                        start Y
		vline.ey=pVl->ey;				//                        end   Y
		num_padfs = pVl->padf_list.GetCount();
		if (num_padfs) {
			pos = pVl->padf_list.GetHeadPosition();
			while (pos) {
				pPadf = (CPadf*)pVl->padf_list.GetNext(pos);
				vline.padf_list.AddTail((CObject*)pPadf);
			}
		}
	}
}
