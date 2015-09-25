// Var.h: CVar クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VAR_H__87AC679F_4668_4C15_8707_E220FA6AC020__INCLUDED_)
#define AFX_VAR_H__87AC679F_4668_4C15_8707_E220FA6AC020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVar : public CObject // CVarクラスをCObjectクラスの派生クラスとした
{
	friend class CModule;
	friend class CVEDoc;
	friend class CVarView;
	DECLARE_SERIAL(CVar)

protected:
	WORD kind;
	WORD scope;
	WORD access_type;
	WORD type;
	WORD pointer;
	CString struct_union;
	CString name;
	CString start;
	CString comment;
public:
	CVar();
	~CVar();
	virtual void Serialize(CArchive& ar);
};

#endif // !defined(AFX_VAR_H__87AC679F_4668_4C15_8707_E220FA6AC020__INCLUDED_)
