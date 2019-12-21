#pragma once
#define ID_MAXSIZE		8			//���� ����� �������� ��������������
#define TI_MAXSIZE		4096		//���� ����� ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT	0		//�������� �� ��������� ��� int
#define TI_CHAR_DEFAULT  NULL		//�������� �� ��������� ��� char
#define TI_STR_DEFAULT	NULL		//�������� �� ��������� ��� string
#define TI_NULLIDX		0xffffffff	//��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255         //����������� ���������� ����� ������
#define INT_MAXSIZE     65536       //����������� ���������� ��������
#define INT_MINUS_MAXSIZE   0		//���������� ���������� ��������
#define TI_CHAR_MAXSIZE     255		//����������� ���������� ����� ������ char
#define TI_CHAR_MINSIZE    3		//���������� ���������� ����� ������ char


namespace IT
{
	enum IDDATATYPE { NUM = 1, STR = 2, CHR = 3 };	        //���� ������ ���������������
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, S = 5 };		//���� ���������������: ����������, �������, ��������, �������,��������.����.
	struct Entry
	{
		int			idxfirstLE;						//������ � ������� ������	
		int         line;                           //������ ������ � �������� ����
		char		id[ID_MAXSIZE];					//�������������, ��������� ��������� �� ID_MAXSIZE
		IDDATATYPE	iddatatype;						//��� ������
		IDTYPE		idtype;							//��� ��������������
		union
		{
			int	vint;								//��������	
			struct
			{
				int len;							//���������� �������� � string
				char str[TI_STR_MAXSIZE - 1];		//������� string
			}vstr;									//�������� string
			struct
			{
				int count;							//���������� �������� � char
				char chr[TI_CHAR_MAXSIZE];						//������� char
			}vchr;
		}value;										//�������� ��������������
		Entry()                                     //����������� ��� ����������
		{
			this->value.vint = TI_INT_DEFAULT;
			this->value.vstr.len = '\0';
			this->value.vchr.count = '\0';
		}
		Entry(char* id, int idxLT, IDDATATYPE datatype, IDTYPE idtype); //����������� � �����������

	};
	struct IdTable									//��������� ������� ���������������
	{
		int maxsize;								//������� ������� ��������������� < TI_MAXSIZE
		int size;									//������� ������ ������� ��������������� < maxsize
		Entry* table;								//������ ����� ������� ���������������
	};
	IdTable Create(int size = NULL);				//������� ������� ��������������� < TI_MAXSIZE
	void Add(										//�������� ������ � ������� ���������������
		IdTable& idtable,							//��������� ������� ���������������
		Entry entry);								//������ ������� ��������������� 
	Entry GetEntry(									//�������� ������ ������� ���������������
		IdTable& idtable,							//��������� ������� ���������������
		int n);										//����� ���������� ������
	int IsId(										//�������: ����� ������(���� ����), TI_NULLIDX(���� ����)
		IdTable& idtable,							//��������� ������� ���������������
		char id[ID_MAXSIZE]);						//�������������
	int GetSize(IdTable& idtable);					//�������� ������
	void SetValue(IdTable& idtable, int, char*);	//������ �������� ��������������
}