// Class.h: CClass クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASS_H__F94745CB_D46A_452B_95B7_A6D0DC1994E7__INCLUDED_)
#define AFX_CLASS_H__F94745CB_D46A_452B_95B7_A6D0DC1994E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClass : public CObject  
{
	friend class CVEDoc;
	friend class CClassView;
	friend class CLeftView;
	friend class CVarView;
	friend class CVEView;
	DECLARE_SERIAL(CClass)

public:
	void SetValue(int type, CString name, int acctype, CString basecls, CString friendcls);
	virtual void Serialize(CArchive& ar);
	CClass();
	virtual ~CClass();
protected:
	int type;		// class type 
	CString name;	// name
	CObList var;	// member variables
	CObList mdl;	// member modules(functions)
	int acctype;	// access type
	CString basecls;// base class: classとあるがインターフェースも含む
	CString friendcls;	// フレンド・クラス
};

#endif // !defined(AFX_CLASS_H__F94745CB_D46A_452B_95B7_A6D0DC1994E7__INCLUDED_)
