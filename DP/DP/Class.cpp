// Class.cpp: CClass クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ve.h"
#include "var.h"
#include "module.h"
#include "Class.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CClass::CClass()
{
}

void CClass::SetValue(int clstype, CString clsname, int clsacctype, CString clsbasecls, CString clsfriendcls)
{
	type = clstype;
	name = clsname;
	acctype = clsacctype;
	basecls = clsbasecls;
	friendcls = clsfriendcls;
}

CClass::~CClass()
{
	POSITION pos;

	if(var.GetCount()) {
		pos = var.GetHeadPosition();
		while(pos) {
			delete (CVar*)(var.GetNext(pos));
		}
		var.RemoveAll();
	}
	if(mdl.GetCount()) {
		pos = mdl.GetHeadPosition();
		while(pos) {
			delete (CModule*)(mdl.GetNext(pos));
		}
		mdl.RemoveAll();
	}
}

IMPLEMENT_SERIAL(CClass, CObject, 0)

void CClass::Serialize(CArchive& ar)
{
	POSITION pos;
	CVar* pVar;
	CModule* pMdl;
	int num_vars, num_mdls;

	if (ar.IsStoring()) {
		ar << type;	// class type
		ar << name;	// class name
		ar << acctype;	// access specifier
		ar << basecls;	// base class
		ar << friendcls;
		ar << (DWORD)var.GetCount();	// variables
		if(var.GetCount()>0) {
			pos=var.GetHeadPosition();
			while(pos) {
				pVar = (CVar*)var.GetNext(pos);
				ar << pVar;
			}
		}
		ar << (DWORD)mdl.GetCount();	// modules
		if(mdl.GetCount()>0) {
			pos=mdl.GetHeadPosition();
			while(pos) {
				pMdl = (CModule*)mdl.GetNext(pos);
				ar << pMdl;
			}
		}
	} else {
		ar >> type;
		ar >> name;
		ar >> acctype;
		ar >> basecls;
		ar >> friendcls;
		ar >> (DWORD&)num_vars;
		if(num_vars>0)
			for(int v=0; v<num_vars; v++) {
				ar >> pVar;
				var.AddTail((CObject*)pVar);
			}
		ar >> (DWORD&)num_mdls;
		if(num_mdls>0)
			for(int m=0; m<num_mdls; m++) {
//				pMdl = new CModule();
				ar >> pMdl;
				mdl.AddTail((CObject*)pMdl);
			}
	}
}