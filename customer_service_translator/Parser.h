#pragma once
#include"dataStructure.h"
#include"script.h"

extern string script_file_name;
extern string data_file_name;
extern File data_file;

class Parser {

private:

	Script _script;
	File script_file;

	//��¼��ǰstep
	Step cur_step;

	
public:

	//��ȡsfname�ļ��е�����,���浽ofname��
	void parseFile(string sfname,File &ofname );

	//�������
	void parseVars();

	//����һ���﷨��
	void buildTree();

	//����tokens
	void processTokens(vector<Token>& tokens);

	//�﷨����
	void Parse();

	//��ȡ�﷨��
	Script& getScript();

	//����׮�����Բ�ͬtokens�Ĵ����������
	void test_processTokens();
	
};