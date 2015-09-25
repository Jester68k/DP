// Module.cpp: CModule クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VE.h"
#include "Var.h"
#include "Padf.h"
//#include "VLine.h"
#include "Module.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CModule::CModule()
{
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
	if(padf.GetCount()>0) {
		pos = padf.GetHeadPosition();
		while(pos) {
			delete (CPadf*)(padf.GetNext(pos));
		}
		padf.RemoveAll();
	}
}

// CModule serialize

IMPLEMENT_SERIAL(CModule, CObject, 0)

void CModule::Serialize(CArchive& ar)
{
	int l, v, p;
	WORD lsize, num_vars, num_padfs;
	CVar* pVar;
	CPadf* pPadf;
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
		lsize = line.GetSize();
		ar << (WORD)lsize;
		if(lsize>0) {
			for(l=0; l<lsize; l++)
				ar << (WORD)line[l];
		}
		ar << (WORD)var.GetCount();
		if(var.GetCount()) {
			pos= var.GetHeadPosition();
			while(pos) {
				pVar= (CVar*)var.GetNext(pos);
				ar << pVar;
			}
		}
		ar << (WORD)padf.GetCount();
		if(padf.GetCount()) {
			pos=padf.GetHeadPosition();
			while(pos) {
				pPadf = (CPadf*)padf.GetNext(pos);
				ar << pPadf;
			}
		}
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
		ar >> (WORD&)num_padfs;
		if(num_padfs>0)
			for(p=0; p<num_padfs; p++) {
				ar >> pPadf;
				padf.AddTail((CObject*)pPadf);
			}
	}
}
