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

	//记录当前step
	Step cur_step;

	
public:

	//读取sfname文件中的内容,保存到ofname中
	void parseFile(string sfname,File &ofname );

	//处理变量
	void parseVars();

	//建立一个语法树
	void buildTree();

	//处理tokens
	void processTokens(vector<Token>& tokens);

	//语法分析
	void Parse();

	//获取语法树
	Script& getScript();

	//测试桩：测试不同tokens的处理结果并输出
	void test_processTokens();
	
};