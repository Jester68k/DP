// VEDoc.cpp : CVEDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "VE.h"

#include "Var.h"
#include "class.h"
#include "OptionDlg.h"
#include "VEDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVEDoc

IMPLEMENT_DYNCREATE(CVEDoc, CDocument)

BEGIN_MESSAGE_MAP(CVEDoc, CDocument)
	//{{AFX_MSG_MAP(CVEDoc)
	ON_COMMAND(ID_SAVE_SOURCE_FILE, OnSaveSourceFile)
	ON_COMMAND(ID_BUILD_BUILD, OnBuildBuild)
	ON_COMMAND(ID_BUILD_EXEC, OnBuildExec)
	ON_COMMAND(ID_TOOL_OPTION, OnToolOption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVEDoc クラスの構築/消滅

CVEDoc::CVEDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。
	ac=0;	// active class (0 is global)
	am=0;
	ap=-1;
	compiler_type=COMPILER_VC2015;
	compiler_path="";
}

CVEDoc::~CVEDoc()
{
	POSITION pos;

	if(cls.GetCount()) {
		pos = cls.GetHeadPosition();
		while(pos) {
			delete (CClass*)(cls.GetNext(pos));
		}
		cls.RemoveAll();
	}
}



/////////////////////////////////////////////////////////////////////////////
// CVEDoc シリアライゼーション

