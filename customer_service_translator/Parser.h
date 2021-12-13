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
	//读取sfname文件中的内容,保存到ofname中
	void parseFile(string sfname,File &ofname );
	//处理变量
	void parseVars();
	//To build a grammer tree.
	void buildTree();
	//处理tokens
	void processTokens(vector<Token>& tokens);
	//Parser parses.
	void Parse();
	//获取语法树
	Script& getScript();
	//查询用户名
	string checkVar(Varname var,string strnm);
	//创建用户
	bool addItem(string namem,double money);
};