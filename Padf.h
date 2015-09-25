class CPadf : public CObject {
	friend class CModule;
	friend class CVEDoc;
	friend class CVEView;
	friend class CLeftView;
	DECLARE_SERIAL(CPadf)

private:
	WORD type;		//　ＰＡＤの種類またはコメント
	WORD type2;		//　選択の場合の２番目のタイプ
	CRect rect;		//　ＰＡＤの左上と右下の座標
	CString str;	//　ＰＡＤの中身の文字列
	WORD case_y;	//　caseのＹ座標
	CString case_str;//　選択のswitchの時のcaseの文字列
	INT prev_p;		//　一つ前につながっているＰＡＤの番号(-1なら前は無し)
	WORD prev_p_pos;//　一つ前につながっているＰＡＤの接続位置
	WORD num_branch;//　switchでの分岐数
	CString comment;// このＰＡＤ図形についてのコメント
//	CObArray vla;

public:
	CPadf();
	~CPadf();
	virtual void Serialize(CArchive& ar);
};

