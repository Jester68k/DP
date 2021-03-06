#pragma once

class CPadf : public CObject {
	friend class CVLine;
	friend class CModule;
	friend class CVEDoc;
	friend class CVEView;
	friend class CLeftView;
	DECLARE_SERIAL(CPadf)

private:
	WORD type;			//　ＰＡＤの種類またはコメント
	WORD type2;			//　ＰＡＤの第２属性
	CRect rect;			//　ＰＡＤの開始位置と終了位置
	CString str;		//　ＰＡＤの中身の文字列
	WORD num_branch;	//　switchでの分岐数
	CString comment;	// このＰＡＤ図形についてのコメント
	CObList vl_list;
public:
	CPadf();
	~CPadf();
	virtual void Serialize(CArchive& ar);
	void Draw(CDC* pDC);
	BOOL HitTest(int x, int y);
};