void CVEDoc::Serialize(CArchive& ar)
{
	int num_clss;
	POSITION pos;
	CClass* pCls;

	if (ar.IsStoring()) {
		// TODO: この位置に保存用のコードを追加してください。
		ar << (LONG)ac;
		ar << (LONG)am;
		ar << (LONG)ap;
		ar << (LONG)compiler_type;
		ar << (CString)compiler_path;
		ar << (DWORD)cls.GetCount();	// global variables
		if(cls.GetCount()>0) {
			pos=cls.GetHeadPosition();
			while(pos) {
				pCls = (CClass*)cls.GetNext(pos);
				ar << pCls;
			}
		}
	} else {
		// TODO: この位置に読み込み用のコードを追加してください。
		ar >> (LONG&)ac;
		ar >> (LONG&)am;
		ar >> (LONG&)ap;
		ar >> (LONG&)compiler_type;
		ar >> (CString&)compiler_path;
		ar >> (DWORD&)num_clss;
		if(num_clss>0)
			for(int v=0; v<num_clss; v++) {
				ar >> pCls;
				cls.AddTail((CObject*)pCls);
			}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVEDoc クラスの診断

#ifdef _DEBUG
void CVEDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVEDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVEDoc コマンド

BOOL CVEDoc::OnNewDocument()
{
	CClass* pCls;
	CModule* pMdl;

	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)
	POSITION pos;

	if(cls.GetCount()) {
		pos = cls.GetHeadPosition();
		while(pos) {
			delete (CClass*)(cls.GetNext(pos));
		}
		cls.RemoveAll();
	}

	pCls = new CClass();
	pCls->SetValue(CLSTYPE_GLOBAL, "", AT_PUBLIC, "", "");
	cls.AddTail((CObject*)pCls);

	pMdl = new CModule();
	pMdl->name = "main";	// モジュール名はmain
	pMdl->arg = "int argc, char* argv[]";
	pMdl->ret_type = TYPE_INT;
	pMdl->ret_pointer = 0;
	pMdl->access_type = AT_PUBLIC;
	pMdl->comment = "この関数から始まります";
	pMdl->rect.top = 5;
	pMdl->rect.left=75+100/2;
	pMdl->rect.bottom = 5+MODULE_HEIGHT;
	pMdl->rect.right = 75+100/2+50;
	pMdl->recursive=FALSE;
	pMdl->func_type=FUNCTYPE_NORMAL;
	pMdl->inline_flag=FALSE;
	pCls->mdl.AddTail((CObject*)pMdl);

	ac=0;	// selected class (0 is global)
	am=0;
	ap=-1;

	return TRUE;
}

CPadf* CVEDoc::GetPadf(CModule* pMdl, int pad)
{
	return (CPadf*)pMdl->padf.GetAt(pMdl->padf.FindIndex(pad));
}

int CVEDoc::GetNextPadfNum(CModule* pMdl, int padf, int p_pos)
{
	int i;
	CPadf* pPadf;
	POSITION pos;

	i=0;
	pos=pMdl->padf.GetHeadPosition();
	while(pos) {
		pPadf=(CPadf*)pMdl->padf.GetNext(pos);
		if(pPadf->prev_p==padf && pPadf->prev_p_pos==p_pos)
			return i;
		i++;
	}
	return -1;
}


void CVEDoc::OnSaveSourceFile() 
{
	CVEDoc::SaveSourceFile();
}

BOOL CVEDoc::SaveSourceFile() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	int i, str_pos, pad;
	CString ext, filename, str;
	CVar* pVar;
	CPadf* pPadf;
	CClass* pCls;
	CModule* pMdl;
	POSITION cpos, lpos, lpos2;	// "l" of "lpos" is short for "list"

	title=GetTitle();
	filename=GetTitle();
	if((str_pos=filename.Find(".dp"))!=-1)
		filename.Delete(str_pos,3);
	CFileDialog fd(FALSE, "",filename,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Ｃ＋＋言語ソースファイル(*.cpp)|*.cpp|");
	if(fd.DoModal()==IDOK) {
		path=fd.GetPathName();
		if(f.Open(path, CFile::modeCreate | CFile::modeWrite)) {
			str.Format("/* %s */\n\n", fd.GetFileName());
			f.WriteString(str);
			f.WriteString(cpp_header_str);
			f.WriteString("\n");
			if(cls.GetCount()>1) {
				cpos = (POSITION)cls.GetHeadPosition();	// 先頭のキー値を得る
				pCls = (CClass*)cls.GetNext(cpos);	// 次のキーを得る
				while(cpos) {
					pCls = (CClass*)cls.GetNext(cpos);
					switch(pCls->type) {
					case CLSTYPE_STRUCT:
						if(pCls->var.GetCount()) {
							str.Format("typedef struct %stag %s;\nstruct %stag {\n", pCls->name, pCls->name, pCls->name);
							f.WriteString(str);
							lpos=pCls->var.GetHeadPosition();
							while(lpos) {
								pVar = (CVar*)pCls->var.GetNext(lpos);
								if(KIND_VARIABLE==pVar->kind) {
									if(pVar->type<TYPE_STRUCT)
										str.Format("\t%s", type_tbl[pVar->type]);
									else
										if(TYPE_UNION==pVar->type)
											str.Format("union %s", pVar->struct_union);
										else
											str.Format("\t%s", pVar->struct_union);
									f.WriteString(str);
									for(i=0; i<pVar->pointer; i++)
										f.WriteString("*");
									str.Format(" %s;", pVar->name);
									f.WriteString(str);
									if(""!=pVar->comment) {
										str.Format(" /* %s */", pVar->comment);
										f.WriteString(str);
									}
									f.WriteString("\n");
								}
							}
							f.WriteString("};\n\n");
						}
						break;
					case CLSTYPE_UNION:
						if(pCls->var.GetCount()) {
							str.Format("union %s {\n", pCls->name);
							f.WriteString(str);
							lpos=pCls->var.GetHeadPosition();
							while(lpos) {
								pVar = (CVar*)pCls->var.GetNext(lpos);
								if(KIND_VARIABLE==pVar->kind) {
									if(pVar->type<TYPE_STRUCT)
										str.Format("\t%s", type_tbl[pVar->type]);
									else
										if(TYPE_UNION==pVar->type)
											str.Format("union %s %s;", pVar->struct_union, pVar->name);
										else
											str.Format("\t%s", pVar->struct_union);
									f.WriteString(str);
									for(i=0; i<pVar->pointer; i++)
										f.WriteString("*");
									str.Format(" %s;", pVar->name);
									f.WriteString(str);
									if(""!=pVar->comment) {
										str.Format(" /* %s */", pVar->comment);
										f.WriteString(str);
									}
									f.WriteString("\n");
								}
							}
							f.WriteString("};\n\n");
						}
						break;
					case CLSTYPE_CLASS:
						if(pCls->var.GetCount()||pCls->mdl.GetCount()) {
							if(pCls->basecls.GetLength())	// 基底クラスがあれば継承を記述する
								str.Format("class %s %s %s{\n", pCls->name, pCls->acctype, pCls->basecls);
							else
								str.Format("class %s {\n", pCls->name);
							f.WriteString(str);
							if(pCls->friendcls.GetLength()) {
								str.Format("\tfriend class %s;\n", pCls->friendcls);
								f.WriteString(str);
							}
							lpos=pCls->var.GetHeadPosition();
							while(lpos) {
								pVar = (CVar*)pCls->var.GetNext(lpos);
								if(KIND_VARIABLE==pVar->kind) {
									if(pVar->type<TYPE_STRUCT)
										str.Format("%s:\t%s", acctype_tbl[pVar->access_type], type_tbl[pVar->type]);
									else
										if(TYPE_UNION==pVar->type)
											str.Format("union %s %s;", pVar->struct_union, pVar->name);
										else
											str.Format("\t%s", pVar->struct_union);
									f.WriteString(str);
									for(i=0; i<pVar->pointer; i++)
										f.WriteString("*");
									if(TYPE_UNION!=pVar->type) {
										str.Format(" %s;", pVar->name);
										f.WriteString(str);
									}
									if(""!=pVar->comment) {
										str.Format(" /* %s */", pVar->comment);
										f.WriteString(str);
									}
									f.WriteString("\n");
								}
							}
							// write member function(s)
							lpos=pCls->mdl.GetHeadPosition();
							while(lpos) {
								pMdl = (CModule*)pCls->mdl.GetNext(lpos);
								if(pMdl->ret_type<TYPE_STRUCT)
									str.Format("%s: ", acctype_tbl[pMdl->access_type]);
								f.WriteString(str);
								if(pMdl->func_type==FUNCTYPE_VIRTUAL||pMdl->func_type==FUNCTYPE_PUREVIRTUAL)
									f.WriteString("virtual ");
								else
									if(pMdl->func_type==FUNCTYPE_FRIEND)
										f.WriteString("friend ");
								if(pMdl->ret_type<TYPE_STRUCT)
									str.Format("%s %s(%s)", type_tbl[pMdl->ret_type], pMdl->name, pMdl->arg);
								else
									str.Format("%s %s(%s)", pMdl->ret_class, pMdl->name, pMdl->arg);
								f.WriteString(str);
								if(pMdl->func_type==FUNCTYPE_PUREVIRTUAL)
									f.WriteString("=0");
								str.Format("; /* %s */\n", pMdl->comment);
								f.WriteString(str);
							}
							f.WriteString("};\n\n");
							lpos=pCls->mdl.GetHeadPosition();
							while(lpos) {
								pMdl = (CModule*)pCls->mdl.GetNext(lpos);
								if(pMdl->inline_flag)
									f.WriteString("inline ");
								if(pMdl->ret_type<TYPE_STRUCT)
									str.Format("%s %s::%s(%s) /* %s */\n{\n", type_tbl[pMdl->ret_type], pCls->name, pMdl->name, pMdl->arg, pMdl->comment);
								else
									str.Format("%s %s::%s(%s) /* %s */\n{\n", pMdl->ret_class, pCls->name, pMdl->name, pMdl->arg, pMdl->comment);
								f.WriteString(str);
								if(pMdl->var.GetCount()) {
									lpos2=pMdl->var.GetHeadPosition();
									while(lpos2) {
										f.WriteString("\t");
										pVar = (CVar*)pMdl->var.GetNext(lpos2);
										if(SCOPE_LOCAL_STATIC==pVar->scope) {
											str.Format("%s ", scope_tbl[pVar->scope]);
											f.WriteString(str);
										}
										if(pVar->type<TYPE_STRUCT)
											str.Format("%s", type_tbl[pVar->type]);
										else
											if(TYPE_UNION==pVar->type)
												str.Format("union %s", pVar->struct_union);
											else
												str.Format("%s", pVar->struct_union);
										f.WriteString(str);
										for(i=0; i<pVar->pointer; i++)
											f.WriteString("*");
										if(""==pVar->start || TYPE_UNION==pVar->type)
											str.Format(" %s;", pVar->name);
										else
											if(pVar->start.Find(',')!=-1)
												str.Format(" %s = {%s};", pVar->name, pVar->start);
											else
												str.Format(" %s = %s;", pVar->name, pVar->start);
										f.WriteString(str);
										if(""!=pVar->comment) {
											str.Format(" /* %s */", pVar->comment);
											f.WriteString(str);
										}
										f.WriteString("\n");
									}
									f.WriteString("\n");
								}
								if(pMdl->padf.GetCount()) { // モジュールにＰＡＤ図形などがあるかどうか
									pad=0;
									lpos2=pMdl->padf.GetHeadPosition();
									while(lpos2) {
										pPadf = (CPadf*)pMdl->padf.GetNext(lpos2);
										if (pPadf->type>=PADF_PROCESS && pPadf->type<=PADF_REPEAT && -1==pPadf->prev_p)
											break;
									pad++;
									}
									WriteLines(pMdl,pad,1);	// pMdlがモジュールのアドレス、pがＰＡＤ、１がインデント
								}
								str.Format("} /* End of %s::%s() */\n", pCls->name, pMdl->name);
								f.WriteString(str);
							}
							f.WriteString("\n");
						}
						break;
					}
				}
			}
			pCls=(CClass*)cls.GetHead();
			if(pCls->var.GetCount()) {
				f.WriteString("/* Macro(s) & Global(s) */\n");
				lpos=pCls->var.GetHeadPosition();
				while(lpos) {
					pVar = (CVar*)pCls->var.GetNext(lpos);
					if(KIND_MACRO==pVar->kind) {
						str.Format("#define %s %s\n", pVar->name, pVar->start);
						f.WriteString(str);
					} else {
						if(KIND_CONSTANT==pVar->kind)
							f.WriteString("const ");
						if(pVar->type<TYPE_STRUCT)
							str.Format("%s", type_tbl[pVar->type]);
						else
							if(TYPE_UNION==pVar->type)
								str.Format("union %s", pVar->struct_union);
							else
								str.Format("%s", pVar->struct_union);
						f.WriteString(str);
						for(i=0; i<pVar->pointer; i++)
							f.WriteString("*");
						if(""==pVar->start || pVar->type!=TYPE_UNION)
							str.Format(" %s;", pVar->name);
						else
							if(pVar->start.Find(',')!=-1)
								str.Format(" %s = {%s};", pVar->name, pVar->start);
							else
								str.Format(" %s = %s;", pVar->name, pVar->start);
						f.WriteString(str);
						if(""!=pVar->comment) {
							str.Format(" /* %s */", pVar->comment);
							f.WriteString(str);
						}
						f.WriteString("\n");
					}
				}
				f.WriteString("\n");
			}
			f.WriteString("\nusing namespace std;\n\n");
			lpos=pCls->mdl.GetHeadPosition();
			while(lpos) {
				pMdl = (CModule*)pCls->mdl.GetNext(lpos);
				if(pMdl->ret_type<TYPE_STRUCT)
					str.Format("%s %s(%s); /* %s */\n", type_tbl[pMdl->ret_type], pMdl->name, pMdl->arg, pMdl->comment);
				else
					str.Format("%s %s(%s); /* %s */\n", pMdl->ret_class, pMdl->name, pMdl->arg, pMdl->comment);
				f.WriteString(str);
			}
			f.WriteString("\n");
			lpos=pCls->mdl.GetHeadPosition();
			while(lpos) {
				pMdl = (CModule*)pCls->mdl.GetNext(lpos);
				if(pMdl->inline_flag)
					f.WriteString("inline ");
				if(pMdl->ret_type<TYPE_STRUCT)
					str.Format("%s %s(%s) /* %s */\n{\n", type_tbl[pMdl->ret_type], pMdl->name, pMdl->arg, pMdl->comment);
				else
					str.Format("%s %s(%s) /* %s */\n{\n", pMdl->ret_class, pMdl->name, pMdl->arg, pMdl->comment);
				f.WriteString(str);
				if(pMdl->var.GetCount()) {
					lpos2=pMdl->var.GetHeadPosition();
					while(lpos2) {
						f.WriteString("\t");
						pVar = (CVar*)pMdl->var.GetNext(lpos2);
						if(SCOPE_LOCAL_STATIC==pVar->scope) {
							str.Format("%s ", scope_tbl[pVar->scope]);
							f.WriteString(str);
						}
						if(pVar->type<TYPE_STRUCT)
							str.Format("%s", type_tbl[pVar->type]);
						else
							if(TYPE_UNION==pVar->type)
								str.Format("union %s", pVar->struct_union);
							else
								str.Format("%s", pVar->struct_union);
						f.WriteString(str);
						for(i=0; i<pVar->pointer; i++)
							f.WriteString("*");
						if(""==pVar->start || TYPE_UNION==pVar->type)
							str.Format(" %s;", pVar->name);
						else
							if(pVar->start.Find(',')!=-1)
								str.Format(" %s = {%s};", pVar->name, pVar->start);
							else
								str.Format(" %s = %s;", pVar->name, pVar->start);
						f.WriteString(str);
						if(""!=pVar->comment) {
							str.Format(" /* %s */", pVar->comment);
							f.WriteString(str);
						}
						f.WriteString("\n");
					}
					f.WriteString("\n");
				}
				if(pMdl->padf.GetCount()) { // モジュールにＰＡＤ図形などがあるかどうか
					pad=0;
					lpos2=pMdl->padf.GetHeadPosition();
					while(lpos2) {
						pPadf = (CPadf*)pMdl->padf.GetNext(lpos2);
						if (pPadf->type>=PADF_PROCESS && pPadf->type<=PADF_REPEAT && -1==pPadf->prev_p)
							break;
						pad++;
					}
					WriteLines(pMdl,pad,1);	// pMdlがモジュールのアドレス、pがＰＡＤ、１がインデント
				}
				str.Format("} /* End of %s() */\n\n", pMdl->name);
				f.WriteString(str);
			}
			f.WriteString("/* End of file */\n"); // ファイルの末尾であることを示す
			f.Close();	// ファイルを閉じる
		} else {
			AfxMessageBox("ファイルを開けません",MB_OK);
			return FALSE;
		}
		return TRUE;
	} else 
		return FALSE;
}

void CVEDoc::WriteLines(CModule* pMdl, int p, int indent)
{

	int pad_num, next_p;
	CString str;
	BOOL do_while_flag=FALSE;
	CPadf *pPadf, *pNextPadf;
	
	WriteIndent(indent);

	pPadf = GetPadf(pMdl,p);
	if(!(pPadf->type==PADF_REPEAT && pPadf->type2==2)) { /* do ～ while */
		str.Format(padf_msg[pPadf->type][pPadf->type2], pPadf->str);
		if(PADF_PROCESS==pPadf->type)
			str += ";";
		f.WriteString(str);
	}
	next_p = GetNextPadfNum(pMdl,p);	// 下のＰＡＤ図形の番号を得る
	switch(pPadf->type) {	// ＰＡＤ図形の種類を得る */
	case PADF_PROCESS:	// 処理
		if(pPadf->comment.GetLength()) {
			str.Format(" /* %s */", pPadf->comment);
			f.WriteString(str);
		}
		f.WriteString("\n");
		break;
	case PADF_SELECTION:	// 選択
		if(pPadf->num_branch>0) {
			if(pPadf->comment.GetLength()) {
				str.Format(" /* %s */", pPadf->comment);
				f.WriteString(str);
			}
			f.WriteString(" {\n");
			switch(pPadf->type2) {
			case 0:	// if文
				if(-1!=(pad_num=GetNextPadfNum(pMdl,p,1))) {
					WriteLines(pMdl,pad_num,indent+1);
					WriteIndent(indent);
				}
				f.WriteString("}");
				if(-1!=(pad_num=GetNextPadfNum(pMdl,p,2))) {
					f.WriteString(" else {\n");
					WriteLines(pMdl,pad_num,indent+1);
					WriteIndent(indent);
					f.WriteString("}\n");
				} else
					f.WriteString("\n");
				break;
			case 1:	// switch文
				for(int pos=1; pos<=pPadf->num_branch; pos++) {
					if(-1!=(pad_num=GetNextPadfNum(pMdl,p,pos))) {
						WriteIndent(indent);
						pNextPadf=GetPadf(pMdl,pad_num);
						str.Format("case %s:\n",pNextPadf->case_str);
						f.WriteString(str);
						WriteLines(pMdl,pad_num,indent+1);
						WriteIndent(indent+1);
						f.WriteString("break;\n");
					}
				}
				WriteIndent(indent);
				f.WriteString("}\n");
				break;
			}
		}
		break;
	case PADF_REPEAT:	// 反復
		switch(pPadf->type2) {
		case 2:	// do while */
			str.Format("do { /* %s */\n", pPadf->comment);
			f.WriteString(str);
			if((pad_num=GetNextPadfNum(pMdl,p,-1))!=-1) {
				WriteLines(pMdl,pad_num,indent+1);
			}
			WriteIndent(indent);
			str.Format("} while(%s);\n",pPadf->str);
			f.WriteString(str);
			break;
		default:	// do while以外
			f.WriteString(" {\n");
			if((pad_num=GetNextPadfNum(pMdl,p,-1))!=-1) {
				WriteLines(pMdl,pad_num,indent+1);
			}
			WriteIndent(indent);
			f.WriteString("}\n");
			break;
		}
		break;
	}
	if(next_p != -1) {
		WriteLines(pMdl, next_p, indent);
	}
}

void CVEDoc::WriteIndent(int indent)
{
	for(int i=0; i<indent; i++)
		f.WriteString("\t");
}

void CVEDoc::OnBuildBuild() // ビルド処理
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	BuildApp(FALSE);
}

