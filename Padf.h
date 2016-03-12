#pragma once

class CPadf : public CObject {
	friend class CVLine;
	friend class CModule;
	friend class CVEDoc;
	friend class CVEView;
	friend class CLeftView;
	DECLARE_SERIAL(CPadf)

private:
	WORD type;			//�@�o�`�c�̎�ނ܂��̓R�����g
	WORD type2;			//�@�o�`�c�̑�Q����
	CRect rect;			//�@�o�`�c�̊J�n�ʒu�ƏI���ʒu
	CString str;		//�@�o�`�c�̒��g�̕�����
	WORD num_branch;	//�@switch�ł̕���
	CString comment;	// ���̂o�`�c�}�`�ɂ��ẴR�����g
	CObList vl_list;
public:
	CPadf();
	~CPadf();
	virtual void Serialize(CArchive& ar);
	void Draw(CDC* pDC);
	BOOL HitTest(int x, int y);
};

