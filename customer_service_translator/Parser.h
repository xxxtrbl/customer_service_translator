#pragma once
#include"dataStructure.h"
#include"script.h"

class Parser {

private:
	Script _script;
	ifstream file;
	vector<vector<string>> script_file;
	//The current step.
	Step cur_step;

public:
	//�����ļ�
	void parseFile();
	//To build a grammer tree.
	void buildTree();
	//����tokens
	void processTokens(vector<Token>& tokens);
	//Parser parses.
	void Parse();
	//��ȡ�﷨��
	Script& getScript();
};