class CPadf : public CObject {
	friend class CModule;
	friend class CVEDoc;
	friend class CVEView;
	friend class CLeftView;
	DECLARE_SERIAL(CPadf)

private:
	WORD type;		//�@�o�`�c�̎�ނ܂��̓R�����g
	WORD type2;		//�@�I���̏ꍇ�̂Q�Ԗڂ̃^�C�v
	CRect rect;		//�@�o�`�c�̍���ƉE���̍��W
	CString str;	//�@�o�`�c�̒��g�̕�����
	WORD case_y;	//�@case�̂x���W
	CString case_str;//�@�I����switch�̎���case�̕�����
	INT prev_p;		//�@��O�ɂȂ����Ă���o�`�c�̔ԍ�(-1�Ȃ�O�͖���)
	WORD prev_p_pos;//�@��O�ɂȂ����Ă���o�`�c�̐ڑ��ʒu
	WORD num_branch;//�@switch�ł̕���
	CString comment;// ���̂o�`�c�}�`�ɂ��ẴR�����g
//	CObArray vla;

public:
	CPadf();
	~CPadf();
	virtual void Serialize(CArchive& ar);
};

