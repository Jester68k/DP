#include "VLine.h"

class CModule : public CObject {
	friend class CPadf;
	friend class CVLine;
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
	WORD total_padfs;
	CWordArray line;
	CObList var;
	CVLine vline;
	CObList comment_list;
public:
	CModule();
	~CModule();
	void Serialize(CArchive& ar);
};