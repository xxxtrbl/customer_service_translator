#pragma once
#include"dataStructure.h"
#include"script.h"

extern string script_file_name;
extern string data_file_name;

class Parser {

private:
	Script _script;
	File script_file;
	File data_file;
	Step cur_step;

	
public:
	//��ȡsfname�ļ��е�����,���浽ofname��
	void parseFile(string sfname,File &ofname );
	//�������
	void parseVars();
	//To build a grammer tree.
	void buildTree();
	//����tokens
	void processTokens(vector<Token>& tokens);
	//Parser parses.
	void Parse();
	//��ȡ�﷨��
	Script& getScript();
	//��ѯ�û���
	string checkVar(Varname var,string strnm);
	//�����û�
	bool addItem(string namem,double money);
};