#include "stdafx.h"
#include "Generation.h"
#include "SA.h"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");
	Log::LOG log = Log::INITLOG;
	bool sintaksis = false;
	bool semantika = false;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);					// ��������� ����������		
		log = Log::getlog(parm.log);									// �������� log				
		Log::LOG out = Log::INITLOG;									// ������������� log �����	
		out = Log::getlog(parm.out);									// ������� out �����		
		Log::writeLog(log);												// ������ ���������			
		Log::writeParm(log, parm);										// ������ ����������		
		In::IN in = In::getin(parm.in, parm.out);						// ��������� �������� ����������
		Log::writeIn(log, in);											// ������ �������� ����������	
		LeX::LEX tables = LeX::INITLEX(in, log);				     	// ��������� ������� ������		
		Log::writeAllTokens(log, in);									// ������ ���� ����			
		Log::writeLexicalTable(log, tables.Lextable);	             	// ������ ������� ����.		
		Log::writeIDtable(log, tables.IDtable);	                     	// ������ ������� ������.	
		Log::writeIntermediateCode(log, tables.Lextable);               // ������ �������������� ����
		semantika = SemanticAnalyze(tables.Lextable, in, tables.IDtable, log); //������ �������������� �������
		if (semantika == true)
		{
			MFST::Mfst mfst(tables, GRB::getGreibach());                    // ������������� ��� ��������������� �����������
			MFST_TRACE_START(log);                                          // �����
			sintaksis = mfst.start(log);                                    // ����� ��������������� �������
			if (sintaksis == false)
				throw ERROR_THROW(8);
			mfst.savededucation();                                          // ��������� ������� ������
			mfst.printrules(log);                                           // ������ ������ �������
		}
		if (sintaksis == true)
		{
			Generation(tables.Lextable, in.tokens, tables.IDtable);         // ���������� ����
			PN Polish;                                                      // ���������� ���������� Polish �����.���� PN
			if (Polish.CreatePolishNotation(&tables))                       // ���������� �������� �������
			{
				Log::writeIntermediateCode(log, tables.Lextable);
			}
		}
		Log::Close(log);												// �������� log �����		
		Log::Close(out);												// �������� out �����

	}
	catch (Error::ERROR e)
	{
		cout << e.id << "," << e.message << endl;
		Log::writeError(log, e);                                        // ������� ������ � ������ �� ���������
	}
	cout << "code is working" << endl;
	system("pause");
	return 0;
}