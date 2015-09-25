class CModule : public CObject {
	friend class CVEDoc;
	friend class CLeftView;
	friend class CVarView;
	friend class CVEView;
	DECLARE_SERIAL(CModule)

private:
	CString name;	// モジュール名
	CString arg;	// 引数
	WORD ret_type;	// 戻り値の型
	WORD ret_pointer;// ポインタ
	CString ret_class;
	WORD access_type;
	CString comment;// コメント
	CRect rect;		// 矩形
	BOOL recursive;
	BOOL inline_flag;
	WORD func_type;
	CWordArray line;
	CObList var;
	CObList padf;
//	CVLine vl;
public:
	CModule();
	~CModule();
	virtual void Serialize(CArchive& ar);
};