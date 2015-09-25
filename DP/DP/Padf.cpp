#include "stdafx.h"
#include "Padf.h"

// CPad シリアライズ
CPadf::CPadf()
{
}

CPadf::~CPadf()
{
}

IMPLEMENT_SERIAL(CPadf, CObject, 0)

void CPadf::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
		ar << (WORD)type;
		ar << (WORD)type2;
		ar << (CRect)rect;
		ar << (CString)str;
		ar << (WORD)case_y;
		ar << (CString)case_str;
		ar << (INT)prev_p;
		ar << (WORD)prev_p_pos;
		ar << (WORD)num_branch;
		ar << (CString)comment;
	} else {
		ar >> (WORD&)type;
		ar >> (WORD&)type2;
		ar >> (CRect&)rect;
		ar >> (CString&)str;
		ar >> (WORD&)case_y;
		ar >> (CString&)case_str;
		ar >> (INT&)prev_p;
		ar >> (WORD&)prev_p_pos;
		ar >> (WORD&)num_branch;
		ar >> (CString&)comment;
	}
}

