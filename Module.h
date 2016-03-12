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
	CString name;	// ���W���[����
	CString arg;	// ����
	WORD ret_type;	// �߂�l�̌^
	WORD ret_pointer;// �|�C���^
	CString ret_class;
	WORD access_type;
	CString comment;// �R�����g
	CRect rect;		// ��`
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