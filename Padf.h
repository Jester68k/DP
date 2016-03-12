#pragma once

class CPadf : public CObject {
	friend class CVLine;
	friend class CModule;
	friend class CVEDoc;
	friend class CVEView;
	friend class CLeftView;
	DECLARE_SERIAL(CPadf)

private:
	WORD type;			//@‚o‚`‚c‚Ìí—Ş‚Ü‚½‚ÍƒRƒƒ“ƒg
	WORD type2;			//@‚o‚`‚c‚Ì‘æ‚Q‘®«
	CRect rect;			//@‚o‚`‚c‚ÌŠJnˆÊ’u‚ÆI—¹ˆÊ’u
	CString str;		//@‚o‚`‚c‚Ì’†g‚Ì•¶š—ñ
	WORD num_branch;	//@switch‚Å‚Ì•ªŠò”
	CString comment;	// ‚±‚Ì‚o‚`‚c}Œ`‚É‚Â‚¢‚Ä‚ÌƒRƒƒ“ƒg
	CObList vl_list;
public:
	CPadf();
	~CPadf();
	virtual void Serialize(CArchive& ar);
	void Draw(CDC* pDC);
	BOOL HitTest(int x, int y);
};

