// Var.cpp: CVar クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Var.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CVar::CVar()
{
}

CVar::~CVar()
{

}

IMPLEMENT_SERIAL(CVar, CObject, 0)

void CVar::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
		ar << (WORD) kind;
		ar << (WORD) access_type;
		ar << (WORD) scope;
		ar << (WORD) type;
		ar << (WORD) pointer;
		ar << struct_union;
		ar << name;
		ar << start;
		ar << comment;
	} else {
		ar >> (WORD&) kind;
		ar >> (WORD&) scope;
		ar >> (WORD&) access_type;
		ar >> (WORD&) type;
		ar >> (WORD&) pointer;
		ar >> struct_union;
		ar >> name;
		ar >> start;
		ar >> comment;
	}
}