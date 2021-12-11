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
	//处理文件
	void parseFile();
	//To build a grammer tree.
	void buildTree();
	//处理tokens
	void processTokens(vector<Token>& tokens);
	//Parser parses.
	void Parse();
	//获取语法树
	Script& getScript();
};