void CVEDoc::OnBuildExec() // 実行処理
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	BuildApp(TRUE);
}

void CVEDoc::BuildApp(BOOL sw)
{
	CString batch_filename, filename, str = "", str2 = "";
	int str_pos;

	m_wndTabs.SetActiveTab(0);	// デバッグ・タブ
	m_wndOutput.PrintBuild(GetTitle() + _T("をビルドします。"));
	if (CVEDoc::SaveSourceFile()) {	// ビルド
		str = path;
		if ((str_pos = str.Find(".cpp")) != -1)
			str.Delete(str_pos, 4);

		f.Open(str + ".mak", CFile::modeCreate | CFile::modeWrite);
		f.WriteString("\"" + str + ".exe\" : \"" + str + ".cpp\"\n\tcl.exe /EHsc \"" + str + ".cpp\"\n");
		f.Close();

		batch_filename = str + ".bat";
		f.Open(batch_filename, CFile::modeCreate | CFile::modeWrite);
		switch (compiler_type) {
		case COMPILER_VC_ENV:
			str2 = "";
			break;
		case COMPILER_VC2015:
			str2 = "call \"C:\\Program Files\\Microsoft Visual Studio 14.0\\VC\\vcvarsall.bat\"\n";
			break;
		case COMPILER_VC2013:
			str2 = "call \"C:\\Program Files\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\"\n";
			break;
		case COMPILER_VC2012:
			str2 = "call \"C:\\Program Files\\Microsoft Visual Studio 11.0\\VC\\vcvarsall.bat\"\n";
			break;
		case COMPILER_VC2010:
			str2 = "call \"C:\\Program Files\\Microsoft Visual Studio 10.0\\VC\\vcvarsall.bat\"\n";
			break;
		case COMPILER_VC2008:
			str2 = "call \"C:\\Program Files\\Microsoft Visual Studio 9.0\\VC\\vcvarsall.bat\"\n";
			break;
		case COMPILER_VC60:
			str2 = "call \"C:\\Program Files\\Microsoft Visual Studio\\VC98\\bin\\vcvars32.bat\"\n";
			break;
		case COMPILER_VC_OTHER:
			str2 = "call \"" + compiler_path + "\"\n";
			break;
		}
		str2 += "nmake /F \"" + str + ".mak\"\n";
		if (sw) {
			str2 += "if errorlevel 1 goto end\npause\ncls\n";
			str2 += "\"" + str + ".exe\"\n:end\npause";
		} else {
			str2 += "pause";
		}
		f.WriteString(str2);
		f.Close();
		system("\"" + batch_filename + "\"");
		if (sw) {
			m_wndTabs.SetActiveTab(1);	// デバッグ・タブ
			m_wndOutput.PrintDebug(GetTitle() + _T("を実行しました。"));
		}
		CFile::Remove(batch_filename);
	}
}

void CVEDoc::OnToolOption() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	COptionDlg dlg;

	dlg.m_compiler_type=compiler_type;
	dlg.m_compiler_path=compiler_path;
	if(dlg.DoModal()==IDOK) {
		compiler_type=dlg.m_compiler_type;
		compiler_path=dlg.m_compiler_path;
	}
}
