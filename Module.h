class CModule : public CObject {
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
	CWordArray line;
	CObList var;
	CObList padf;
//	CVLine vl;
public:
	CModule();
	~CModule();
	virtual void Serialize(CArchive& ar);
};